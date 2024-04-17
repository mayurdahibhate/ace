#ifndef __window_manager_h__
#define __window_manager_h__

#include <windows.h>
#include <stdio.h>
#include <string.h>

#define UNICODE
#define MYICON 101

typedef void (*InitializeCallback)      (void);
typedef void (*UninitializeCallback)    (void);

typedef void (*KeyboardCallback)        (unsigned int key);
typedef void (*MouseMoveCallback)       (int x, int y);
typedef void (*MouseClickCallback)      (unsigned int key, int x, int y);

typedef void (*DisplayCallback)         (void);
typedef void (*UpdateCallback)          (void);

typedef void (*ReshapeCallback)         (int width, int height);

// function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ToggleFullscreen(void);

void acewmCreateWindow(const char *title, int x, int y, int width, int height);
void acewmDestroyWindow(void);

void acewmInitializeCallback(InitializeCallback callback);
void acewmUninitiiizeCallback(UninitializeCallback callback); 

void acewmFullScreen();
void acewmExitFullScreen();

void acewmEventLoop();
void acewmExitEventLoop();

void acewmKeyboardCallback(KeyboardCallback callback);
void acewmMouseMoveCallback(MouseMoveCallback callback);
void acewmMouseClickCallback(MouseClickCallback callback);

void acewmDisplayCallback(DisplayCallback callback);
void acewmUpdateCallback(UpdateCallback callback);

void acewmReshapeCallback(ReshapeCallback callback);

void acewmSwapBuffers(void);

#endif
