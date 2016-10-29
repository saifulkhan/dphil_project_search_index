
#include "QueryProcessorWrapper.h"

void InitAll(v8::Handle<v8::Object> exports)
{
    QueryProcessorWrapper::Init(exports);
}

NODE_MODULE(QueryProcessorAddon, InitAll)


#if 0
#include <node/node.h>
#include <node/v8.h>

using namespace v8;

Handle<Value> Method(const Arguments& args)
{
  HandleScope scope;
  return scope.Close(String::New("world"));
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(hello, init)
#endif
