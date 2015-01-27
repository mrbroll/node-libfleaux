#include "editor.hh"
#include <node.h>
#include <v8.h>

using namespace v8;

void InitAll(Handle<Object> exports) {
    Fleaux::Node::Editor::Init(exports);
    Fleaux::Node::Cursor::Init(exports);
}

NODE_MODULE(fleaux, InitAll)
