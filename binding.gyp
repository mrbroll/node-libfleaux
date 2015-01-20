{
    "target_defaults": {
        "default_configuration": "Debug",
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
            "include_dirs": [ "/home/michael/Projecs/node-libfleaux/deps/liblfleaux/include" ],
            "libraries": [ "/home/michael/Projects/node-libfleaux/deps/libfleaux/lib/libfleaux.a" ],
            "cflags": [ "-std=c++11" ]
        }
    ]
}
