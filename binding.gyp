{
  "targets": [
    {
      "target_name": "MtpLite",
      "conditions": [
        ['OS == "win"', {
          "sources": [
            "binding.cc"
          ],
          "include_dirs": [
            "./MtpLite",
            "<!(node -e \"require('nan')\")"
          ],
          "libraries": [
            "ShlWapi.lib",
            "PortableDeviceGuids.lib"
          ],
          "cflags!": [ "-fno-exceptions" ],
          "cflags": [ "-std=c++11" ],
          "cflags_cc!": [ "-fno-exceptions" ]
        }],

        ['OS == "mac"', {
          "sources": [
            "binding_mac.cc"
          ],
          "include_dirs": [
            "<!(node -e \"require('nan')\")"
          ],
        }],

        ['OS == "linux"', {

        }]
      ]
    }
  ]
}
