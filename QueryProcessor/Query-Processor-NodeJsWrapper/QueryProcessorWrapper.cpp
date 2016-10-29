#include "QueryProcessorWrapper.h"


#ifdef TEST_WRAPPER
myclass QueryProcessorWrapper::m_myclass;
#endif

QueryProcessor QueryProcessorWrapper::m_queryprocessor;

v8::Persistent<v8::Function> QueryProcessorWrapper::constructor;

QueryProcessorWrapper::QueryProcessorWrapper(double value) : value_(value)
{
}


QueryProcessorWrapper::~QueryProcessorWrapper()
{
}


void QueryProcessorWrapper::Init(v8::Handle<v8::Object> exports)
{
    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
    tpl->SetClassName(v8::String::NewSymbol("QueryProcessorWrapper"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype

    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("treemapBuild"),
    v8::FunctionTemplate::New(treemapBuild)->GetFunction());

    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("treemapData"),
    v8::FunctionTemplate::New(treemapData)->GetFunction());

    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("search"),
    v8::FunctionTemplate::New(search)->GetFunction());

    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("feedback"),
    v8::FunctionTemplate::New(feedback)->GetFunction());

    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("saveSession"),
    v8::FunctionTemplate::New(saveSession)->GetFunction());

    constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
    exports->Set(v8::String::NewSymbol("QueryProcessorWrapper"), constructor);
}


v8::Handle<v8::Value> QueryProcessorWrapper::New(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.IsConstructCall())
    {
        // Invoked as constructor: `new QueryProcessorWrapper(...)`
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        QueryProcessorWrapper* obj = new QueryProcessorWrapper(value);
        obj->Wrap(args.This());
        return args.This();
    }
    else
    {
        // Invoked as plain function `QueryProcessorWrapper(...)`, turn into construct call.
        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}


v8::Handle<v8::Value> QueryProcessorWrapper::treemapBuild(const v8::Arguments& args)
{
    cout << "QueryProcessorWrapper::treemapBuild" << endl;

    v8::HandleScope scope;

    if (args.Length() < 4)
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("treemapBuild: Wrong number of arguments")));
        return scope.Close(v8::Undefined());
    }
    if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber())
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("treemapBuild: Wrong arguments")));
        return scope.Close(v8::Undefined());
    }

    int x      = args[0]->Uint32Value();
    int y      = args[1]->Uint32Value();
    int width  = args[2]->Uint32Value();
    int height = args[3]->Uint32Value();


    QueryProcessorWrapper* obj = ObjectWrap::Unwrap<QueryProcessorWrapper>(args.This());
    string jsondata = obj->m_queryprocessor.treemap(x, y, width, height);
    v8::Local<v8::String> value = v8::String::New(jsondata.c_str());

    // Callback part implementation
    v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[4]);
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { v8::Local<v8::Value>::New(value) };
    cb->Call(v8::Context::GetCurrent()->Global(), argc, argv);


    return scope.Close(v8::Undefined());
}


v8::Handle<v8::Value> QueryProcessorWrapper::treemapData(const v8::Arguments& args)
{
    cout << "QueryProcessorWrapper::treemapData" << endl;

    v8::HandleScope scope;

    if (args.Length() < 1)
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("treemapData: Wrong number of arguments")));
        return scope.Close(v8::Undefined());
    }
    if (!args[0]->IsNumber())
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("treemapData: Wrong arguments")));
        return scope.Close(v8::Undefined());
    }

    int depth = args[0]->Uint32Value();


    QueryProcessorWrapper* obj = ObjectWrap::Unwrap<QueryProcessorWrapper>(args.This());
    string jsondata = obj->m_queryprocessor.treemap(depth);
    v8::Local<v8::String> value = v8::String::New(jsondata.c_str());

    // Callback part implementation
    v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[1]);
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { v8::Local<v8::Value>::New(value) };
    cb->Call(v8::Context::GetCurrent()->Global(), argc, argv);


    return scope.Close(v8::Undefined());
}


v8::Handle<v8::Value> QueryProcessorWrapper::search(const v8::Arguments& args)
{
    cout << "QueryProcessorWrapper::search " << endl;

    v8::HandleScope scope;

    if (args.Length() < 1)
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("search: Wrong number of arguments")));
        return scope.Close(v8::Undefined());
    }
    if (!args[0]->IsString())
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("search: Wrong arguments")));
        return scope.Close(v8::Undefined());
    }


    v8::String::Utf8Value query(args[0]->ToString());
    std::string queryString = std::string(*query);

    cout << "QueryProcessorWrapper::search: query " << queryString << endl;

    QueryProcessorWrapper* obj = ObjectWrap::Unwrap<QueryProcessorWrapper>(args.This());
    string jsondata = obj->m_queryprocessor.search(queryString);
    v8::Local<v8::String> value = v8::String::New(jsondata.c_str());

    // Callback part implementation
    v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[1]);
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { v8::Local<v8::Value>::New(value) };
    cb->Call(v8::Context::GetCurrent()->Global(), argc, argv);


    return scope.Close(v8::Undefined());

}


v8::Handle<v8::Value> QueryProcessorWrapper::feedback(const v8::Arguments &args)
{
    cout << "QueryProcessorWrapper::feedback " << endl;

    v8::HandleScope scope;

    if (args.Length() < 1)
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("feedback: Wrong number of arguments")));
        return scope.Close(v8::Undefined());
    }
    if (!args[0]->IsString())
    {
        v8::ThrowException(v8::Exception::TypeError(v8::String::New("feedback: Wrong arguments")));
        return scope.Close(v8::Undefined());
    }


    v8::String::Utf8Value feedbackStr1(args[0]->ToString());
    std::string feedbackStr = std::string(*feedbackStr1);

    cout << "QueryProcessorWrapper::feedback: " << feedbackStr << endl;

    QueryProcessorWrapper* obj = ObjectWrap::Unwrap<QueryProcessorWrapper>(args.This());
    obj->m_queryprocessor.feedback(feedbackStr);

    return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> QueryProcessorWrapper::saveSession(const v8::Arguments &args)
{
    cout << "QueryProcessorWrapper::saveSession" << endl;
    v8::HandleScope scope;

    QueryProcessorWrapper* obj = ObjectWrap::Unwrap<QueryProcessorWrapper>(args.This());
    obj->m_queryprocessor.saveSession();

    return scope.Close(v8::Undefined());
}
