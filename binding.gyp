{
    "target_defaults": {
        "default_configuration": "Release",
        "configurations": {
            "Debug": {
                "defines": [ "DEBUG" ],
                "cflags": [ "-g" ],
            },
            "Release": {
                "defines": [ "NDEBUG" ]
            }
        }
    },
    "targets": [
        {
            "target_name": "libfleaux",
            "sources": [ "src/fleaux.cc", "src/editor.cc" ],
            "include_dirs": [ "../deps/liblfleaux/include" ],
            "cflags": [ "-std=c++11" ],
            "conditions": [
                ["OS=='linux'", {
                    "libraries": [ "../deps/libfleaux/lib/linux/libfleaux.a" ] 
                }],
                ["OS=='mac'", {
                    "xcode_settings": {
                        "OTHER_CPLUSPLUSFLAGS": [
                            "-mmacosx-version-min=10.7",
                            "-std=c++11",
                            "-stdlib=libc++",
                            "-fPIC"
                        ],
                        "OTHER_LDFLAGS": [
                            "-stdlib=libc++"
                        ],
                        "MACOSX_DEPLOYMENT_TARGET": "10.7"
                    },
                    "libraries": [ "../deps/libfleaux/lib/mac/libfleaux.a" ] 
                }],
                ["OS=='win'", {
                    "libraries": [ "../deps/libfleaux/lib/win/libfleaux.lib" ] 
                }]
            ]
        }
    ]
}
