#include "../deps/libfleaux/include/editor.hh"
#include "editor.hh"
#include <node.h>
#include <v8.h>

using namespace v8;

Persistent<Function> Editor::constructor;

Editor::Editor(void)
{
    __Cursor = new Cursor(this);
}

Editor::~Editor(void)
{
    delete __Cursor;
}

void
Editor::Init(Handle<Object> exports)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Editor"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getCursor"),
                                    FunctionTemplate::New(GetCursor)->GetFunction());
    Editor::constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("Editor"), Editor::constructor);
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
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
Editor::GetCursor(const Arguments& args)
{
    HandleScope scope;
    Editor* thisEd = ObjectWrap::Unwrap<Editor>(args.This());
    Local<Object> cursObj = Object::New();
    thisEd->__Cursor->Wrap(cursObj);
    return scope.Close(cursObj);
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
    tpl->PrototypeTemplate()->Set(   String::NewSymbol("remove"),
                                    FunctionTemplate::New(Remove)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getIndex"),
                                    FunctionTemplate::New(GetIndex)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("getX"),
                                    FunctionTemplate::New(GetX)->GetFunction());
    tpl->PrototypeTemplate()->Set(   String::NewSymbol("getY"),
                                    FunctionTemplate::New(GetY)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveH"),
                                    FunctionTemplate::New(MoveH)->GetFunction());
    tpl->PrototypeTemplate()->Set(  String::NewSymbol("moveV"),
                                    FunctionTemplate::New(MoveV)->GetFunction());
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
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: Cursor::Insert - must provide an argument"));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        /* input could be pretty big, so let's heap allocate the c++ string */
        string* input = new string(*String::Utf8Value(args[0]));
        thisCurs->insert(*input);
        delete input;
        return Undefined();
    }
}

Handle<Value>
Cursor::Remove(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: Cursor::Remove - Must provide an argument"));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int length = (int)args[0]->IntegerValue();
        thisCurs->remove(length);
        return Undefined();
    }
}

Handle<Value>
Cursor::GetIndex(const Arguments& args)
{
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t index = thisCurs->getIndex();
    return Number::New(static_cast<double>(index));
}

Handle<Value>
Cursor::GetX(const Arguments& args)
{
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t x = thisCurs->getX();
    return Number::New(static_cast<double>(x));
}

Handle<Value>
Cursor::GetY(const Arguments& args)
{
    Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
    size_t y = thisCurs->getY();
    return Number::New(static_cast<double>(y));
}

Handle<Value>
Cursor::MoveH(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: Cursor::MoveH - must provide an argument"));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int offset = args[0]->IntegerValue();
        thisCurs->moveH(offset);
        return Undefined();
    }
}

Handle<Value>
Cursor::MoveV(const Arguments& args)
{
    if (args[0]->IsUndefined()) {
        return ThrowException(String::New("ERROR: Cursor::MoveV - must provide an argument"));
    } else {
        Cursor* thisCurs = ObjectWrap::Unwrap<Cursor>(args.This());
        int offset = args[0]->IntegerValue();
        thisCurs->moveV(offset);
        return Undefined();
    }
}
