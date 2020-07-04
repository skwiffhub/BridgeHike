// Compile with:
//
//   g++ -std=c++11 -I yaml-cpp/include/ -L yaml-cpp/build -o bridge_hikers bridge_hikers.cpp -l yaml-cpp
//
// Note that "-l yaml-cpp" must be at the end after the source file.
#include <iostream>
#include <algorithm>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "hikers.h"

// Comment out to remove debug traces
//#define DEBUG_BH

// Maintain a vector with all the hikers and keep them sorted in
// order from slowest to fastest.
void Hiker::AddAndSortHikers( const YAML::Node& hikersYAML )
{
    for( YAML::const_iterator it = hikersYAML.begin(); it != hikersYAML.end() ; ++it ) {
#ifdef DEBUG_BH
        std::cout << "adding hiker: " << it->as<double>() << std::endl;
#endif
        all_hikers.push_back(it->as<double>());
    }
    std::sort( all_hikers.begin(), all_hikers.end() );
}

// The narrow bridge can only hold two people at a time. They have one
// torch and because it's night, the torch has to be used when crossing
// the bridge. Each hiker can cross the bridge at different speeds. When
// two hikers cross the bridge together, they must move at the slower
// person's pace. 
void Hiker::HikeAcrossBridge( const YAML::Node& bridgeYAML )
{
    double bridge_time = 0.0; // in minutes
    double bridge_length = bridgeYAML.as<double>();
    double fastest_hiker;

    if ( all_hikers.size() == 0 ) {
        std::cout << "No hikers!" << std::endl;
        goto save_time;
    }
        
    if ( all_hikers.size() <= 2 ) {
        bridge_time = bridge_length / all_hikers.at(0);
        goto save_time;
    }

    // With more than two hikers, it gets more complicated ...
    //
    // Always have the fastest hiker carrying the torch. They will have
    // to double back across the bridge and escort the next hiker. It
    // The order in which the hikers cross shouldn't matter, as the
    // fastest person needs to be carrying the torch at all times. That
    // person will be pretty worn out by the end of the hike.
    fastest_hiker = all_hikers.at(all_hikers.size() - 1);

#ifdef DEBUG_BH
    std::cout << "bridge length: " << bridge_length << " feet" << std::endl <<
        "fastest hiker speed: " << fastest_hiker << " feet per minute" << std::endl;
#endif

    for( std::vector<double>::iterator it = all_hikers.begin(); it < (all_hikers.end() - 1); ++it ) {
        // The current hiker is always slower than (or the same speed as) the
        // torch carrier. Add  the time that both hikers take to cross
        // (the slower hiker's time) plus the time it takes the fastest hiker
        // to run back across the bridge with the torch to get the next hiker.
#ifdef DEBUG_BH
       std::cout << "hiker speed: " << *it << " feet per minute" << std::endl;
#endif
        bridge_time += ( bridge_length / *it );
        // When the last hiker is escorted across, we're done with this bridge.
        if ( (it + 2) != all_hikers.end() ) {
            // fastest hiker runs back across the bridge with the torch
#ifdef DEBUG_BH
            std::cout << "it pointers: " << it - all_hikers.begin() << " " << all_hikers.end() - all_hikers.begin() << std::endl; 
#endif
            bridge_time += ( bridge_length / fastest_hiker );
        } else {
#ifdef DEBUG_BH
            std::cout << "last two hikers crossing bridge" << std::endl;
#endif
        }
#ifdef DEBUG_BH
        std::cout << "bridge time: " << bridge_time << " minutes" << std::endl;
#endif
    }
#ifdef DEBUG_BH
    std::cout << std::endl;
#endif

save_time:
    bridge_times.push_back( bridge_time );
}

void Hiker::AllBridgeTimes()
{
    for( std::vector<double>::iterator it = bridge_times.begin(); it != bridge_times.end(); ++it ) {
        total_bridge_time += *it;
        std::cout << "Bridge " << it - bridge_times.begin() <<
            " time: " << *it << " minutes" << std::endl;
    }

    std::cout << "Total time on all bridges: " << total_bridge_time << " minutes" << std::endl;
}

int main( int    argc,
          char** argv )
{
    Hiker hike_bridge;
    YAML::Node config = YAML::LoadFile("config.yaml");

#ifdef DEBUG_BH
    std::cout << "Config:" << std::endl << config << std::endl;
    std::cout << "Number of bridges: " << config["bridges"].size() << std::endl;
#endif
    
    if ( config["bridges"].size() == 0 ) {
        std::cout << "No bridges to cross ... we're done!" << std::endl;
        exit(0);
    }

    if ( config["initial_hikers_speed"].size() == 0 ) {
        std::cout << "No hikers ... we're done!" << std::endl;
        exit(0);
    }

    // add starting hikers
    hike_bridge.AddAndSortHikers( config["initial_hikers_speed"] );

#ifdef DEBUG_BH
    hike_bridge.DumpHikers();
#endif

    // Traverse the bridges
    for ( YAML::const_iterator it = config["bridges"].begin(); it != config["bridges"].end() ; ++it ) {
        // Additional hikers we encounter
        hike_bridge.AddAndSortHikers( (*it)["additional_hiker_speed"] );
#ifdef DEBUG_BH
        hike_bridge.DumpHikers();
#endif
        hike_bridge.HikeAcrossBridge( (*it)["length"] );
    }

    // Add up all the times on each bridge and dump the times
    hike_bridge.AllBridgeTimes();
}

