This is a research prototype of (a) an Enterprise Search Engine (C++) and (b) a Search Interface (Qt and Angular, d3).

Entire version of the prototype (part of my DPhil) is not open sourced. This code contains minimal comments and test cases.
Nevertheless, it can particulary be useful for learning, educational, and research purposes.


The search engine consists of 5 sub projects. 
- Common
- Simulate-Data
- Inverted-Index
- Onto-Search
- Search-Interface-Qt.


# Common  

- Some common algorithms/functions being shared by all modules are implemented here. 
- The fileInfo (information related to a file (search result) data structure is also defined here.
 
	
## Compile and Test

We shall install this project-related deliverables in `$HOME/install/`. 

- `cd Common`
- `cmake -DCMAKE_INSTALL_PREFIX=$HOME/install/ -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug `
- `make`
- `make install`

Some basic test cases are available in `test` directory and run it. Note: add the libraries, e.g., libCommon.so, libtinyxml.so, etc in the LD_LIBRARY path

- `cd test`
- `ldd Test`  <-- check the dependent libraries
- `./Test`


# Simulate-Data
Generate simulated dataset (a file containing file metadata information) based on the statistics available in the `Simulate-Data/Stat` folder.

## Compile, Run, and Generate Simulated Data

- Read the `DataManager.pro` file and load the project in QtCreator or use 'qmake' tool to generate the binary `DataManager`.

- Run the` DataManager` binary (select Simulation -> input a number of simulated file metadata to be generated -> click Apply). 

- The generated statistics can be found in $HOME/install/stat/data.csv (can be set in the `DataManager.pro` file).

- In order to generate the statistics available in the `Simulate-Data/Stat` folder, run the` DataManager` binary (select Statistics -> click Apply).   


# Inverted-Index

This is a Enterprise Search Engine Index code (minimal version based on Java Lucene). 

TBD

# Onto-Search

TBD

# Search-Interface-Qt
This is initial version of the search interface.
Eventually we moved to a web-based (Angular and D3) search interface which is in [this repository](https://github.com/saifulkhan/Search-Interface).

TBD
