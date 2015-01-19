#include "../deps/libfleaux/include/editor.hh"
#include "editor.hh"
#include <node.h>
#include <v8.h>

using namespace v8;

Persistent<Function> Editor::constructor;

Editor::Editor(void)
{
//    __Cursor = new Cursor(this);
}

Editor::~Editor(void)
{
//    delete __Cursor;
}

void
Editor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Editor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getCursor"),
                                    FunctionTemplate::New(GetCursor)->getFunction());
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

Handle<Value>
Editor::GetCursor(const Arguments& args)
{
    HandleScope scope;
    Persistent<Context> ctx = Context::New();
    Handle<Object> global = ctx->Global();
    Handle<Value> newArgs[1];
    newArgs[0] = args.This();
    Cursor
}

Persistent<Function> Cursor::constructor;

void
Cursor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Cursor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("insert"),
                                    FunctionTemplate::New(Insert)->getFunction());
    tpl-PrototypeTemplate()->Set(   String::NewSymbol("remove"),
                                    FunctionTemplate::New(Remove)->getFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getIndex"),
                                    FunctionTemplate::New(GetIndex)->getFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getX"),
                                    FunctionTemplate::New(GetX)->getFunction());
    tpl-PrototypeTemplate()->Set(   String::NewSymbol("getY"),
                                    FunctionTemplate::New(GetY)->getFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveH"),
                                    FunctionTemplate::New(MoveH)->getFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveV"),
                                    FunctionTemplate::New(MoveV)->getFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Editor"), constructor);
}

Handle<Value>
Cursor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) {
        if (args[0]->IsUndefined()) {
            return ThrowException(String::New("ERROR: Must provide an argument"));
        } else {
        Cursor* curs = new Cursor(ObjectWrap::Unwrap<Editor>(args[0]));
        curs->Wrap(args.This());
        return args.This();
    } else {
        return scop.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Cursor::Insert(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: must provide an argument"));
    } else {
        /* input could be pretty big, so let's heap allocate the c++ string */
        string input = new string(String::Utf8Value(args[0]));
        insert(*input);
        delete input;
        return Undefined();
    }
}

Handle<Value>
Cursor::Remove(const Arguments& args)
{
    if (args[0]-IsUndefined()) {
        return ThrowException(String::New("Error Must provide an argument"));
    } else {
        int length = (int)args[0]->IntegerValue();
        remove(length);
        return Undefined();
    }
}

Handle<Value>
Cursor::GetIndex(const Arguments& args)
{
    size_t index = getIndex();
    return Number::New(static_cast<double>(index));
}

Handle<Value>
Cursor::GetX(const Arguments& args)
{
    size_t x = getX();
    return Number::New(static_cast<double>(x));
}

Handle<Value>
Cursor::GetY(const Arguments& args)
{
    size_t y = getY();
    return Number::New(static_cast<double>(y));
}

Handle<Value>
Cursor::MoveH(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: must provide an argument"));
    } else {
        int offset = args[0]->IntegerValue();
        moveH(offset);
        return Undefined();
    }
}

Handle<Value>
Cursor::MoveV(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: must provide an argument"));
    } else {
        int offset = args[0]->IntergerValue();
        moveV(offset);
        return Undefined();
    }
}
