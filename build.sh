g++ -c -o app.o -I /usr/include/ -I./include/ main.cpp
g++ -c -o LoadShaders.o -I /usr/include/ -I./include/ src/LoadShaders.cpp
g++ -c -o window_manager.o  -I /usr/include/ -I./include/ src/window_manager.cpp
g++ -c -o mesh.o  -I /usr/include/ -I./include/ src/mesh.cpp
 
g++ -o app -L/usr/lib/x86_64-linux-gnu app.o LoadShaders.o window_manager.o mesh.o -L ./src/ -lX11 -lGL -lGLEW
