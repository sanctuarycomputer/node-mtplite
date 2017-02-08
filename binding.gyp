{
  "variables": {
      'mtplite_dir%': './MtpLite'
  },
  "targets": [
    {
      "include_dirs": [
        "./MtpLite",
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "MtpLite",
      "sources": [
        "binding.cc"
      ],
      "libraries": [
        "ShlWapi.lib",
        "PortableDeviceGuids.lib"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags": [ "-std=c++11" ],
      "cflags_cc!": [ "-fno-exceptions" ]
    }
  ]
}
