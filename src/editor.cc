#include "../deps/libfleaux/include/editor.hh"
#include "editor.hh"
#include <iostream>
#include <fstream>
#include <node.h>
#include <sstream>
#include <v8.h>

using namespace std;
using namespace v8;

Persistent<Function> Fleaux::Node::Editor::constructor;

void
Fleaux::Node::Editor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Fleaux::Node::Editor::New);
    tpl->SetClassName(String::NewSymbol("Editor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("toString"),
                                    FunctionTemplate::New(Fleaux::Node::Editor::ToString)->GetFunction());
    Fleaux::Node::Editor::constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Editor"), Editor::constructor);
}

Handle<Value>
Fleaux::Node::Editor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) { //new Editor()
        if (!args[0]->IsUndefined()) {
            string path(*String::Utf8Value(args[0]));
            Fleaux::Node::Editor* ed = new Fleaux::Node::Editor(path);
            cout << "Editor in Node Editor Constructor: " << ed << endl;
            ed->Wrap(args.This());
            return args.This();
        } else {
            Fleaux::Node::Editor* ed = new Fleaux::Node::Editor();
            ed->Wrap(args.This());
            return args.This();
        }
    } else { //Editor()
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(Fleaux::Node::Editor::constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Fleaux::Node::Editor::ToString(const Arguments& args)
{
    HandleScope scope;
    Fleaux::Node::Editor* thisEd = ObjectWrap::Unwrap<Fleaux::Node::Editor>(args.This());
    stringstream outStream;
    outStream << *thisEd;
    return scope.Close(String::New(outStream.str().c_str(), thisEd->size));
}

Persistent<Function> Fleaux::Node::Cursor::constructor;

void
Fleaux::Node::Cursor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Fleaux::Node::Cursor::New);
    tpl->SetClassName(String::NewSymbol("Cursor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(7);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("insert"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::Insert)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("remove"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::Remove)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("replace"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::Replace)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getIndex"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::GetIndex)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getX"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::GetX)->GetFunction());
    tpl->PrototypeTemplate()->Set(   String::NewSymbol("getY"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::GetY)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("move"),
                                    FunctionTemplate::New(Fleaux::Node::Cursor::Move)->GetFunction());
    Fleaux::Node::Cursor::constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Cursor"), Fleaux::Node::Cursor::constructor);
}

Handle<Value>
Fleaux::Node::Cursor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) {
        if (args[0]->IsUndefined()) {
            return ThrowException(String::New("ERROR: Cursor::New - Must provide an argument"));
        } else {
            Fleaux::Node::Editor* ed = ObjectWrap::Unwrap<Fleaux::Node::Editor>(args[0]->ToObject());
            cout << "Editor in Node Cursor constructor: " << ed << endl;
            Fleaux::Node::Cursor* curs = new Fleaux::Node::Cursor(*ed);
            cout << "Created Cursor!" << endl;
            curs->Wrap(args.This());
            return args.This();
        }
    } else {
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(Fleaux::Node::Cursor::constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Fleaux::Node::Cursor::Insert(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Insert - must provide an argument")));
    } else {
        Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
        /* input could be pretty big, so let's heap allocate the c++ string */
        string* input = new string(*String::Utf8Value(args[0]));
        thisCurs->insert(*input);
        delete input;
        return scope.Close(Undefined());
    }
}

Handle<Value>
Fleaux::Node::Cursor::Remove(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Remove - Must provide an argument")));
    } else {
        Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
        int length = (int)args[0]->IntegerValue();
        thisCurs->remove(length);
        return scope.Close(Undefined());
    }
}

Handle<Value>
Fleaux::Node::Cursor::Replace(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined() || args[1]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Replace - missing or invalid arguments")));
    } else {
        Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
        int length = (int)args[0]->IntegerValue();
        string* replacement = new string(*String::Utf8Value(args[1]));
        thisCurs->replace(length, *replacement);
        return scope.Close(Undefined());
    }
}

Handle<Value>
Fleaux::Node::Cursor::GetIndex(const Arguments& args)
{
    HandleScope scope;
    Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
    size_t index = thisCurs->getIndex();
    return scope.Close(Number::New(static_cast<double>(index)));
}

Handle<Value>
Fleaux::Node::Cursor::GetX(const Arguments& args)
{
    HandleScope scope;
    Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
    size_t x = thisCurs->getX();
    return scope.Close(Number::New(static_cast<double>(x)));
}

Handle<Value>
Fleaux::Node::Cursor::GetY(const Arguments& args)
{
    HandleScope scope;
    Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
    size_t y = thisCurs->getY();
    return scope.Close(Number::New(static_cast<double>(y)));
}

Handle<Value>
Fleaux::Node::Cursor::Move(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined() || args[1]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Move - invalid arguments")));
    } else {
        Fleaux::Node::Cursor* thisCurs = ObjectWrap::Unwrap<Fleaux::Node::Cursor>(args.This());
        int offsetX = args[0]->IntegerValue();
        int offsetY = args[1]->IntegerValue();
        thisCurs->move(offsetX, offsetY);
        return scope.Close(Undefined());
    }
}
