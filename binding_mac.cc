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
#define LIBMTP_FILES_AND_FOLDERS_ROOT 0xffffffff

#include "./Posix/Utils/pathutils.cc"
#include "./Posix/Detect.cc"
#include "./Posix/List.cc"
#include "./Posix/SendFile.cc"
#include "./Posix/GetFile.cc"
#include "./Posix/DelFile.cc"

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, Detect);
  NAN_EXPORT(target, List);
  NAN_EXPORT(target, SendFile);
  NAN_EXPORT(target, GetFile);
  NAN_EXPORT(target, DelFile);
}

NODE_MODULE(MtpLite, Initialize)
