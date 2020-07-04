# BridgeHike Sample Code

C++ program that simulates a team hiking through a forest at night. 
The team encounters a series of narrow bridges along the way. 
At each bridge they may meet additional hikers who need their help to cross the bridge.

The narrow bridge can only hold two people at a time. They have one torch and because
it's night, the torch has to be used when crossing the bridge. Each hiker can cross the
bridge at different speeds. When two hikers cross the bridge together, they must move at
the slower person's pace.

Determine the fastest time that the hikers can cross the each bridge and the total time for all
crossings. The input to the program will be a yaml file that describes the speeds of each
person, the bridges encountered, their length, and the additional hikers encountered along
the way. Your solution should assume any number of people and bridges can be provided
as inputs.

Demonstrate the operation of your program using the following inputs: the hikers cross 3
bridges, at the first bridge (100 ft long) 4 hikers cross (hiker A can cross at 100 ft/minute, B
at 50 ft/minute, C at 20 ft/minute, and D at 10 ft/minute), at the second bridge (250 ft long)
an additional hiker crosses with the team (E at 2.5 ft/minute), and finally at the last bridge
(150 ft long) two hikers are encountered (F at 25 ft/minute and G at 15 ft/minute).

## Building (tested on CentOS 7 and Ubuntu 16.04)

Clone this repo and then run this from the project root directory:

```
$ make get-yaml-cpp
$ make
```

## Running

To run the three-bridge scenario described above:
```
$ make run_it
```
or:
```
$ ./bridge_hikers
```
