# About

This is a research prototype of (a) an Enterprise Search Engine (C++) and (b) a Search Interface (Qt and Angular, d3). 


This repository contains the Enterprise Search Engine (back-end code).
Entire version of the prototype (part of my DPhil) is not open sourced. This code contains minimal comments and test cases.
Nevertheless, it can particulary be useful for learning, educational, and research purposes.


The search engine consists of following sub projects. 
1. Common		
2. Simulate-Data        <-- Create a large-scale data/files to be searched
3. LanguageProcessor    <-- Search: WordNet reader 
4. Ontology             <-- Search: ontology modules to support knowledge-assisted search, e.g., query expansion, ranking
5. Inverted-Index       <-- Index: to create, read, and update index (of files to be searched) 
6. Search-Interface-Qt. <-- UI


# Common  

- Some common algorithms/functions being shared by all modules are implemented here. 
- The fileInfo (information related to a file (search result) data structure is also defined here.
 
	
## Compile and Test

We shall install this project-related deliverables (header files and Common.so) in `$HOME/install/`. 

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

### Dependencies
Common project



# Language-Processor
	
## Compile and Test

We shall install this project-related deliverables (header files and LanguageProcessor.so) in `$HOME/install/`. 

- `cd Language-Processor`
- `cmake -DCMAKE_INSTALL_PREFIX=$HOME/install/ -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug `
- `make`
- `make install`
- `cd test`
- `ldd Test`  <-- check the dependent libraries
- `./Test`

### Dependencies
Common project


# Index

This is a enterprise search engine Inverted-Index code (minimal version based on Java Lucene). 

## Compile, Test, and Create Index



### Dependencies
Common, LanguageProcessor


# Onto-Search

TBD

# Search-Interface-Qt
This is initial version of the search interface.
Eventually we moved to a web-based (Angular and D3) search interface which is in [this repository](https://github.com/saifulkhan/Search-Interface).

TBD
