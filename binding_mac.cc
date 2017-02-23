#include <nan.h>
#include <node.h>

using namespace std;
using namespace v8;

NAN_METHOD(Detect) {
}

NAN_METHOD(List) {
}

NAN_METHOD(SendFile) {
}

NAN_METHOD(GetFile) {
}

NAN_METHOD(DelFile) {
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, Detect);
  NAN_EXPORT(target, List);
  NAN_EXPORT(target, SendFile);
  NAN_EXPORT(target, GetFile);
  NAN_EXPORT(target, DelFile);
}

NODE_MODULE(MtpLite, Initialize)
