#include "../deps/libfleaux/include/editor.hh"
#include "editor.hh"
#include <fstream>
#include <node.h>
#include <sstream>
#include <v8.h>

using namespace std;
using namespace v8;

Persistent<Function> Editor::constructor;

void
Editor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Editor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("toString"),
                                    FunctionTemplate::New(ToString)->GetFunction());
    Editor::constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Editor"), Editor::constructor);
}

Handle<Value>
Editor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) { //new Editor()
        Editor* ed;
        if (!args[0]->IsUndefined()) {
            string path(*String::Utf8Value(args[0]));
            ed = new Editor(path);
        } else {
            ed = new Editor();
        }
        ed->Wrap(args.This());
        return args.This();
    } else { //Editor()
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Editor::ToString(const Arguments& args)
{
    HandleScope scope;
    Editor* thisEd = ObjectWrap::Unwrap<Editor>(args.This());
    stringstream outStream;
    outStream << *thisEd;
    return scope.Close(String::New(outStream.str().c_str(), thisEd->size));
}

Persistent<Function> Cursor::constructor;

void
Cursor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Cursor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(7);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("insert"),
                                    FunctionTemplate::New(Insert)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("remove"),
                                    FunctionTemplate::New(Remove)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("replace"),
                                    FunctionTemplate::New(Replace)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getIndex"),
                                    FunctionTemplate::New(GetIndex)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getX"),
                                    FunctionTemplate::New(GetX)->GetFunction());
    tpl->PrototypeTemplate()->Set(   String::NewSymbol("getY"),
                                    FunctionTemplate::New(GetY)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveX"),
                                    FunctionTemplate::New(MoveX)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveY"),
                                    FunctionTemplate::New(MoveY)->GetFunction());
    Cursor::constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Cursor"), Cursor::constructor);
}

Handle<Value>
Cursor::New(const Arguments& args)
{
    HandleScope scope;
    if (args.IsConstructCall()) {
        if (args[0]->IsUndefined()) {
            return ThrowException(String::New("ERROR: Cursor::New - Must provide an argument"));
        } else {
            Local<Object> editorObj = Local<Object>::Cast(args[0]);
            Cursor* curs = new Cursor(ObjectWrap::Unwrap<Editor>(editorObj));
            curs->Wrap(args.This());
            return args.This();
        }
    } else {
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Cursor::Insert(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Insert - must provide an argument")));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        /* input could be pretty big, so let's heap allocate the c++ string */
        string* input = new string(*String::Utf8Value(args[0]));
        thisCurs->insert(*input);
        delete input;
        return scope.Close(Undefined());
    }
}

Handle<Value>
Cursor::Remove(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Remove - Must provide an argument")));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int length = (int)args[0]->IntegerValue();
        thisCurs->remove(length);
        return scope.Close(Undefined());
    }
}

Handle<Value>
Cursor::Replace(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined() || args[1]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::Replace - missing or invalid arguments")));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int length = (int)args[0]->IntegerValue();
        string* replacement = new string(*String::Utf8Value(args[0]));
        thisCurs->replace(length, *replacement);
        return scope.Close(Undefined());
    }
}

Handle<Value>
Cursor::GetIndex(const Arguments& args)
{
    HandleScope scope;
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t index = thisCurs->getIndex();
    return scope.Close(Number::New(static_cast<double>(index)));
}

Handle<Value>
Cursor::GetX(const Arguments& args)
{
    HandleScope scope;
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t x = thisCurs->getX();
    return scope.Close(Number::New(static_cast<double>(x)));
}

Handle<Value>
Cursor::GetY(const Arguments& args)
{
    HandleScope scope;
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t y = thisCurs->getY();
    return scope.Close(Number::New(static_cast<double>(y)));
}

Handle<Value>
Cursor::MoveX(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::MoveX - must provide an argument")));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int offset = args[0]->IntegerValue();
        thisCurs->moveX(offset);
        return scope.Close(Undefined());
    }
}

Handle<Value>
Cursor::MoveY(const Arguments& args)
{
    HandleScope scope;
    if (args[0]->IsUndefined()) {
        return scope.Close(ThrowException(String::New("ERROR: Cursor::MoveY - must provide an argument")));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int offset = args[0]->IntegerValue();
        thisCurs->moveY(offset);
        return scope.Close(Undefined());
    }
}
