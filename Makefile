all: make-yaml-cpp bridge_hikers

get-yaml-cpp:
	-rm -rf yaml-cpp
	git clone https://github.com/jbeder/yaml-cpp

make-yaml-cpp:
	-mkdir -p yaml-cpp/build
	cd yaml-cpp && \
	cd build && \
	cmake .. && \
	make

bridge_hikers: yaml-cpp/build/libyaml-cpp.a bridge_hikers.cpp hikers.h
	g++ -std=c++11 -I yaml-cpp/include/ -L yaml-cpp/build -o bridge_hikers bridge_hikers.cpp -l yaml-cpp

run_it: config.yaml
	./bridge_hikers
