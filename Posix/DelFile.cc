NAN_METHOD(DelFile) {
  LIBMTP_folder_t *folders;
  LIBMTP_file_t *files;
  LIBMTP_mtpdevice_t *device;

  v8::Local<v8::Object> results = Nan::New<v8::Object>();
  results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::False());

  v8::String::Utf8Value param1(info[0]->ToString());
  std::string stringParam1 = std::string(*param1);
  char *cStr1 = new char[stringParam1.length() + 1];
  strcpy(cStr1, stringParam1.c_str());

  LIBMTP_Init();
  device  = LIBMTP_Get_First_Device();
  files   = LIBMTP_Get_Filelisting_With_Callback(device, NULL, NULL);
  folders = LIBMTP_Get_Folder_List(device);

  if (device != NULL) {
    uint32_t id = parse_path(cStr1, files, folders);

    if (id > 0) {
      int ret = 1;
      ret = LIBMTP_Delete_Object(device, id);
      if (ret == 0) {
        results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::True());
      }
    }
  }

  delete [] cStr1;
  info.GetReturnValue().Set(results);
}
