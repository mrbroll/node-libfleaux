#include "deps/libfleaux/include/editor.hh"
#include "editor.hh"
#include <node.h>
#include <v8.h>

using namespace v8;

Persistent<Function> Editor::constructor;

Editor::Editor(void) : Fleaux::Editor() {}
Editor::~Editor(void) : Fleaux::~Editor() {}

void
Editor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Editor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getCursor"),
                                    FunctionTemplate::New(getCursor)->getFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Editor"), constructor);
}

Handle<Value>
Editor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) { //new Editor()
        Editor* ed = new Editor();
        ed->Wrap(args.This());
        return args.This();
    } else { //Editor()
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Object>
Editor::getCursor(const Arguments& args)
{
    
}
