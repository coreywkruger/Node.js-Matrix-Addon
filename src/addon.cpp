//#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "matrix.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  matrix::Init(exports);
}

NODE_MODULE(matrix, InitAll)