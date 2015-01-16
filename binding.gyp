{
    "targets": [
        {
            "target_name": "libfleaux",
            "sources": [ "src/editor.cc" ],
            "conditions": [
                "OS=='Linux'",
                {
                    "libraries": [ "deps/libfleaux/lib/libfleaux.a" ],
                    "cflags": [ "-std=c++11" ]
                }
            ]
        }
    ]
}
