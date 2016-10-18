g++ -fPIC -c Wrapper.cpp -o Wrapper.o
g++ -shared  -Wl,-soname,libWrapper.so -o libWrapper.so Wrapper.o
