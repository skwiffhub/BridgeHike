all: yaml-cpp bridge_hikers

get-yaml-cpp:
	git clone https://github.com/jbeder/yaml-cpp

yaml-cpp:
	cd yaml-cpp
	-mkdir build
	cd build
	cmake ..

bridge_hikers: bridge_hikers.cpp hikers.h
	g++ -std=c++11 -I yaml-cpp/include/ -L yaml-cpp/build -o bridge_hikers bridge_hikers.cpp -l yaml-cpp

run_it: config.yaml
	./bridge_hikers
