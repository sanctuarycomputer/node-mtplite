NAN_METHOD(GetFile) {
  LIBMTP_folder_t *folders;
  LIBMTP_file_t *files;
  LIBMTP_mtpdevice_t *device;

  v8::Local<v8::Object> results = Nan::New<v8::Object>();
  results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::False());

  v8::String::Utf8Value param1(info[0]->ToString());
  std::string stringParam1 = std::string(*param1);
  char *cStr1 = new char[stringParam1.length() + 1];
  strcpy(cStr1, stringParam1.c_str());

  v8::String::Utf8Value param2(info[1]->ToString());
  std::string stringParam2 = std::string(*param2);
  char *cStr2 = new char[stringParam2.length() + 1];
  strcpy(cStr2, stringParam2.c_str());

  LIBMTP_Init();
  device  = LIBMTP_Get_First_Device();
  files   = LIBMTP_Get_Filelisting_With_Callback (device, NULL, NULL);
  folders = LIBMTP_Get_Folder_List (device);

  if (device != NULL) {
    int id = parse_path(cStr1, files, folders);
    if (LIBMTP_Get_File_To_File(device, id, cStr2, progress, NULL) != 0 ) {
      results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::False());
    } else {
      results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::True());
      results->Set(Nan::New("file").ToLocalChecked(), Nan::New(cStr2).ToLocalChecked());
    }

    LIBMTP_Release_Device(device);
  }

  delete [] cStr1;
  delete [] cStr2;
  info.GetReturnValue().Set(results);
}

