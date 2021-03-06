static void write_storage_content(LIBMTP_file_t *file, v8::Local<v8::Object> deviceContent)
{
  v8::Local<v8::Object> item;
  item = Nan::New<v8::Object>();
  item->Set(Nan::New("OBJECT_ID").ToLocalChecked(), Nan::New(file->item_id));
  item->Set(Nan::New("OBJECT_PARENT_ID").ToLocalChecked(), Nan::New(file->parent_id));
  if (file->filename != NULL) {
    item->Set(Nan::New("OBJECT_NAME").ToLocalChecked(), Nan::New(file->filename).ToLocalChecked());
    item->Set(Nan::New("OBJECT_ORIGINAL_FILE_NAME").ToLocalChecked(), Nan::New(file->filename).ToLocalChecked());
  } else {
    item->Set(Nan::New("OBJECT_NAME").ToLocalChecked(), Nan::Null());
    item->Set(Nan::New("OBJECT_ORIGINAL_FILE_NAME").ToLocalChecked(), Nan::Null());
  }
  item->Set(Nan::New("OBJECT_CONTENT_TYPE").ToLocalChecked(), Nan::New(LIBMTP_Get_Filetype_Description(file->filetype)).ToLocalChecked());
  deviceContent->Set(Nan::New(file->item_id), item);
}

static void enumerate_files_and_write_content(LIBMTP_mtpdevice_t *device, uint32_t storageid, int leaf, v8::Local<v8::Object> deviceContent)
{
  LIBMTP_file_t *files;

  /* Get file listing. */
  files = LIBMTP_Get_Files_And_Folders(device, storageid, leaf);
  if (files != NULL) {
    LIBMTP_file_t *file, *tmp;
    file = files;
    while (file != NULL) {
	    write_storage_content(file, deviceContent);
      if (file->filetype == LIBMTP_FILETYPE_FOLDER) {
        enumerate_files_and_write_content(device, storageid, file->item_id, deviceContent);
      }
      tmp = file;
      file = file->next;
      LIBMTP_destroy_file_t(tmp);
    }
  }
}

NAN_METHOD(List) {
  v8::Local<v8::Array> deviceArray;
  deviceArray = Nan::New<v8::Array>(0);

  LIBMTP_raw_device_t *rawdevices;
  int numrawdevices;
  int i;

  LIBMTP_Init();
  LIBMTP_Detect_Raw_Devices(&rawdevices, &numrawdevices);

  /* iterate through connected MTP devices */
  for (i = 0; i < numrawdevices; i++) {
    LIBMTP_mtpdevice_t *device;
    LIBMTP_devicestorage_t *storage;
    char *modelname;

    device = LIBMTP_Open_Raw_Device_Uncached(&rawdevices[i]);
    if (device == NULL) {
      continue;
    }

    v8::Local<v8::Object> deviceContent;
    deviceContent = Nan::New<v8::Object>();

    /* Echo the friendly name so we know which device we are working with */
    modelname = LIBMTP_Get_Modelname(device);

    v8::Local<v8::Object> deviceMeta;
    deviceMeta = Nan::New<v8::Object>();

    if (modelname == NULL) {
      deviceMeta->Set(
        Nan::New("OBJECT_NAME").ToLocalChecked(),
        Nan::Null()
      );
    } else {
      deviceMeta->Set(
        Nan::New("OBJECT_NAME").ToLocalChecked(),
        Nan::New(modelname).ToLocalChecked()
      );
      free(modelname);
    }

    deviceContent->Set(
      Nan::New("DEVICE").ToLocalChecked(),
      deviceMeta
    );

    /* Loop over storages */
    for (storage = device->storage; storage != 0; storage = storage->next) {
      enumerate_files_and_write_content(device, storage->id, LIBMTP_FILES_AND_FOLDERS_ROOT, deviceContent);
    }
    deviceArray->Set(i, deviceContent);
    LIBMTP_Release_Device(device);
  }

  free(rawdevices);
  info.GetReturnValue().Set(deviceArray);
}
