CLS
cl.exe /c /EHsc /I "D:\\code\\glew-2.1.0\\include" /I "D:\\code\\mini-demos\\supershapes\\include" main.cpp src/LoadShaders.cpp src/window_manager.cpp
rc.exe res/OGL.rc
link.exe /OUT:OGL.exe main.obj window_manager.obj LoadShaders.obj OGL.res user32.lib GDI32.lib /LIBPATH:"D:\\code\\glew-2.1.0\\lib\\Release\\x64"
del *.obj
