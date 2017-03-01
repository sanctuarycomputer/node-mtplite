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
    LIBMTP_Release_Device(device);
  }
  free(rawdevices);
  info.GetReturnValue().Set(deviceArray);
}
