#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
// May not be necessary, leaving here for Mac incase...
#include "./Utils/util.cc"

NAN_METHOD(SendFile) {
  LIBMTP_folder_t *folders;
  LIBMTP_file_t *files;
  LIBMTP_mtpdevice_t *device;

  v8::Local<v8::Object> results = Nan::New<v8::Object>();
  results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::False());

  v8::String::Utf8Value param1(info[0]->ToString());
  std::string stringParam1 = std::string(*param1);
  char *from_path = new char[stringParam1.length() + 1];
  strcpy(from_path, stringParam1.c_str());

  v8::String::Utf8Value param2(info[1]->ToString());
  std::string stringParam2 = std::string(*param2);
  char *to_path= new char[stringParam2.length() + 1];
  strcpy(to_path, stringParam2.c_str());

  LIBMTP_Init();
  device  = LIBMTP_Get_First_Device();
  files   = LIBMTP_Get_Filelisting_With_Callback(device, NULL, NULL);
  folders = LIBMTP_Get_Folder_List(device);

  if (device != NULL) {
    char *filename;
    uint64_t filesize;
    struct stat sb;
    LIBMTP_file_t *genfile;
    int ret;
    uint32_t parent_id = 0;

    if ( stat(from_path, &sb) != -1 ) {
      filesize = sb.st_size;
      filename = basename(from_path);
      parent_id = parse_path(to_path, files, folders);
      if (parent_id == -1) {
        printf("Parent folder could not be found, skipping\n");
        // SUCCESS
      } else {
        printf("Found parent\n");
      }

      genfile = LIBMTP_new_file_t();
      genfile->filesize = filesize;
      genfile->filename = strdup(filename);
      genfile->filetype = find_filetype (filename);
      genfile->parent_id = parent_id;
      genfile->storage_id = 0;

      if (LIBMTP_Send_File_From_File(device, from_path, genfile, progress, NULL) == 0) {
        results->Set(Nan::New("didSucceed").ToLocalChecked(), Nan::True());
        results->Set(Nan::New("newObjectId").ToLocalChecked(), Nan::New(genfile->item_id));
      }
      printf("Got hereg\n");

      LIBMTP_destroy_file_t(genfile);
    }
    LIBMTP_Release_Device(device);
  }

  delete [] from_path;
  delete [] to_path;
  info.GetReturnValue().Set(results);
}
