#ifndef __HIKERS_H
#define __HIKERS_H

class Hiker
{
public:
    Hiker() {
        all_hikers.clear();
        bridge_times.clear();

        total_bridge_time = 0.0;
    }
    ~Hiker() {};
    
    void AddAndSortHikers( const YAML::Node& hikersYAML );
    void HikeAcrossBridge( const YAML::Node& bridgeYAML );
    void AllBridgeTimes( void );
    void DumpHikers() {
        std::cout << "hikers: ";
        for( std::vector<double>::iterator it = all_hikers.begin();
             it != all_hikers.end();
             ++it ) {
            std::cout << *it << " ft./min., ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<double> all_hikers;
    std::vector<double> bridge_times;
    double total_bridge_time;
};

#endif
