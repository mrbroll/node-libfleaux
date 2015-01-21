#ifndef NODE_FLEAUX_EDITOR_HH_
#define NODE_FLEAUX_EDITOR_HH_

#include "../deps/libfleaux/include/editor.hh"
#include <node.h>
#include <string>

using namespace v8;

class Cursor;

class Editor : public Fleaux::Editor, public node::ObjectWrap
{
    public:
        static void Init(Handle<Object> exports);

    private:
        Editor(void) : Fleaux::Editor() {};
        Editor(const string& path) : Fleaux::Editor(path) {};
        ~Editor(void) {};

        static Handle<Value> New(const Arguments& args);
        static Persistent<Function> constructor;

        static Handle<Value> ToString(const Arguments& args);
};


class Cursor : public Fleaux::Cursor, public node::ObjectWrap
{
    public:
        static void Init(Handle<Object> exports);

    private:
        explicit Cursor(Editor* ed) : Fleaux::Cursor(ed) {};
        ~Cursor(void) {};

        static Handle<Value> New(const Arguments& args);
        static Persistent<Function> constructor;

        static Handle<Value> Insert(const Arguments& args);
        static Handle<Value> Remove(const Arguments& args);
        static Handle<Value> Replace(const Arguments& args);
        static Handle<Value> GetIndex(const Arguments& args);
        static Handle<Value> GetX(const Arguments& args);
        static Handle<Value> GetY(const Arguments& args);
        static Handle<Value> MoveX(const Arguments& args);
        static Handle<Value> MoveY(const Arguments& args);
};

#endif
