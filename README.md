# discovering_modern_cpp

// 2020-02-06

Mac의 VSC에서 cpp 실행을 위해선 Command + Shift + b 를 눌러 g++ build active file 옆의 톱니바퀴 선택
생성된 tasks.json 파일을 다음의 코드로 대체

    {
        // See https://go.microsoft.com/fwlink/?LinkId=733558 
        // for the documentation about the tasks.json format 
        "version": "2.0.0", 
        "tasks": [ 
            {
                "label": "Build with Clang",
                "type": "shell",
                "command": "clang++",
                "args": [
                "-std=c++17",
                "-stdlib=libc++",
                "${file}"
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}.out",
                "--debug"
                ],
                "group": {
                "kind": "build",
                "isDefault": true
                }
            },
            { 
                "label": "build_gcc", 
                "type": "shell", 
                "command": "gcc", 
                "args": [ 
                    "-g", 
                    "-o", 
                    "${fileDirname}/${fileBasenameNoExtension}.out", 
                    "${file}"
                ], 
                "group": { 
                    "kind": "build", 
                    "isDefault": true 
                } 
            }, 
            { 
                "label": "build_g++", 
                "type": "shell", 
                "command": "g++", 
                "args": [
                    "-g", 
                    "-o", 
                    "${fileDirname}/${fileBasenameNoExtension}.out", 
                    "${file}" 
                ], 
                "group": { 
                    "kind": "build", 
                    "isDefault": true 
                } 
            },
            { 
                "label": "exec", 
                "type": "shell", 
                "command": "${fileDirname}/${fileBasenameNoExtension}.out", 
                "group": { 
                    "kind": "build", 
                    "isDefault": true 
                } 
            }
        ] 
    }

이후 .vscode 파일 아래에 launch.json 파일 생성 후 다음 코드를 삽입

    {
        // IntelliSense를 사용하여 가능한 특성에 대해 알아보세요.
        // 기존 특성에 대한 설명을 보려면 가리킵니다.
        // 자세한 내용을 보려면 https://go.microsoft.com/fwlink/?linkid=830387을(를) 방문하세요.
        "version": "0.2.0", 
        "configurations": [ 
            { 
                "name": "(lldb) Launch", 
                "type": "cppdbg", 
                "request": "launch", 
                "program": "${fileDirname}/${fileBasenameNoExtension}.out", 
                "args": [], 
                "stopAtEntry": false, 
                "cwd": "${workspaceFolder}", 
                "environment": [], 
                "externalConsole": false, 
                "MIMode": "lldb", 
                "osx": { 
                    "MIDebuggerPath": "/Applications/Xcode.app/Contents/Developer/usr/bin/lldb-mi" 
                } 
            } 
        ]
    }

이후 Command + Shift + b 를 눌러 g++ build 후 exec (gcc는 비추...)

이렇게 작업을 했지만... C++11이 작동 안되는 부분이 있어 Clang을 도입하기로 했다.
https://code.visualstudio.com/docs/cpp/config-clang-mac 이 Visual Studio Code Docs를 보고... 도전...

git에 yuhyeon으로 등록되는 것을 수정해보자. => git config를 수정해 해결했다

다시 g++로 옮겼다 (competitive의 README 참조)
