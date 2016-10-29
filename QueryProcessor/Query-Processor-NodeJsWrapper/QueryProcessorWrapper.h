#ifndef WRAPPER_H
#define WRAPPER_H

#define BUILDING_NODE_EXTENSION

#include <node/node.h>
#include <node/v8.h>
#include <node/node_object_wrap.h>

#include <string>
#include <iostream>
#include <sstream>

#include <QueryProcessor.h>
#include "Test/Wrapper.h"


using namespace std;

// For all classes that we want to include in our addon, we must extend the node::ObjectWrap class.
class QueryProcessorWrapper : public node::ObjectWrap
{
private:
    double value_;

#ifdef TEST_WRAPPER
    static myclass m_myclass;
#endif

    static QueryProcessor m_queryprocessor;

private:
    explicit QueryProcessorWrapper(double value = 0);
    ~QueryProcessorWrapper();

    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> treemapBuild(const v8::Arguments& args);
    static v8::Handle<v8::Value> treemapData(const v8::Arguments& args);
    static v8::Handle<v8::Value> search(const v8::Arguments& args);
    static v8::Handle<v8::Value> feedback(const v8::Arguments& args);
    static v8::Handle<v8::Value> saveSession(const v8::Arguments& args);

public:
    static void Init(v8::Handle<v8::Object> exports);
};

#endif // WRAPPER_H
