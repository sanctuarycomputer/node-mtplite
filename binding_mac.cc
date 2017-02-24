#include <nan.h>
#include <node.h>

using namespace std;
using namespace v8;

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <libmtp.h>

#define XML_BUFSIZE 0x10000

using namespace std;
using namespace v8;

NAN_METHOD(Detect) {
  LIBMTP_raw_device_t * rawdevices;
  int numrawdevices;
  LIBMTP_error_number_t err;
  int i;
  v8::Local<v8::Array> deviceArray;

  LIBMTP_Init();
  err = LIBMTP_Detect_Raw_Devices(&rawdevices, &numrawdevices);
  deviceArray = Nan::New<v8::Array>(numrawdevices);

  for (i = 0; i < numrawdevices; i++) {
    LIBMTP_mtpdevice_t *device;
    char *friendlyname;
    char *manufacturername;
    char *modelname;

    device = LIBMTP_Open_Raw_Device_Uncached(&rawdevices[i]);
    if (device == NULL) {
      continue;
    }

    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    friendlyname = LIBMTP_Get_Friendlyname(device);
    if (friendlyname == NULL) {
      obj->Set(Nan::New("friendlyName").ToLocalChecked(), Nan::Null());
    } else {
      obj->Set(Nan::New("friendlyName").ToLocalChecked(), Nan::New(friendlyname).ToLocalChecked());
      free(friendlyname);
    }

    manufacturername = LIBMTP_Get_Manufacturername(device);
    if (manufacturername == NULL) {
      obj->Set(Nan::New("manufacturer").ToLocalChecked(), Nan::Null());
    } else {
      obj->Set(Nan::New("manufacturer").ToLocalChecked(), Nan::New(manufacturername).ToLocalChecked());
      free(manufacturername);
    }

    modelname = LIBMTP_Get_Modelname(device);
    if (modelname == NULL) {
      obj->Set(Nan::New("description").ToLocalChecked(), Nan::Null());
    } else {
      obj->Set(Nan::New("description").ToLocalChecked(), Nan::New(modelname).ToLocalChecked());
      free(modelname);
    }
    deviceArray->Set(i, obj);
  }
  free(rawdevices);
  info.GetReturnValue().Set(deviceArray);
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
