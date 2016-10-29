This is a DPhil research prototype with minimal comments in the code. The search engine consists of 4 sub projects. The web-based user interface is in a different [repository](https://github.com/saifulkhan/Search-Interface). 

# Common  

- Some common algorithms/functions being shared by all modules are implemented here. 
- The fileInfo (information related to a file (search result) data structure is also defined here.
 
	
## Compile 

We shall install this project-related deliverables in `$HOME/install/`. 

- `cd Common`
- `cmake -DCMAKE_INSTALL_PREFIX=$HOME/install/ -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug `
- make
- make install

## Test 

Write basic test cases in `test` directory and run it. Note: add the libraries, e.g., libCommon.so, libtinyxml.so, etc in the LD_LIBRARY path

- cd test
- ldd Test  <-- check the dependent libraries
- ./Test


# Inverted-Index

- Search engine inverted index

# Onto-Search


# Search-Interface-Qt
This is initial version of the search interface. Eventually we moved to web-based interface [repository](https://github.com/saifulkhan/Search-Interface). 

# TBD
- Cleanup all the projects
- Add comments
- Update the README file
-  
