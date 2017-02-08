#include <nan.h>
#include <node.h>

using namespace std;
using namespace v8;

#include "ContentEnumeration.cpp"
#include "ContentProperties.cpp"
#include "ContentTransfer.cpp"
#include "DeviceCapabilities.cpp"
#include "DeviceEnumeration.cpp"
#include "DeviceEvents.cpp"
#include "MtpLite.cpp"

NAN_METHOD(MakeArray) {
  info.GetReturnValue().Set(Nan::New<v8::Array>());
}

NAN_METHOD(Detect) {
  HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (SUCCEEDED(hr))
  {
      info.GetReturnValue().Set(DoDeviceListV8());
  }
  CoUninitialize();
}

NAN_METHOD(List) {
  HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (SUCCEEDED(hr))
  {
      info.GetReturnValue().Set(DoContentListV8());
  }
  CoUninitialize();
}

NAN_METHOD(SendFile) {
  HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (SUCCEEDED(hr))
  {
      // 100 dollarydoos for whoever can make this better
      v8::String::Utf8Value param1(info[0]->ToString());
      std::string stringParam1 = std::string(*param1);
      std::wstring wstringParam1(stringParam1.begin(), stringParam1.end());
      const wchar_t* param1_ptr = wstringParam1.c_str();
      std::vector<wchar_t> param1_buffer(param1_ptr, param1_ptr + wstringParam1.size() + 1);
      wchar_t* param1_buffer_ptr = &param1_buffer[0];

      v8::String::Utf8Value param2(info[1]->ToString());
      std::string stringParam2 = std::string(*param2);
      std::wstring wstringParam2(stringParam2.begin(), stringParam2.end());
      const wchar_t* param2_ptr = wstringParam2.c_str();
      std::vector<wchar_t> param2_buffer(param2_ptr, param2_ptr + wstringParam2.size() + 1);
      wchar_t* param2_buffer_ptr = &param2_buffer[0];

      info.GetReturnValue().Set(DoSendFileV8(param1_buffer_ptr, param2_buffer_ptr));\
  }
  CoUninitialize();
}

NAN_METHOD(GetFile) {
  HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (SUCCEEDED(hr))
  {
      // 100 dollarydoos for whoever can make this better
      v8::String::Utf8Value param1(info[0]->ToString());
      std::string stringParam1 = std::string(*param1);
      std::wstring wstringParam1(stringParam1.begin(), stringParam1.end());
      const wchar_t* param1_ptr = wstringParam1.c_str();
      std::vector<wchar_t> param1_buffer(param1_ptr, param1_ptr + wstringParam1.size() + 1);
      wchar_t* param1_buffer_ptr = &param1_buffer[0];

      info.GetReturnValue().Set(DoGetFileV8(param1_buffer_ptr));
  }
  CoUninitialize();
}

NAN_METHOD(DelFile) {
  HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (SUCCEEDED(hr))
  {
      // 100 dollarydoos for whoever can make this better
      v8::String::Utf8Value param1(info[0]->ToString());
      std::string stringParam1 = std::string(*param1);
      std::wstring wstringParam1(stringParam1.begin(), stringParam1.end());
      const wchar_t* param1_ptr = wstringParam1.c_str();
      std::vector<wchar_t> param1_buffer(param1_ptr, param1_ptr + wstringParam1.size() + 1);
      wchar_t* param1_buffer_ptr = &param1_buffer[0];

      info.GetReturnValue().Set(DoDeleteFileV8(param1_buffer_ptr));
  }
  CoUninitialize();
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, Detect);
  NAN_EXPORT(target, List);
  NAN_EXPORT(target, SendFile);
  NAN_EXPORT(target, GetFile);
  NAN_EXPORT(target, DelFile);
  NAN_EXPORT(target, MakeArray);
}

NODE_MODULE(MtpLite, Initialize)
