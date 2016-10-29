This is a DPhil research prototype with minimal comments and test cases. 
The search engine consists of 5 sub projects. 
- Common
- Simulate-Data
- Inverted-Index
- Onto-Search
- Search-Interface-Qt : The web-based user interface is in a different [repository](https://github.com/saifulkhan/Search-Interface). 


# Common  

- Some common algorithms/functions being shared by all modules are implemented here. 
- The fileInfo (information related to a file (search result) data structure is also defined here.
 
	
## Compile 

We shall install this project-related deliverables in `$HOME/install/`. 

- `cd Common`
- `cmake -DCMAKE_INSTALL_PREFIX=$HOME/install/ -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug `
- `make`
- `make install`

## Test 

Write basic test cases in `test` directory and run it. Note: add the libraries, e.g., libCommon.so, libtinyxml.so, etc in the LD_LIBRARY path

- `cd test`
- `ldd Test`  <-- check the dependent libraries
- `./Test`


# Simulate-Data
Generate simulated dataset based on the statistics available in the `Simulate-Data/Stat` folder.

## Compile

- Read the `DataManager.pro` file and load the project in QtCreator or use 'qmake' tool to generate the binary `DataManager`.

- Run the` DataManager` binary (select Simulation -> input a number of simulated file metadata to be generated -> click Apply). 

- The generated statistics can be found in $HOME/install/stat/data.csv (can be set in the `DataManager.pro` file).

- In order to generate the statistics available in the `Simulate-Data/Stat` folder, run the` DataManager` binary (select Statistics -> click Apply).   


# Inverted-Index

This is a Enterprise Search Engine Index code (minimal version based on Java Lucene). 

# Onto-Search


# Search-Interface-Qt
This is initial version of the search interface. Eventually we moved to web-based interface [repository](https://github.com/saifulkhan/Search-Interface). 

# TBD
- Cleanup all the projects
- Add comments
- Update the README file
-  
