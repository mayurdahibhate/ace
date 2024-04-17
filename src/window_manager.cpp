#include "../include/window_manager.h"

HWND _ghwnd = NULL;
DWORD _dwStyle = 0;
WINDOWPLACEMENT _wpPrev = { sizeof(WINDOWPLACEMENT) };

BOOL _gbFullscreen = FALSE;
BOOL _gbActive = FALSE;

int _gWidth = 800;
int _gHeight = 600;

// OpenGL related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// global callback declarations
InitializeCallback   _initializeCallback  = NULL;
KeyboardCallback     _keyboardCallback    = NULL;  
MouseMoveCallback    _mouseMoveCallback   = NULL; 
MouseClickCallback   _mouseClickCallback  = NULL;
DisplayCallback      _displayCallback     = NULL;   
UpdateCallback       _updateCallback      = NULL;    
ReshapeCallback      _reshapeCallback     = NULL;   
UninitializeCallback _uninitializeCallback = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		_gbActive = TRUE;
		break;
	case WM_KILLFOCUS:
		_gbActive = FALSE;
		break;
	case WM_SIZE:
        if (_reshapeCallback)
        {
		    _reshapeCallback(LOWORD(lParam), HIWORD(lParam));
        }
		break;
	case WM_ERASEBKGND:
		return(0);
	case WM_KEYDOWN:
        if(_keyboardCallback) 
		{
            _keyboardCallback(wParam);
		}
        break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'F':
		case 'f':
			if (_gbFullscreen == FALSE)
			{
				ToggleFullscreen();
				_gbFullscreen = TRUE;
			}
			else
			{
				ToggleFullscreen();
				_gbFullscreen = FALSE;
			}
			break;
		case 27:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
 
void ToggleFullscreen(void)
{
	// local variable declarations
	MONITORINFO mi = { sizeof(MONITORINFO) };

	// code
	if (_gbFullscreen == FALSE)
	{
		_dwStyle = GetWindowLong(_ghwnd, GWL_STYLE);

		if (_dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(_ghwnd, &_wpPrev) && GetMonitorInfo(MonitorFromWindow(_ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(_ghwnd, GWL_STYLE, _dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(_ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}

		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(_ghwnd, &_wpPrev);
		SetWindowLong(_ghwnd, GWL_STYLE, _dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(_ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	// code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// initialization of PI
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	// get the DC
	ghdc = GetDC(_ghwnd);
	if (ghdc == NULL)
	{
		// fprintf(gpFile, "GetDC() failed.\n");
		return(-1);
	}

	// get pixel format
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		// fprintf(gpFile, "ChoosePixelFormat() failed.\n");
		return(-2);
	}

	// set obtained pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE) {
		// fprintf(gpFile, "SetPixelFormat() failed.\n");
		return(-3);
	}

	// create OpenGL context from Device Context
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		// fprintf(gpFile, "wglCreateContext() failed.\n");
		return(-4);
	}

	// make rendering context current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		// fprintf(gpFile, "wglMakeCurrent() failed.\n");
		return(-5);
	}

    if(_initializeCallback)
    {
        _initializeCallback();
    }

	// warm up resize
    if(_reshapeCallback) 
    {
        _reshapeCallback(_gWidth, _gHeight);
	}

	return(0);
}

void acewmEventLoop()
{
    // variables
    BOOL bDone = FALSE;
    MSG msg;

    // code
    while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (_gbActive == TRUE) 
            {
                if (_updateCallback)
                    _updateCallback();
            }

            if (_displayCallback)
			{
			    _displayCallback();
			}
		}
    }    
}


void _uninitialize(void)
{
    if (_uninitializeCallback)
        _uninitializeCallback();

    	// fullscreen check
	if (_gbFullscreen == TRUE)
	{
		SetWindowLong(_ghwnd, GWL_STYLE, _dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(_ghwnd, &_wpPrev);
		SetWindowPos(_ghwnd,
			HWND_TOP,
			0,
			0,
			0,
			0,
			SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

		ShowCursor(TRUE);
	}

	// break the current context
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
	}

	if (ghdc)
	{
		ReleaseDC(_ghwnd, ghdc);
		ghdc = NULL;
	}

}

void acewmCreateWindow(const char *title, int x, int y, int width, int height)
{
    // variables 
	int iRet = 0;
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

    _gWidth = width;
    _gHeight = height;

    HINSTANCE hInstance = (HINSTANCE) GetModuleHandle(NULL);

    size_t size = strlen(title) + 1;
	TCHAR *szClassName = new TCHAR[size];
    szClassName = (TCHAR*)title;

	// code
	// TO DO : create file for logging

	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register WNDCLASSEX
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		szClassName,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - _gWidth) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _gHeight) / 2,
		_gWidth,
		_gHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	_ghwnd = hwnd;

	iRet = initialize();
	if (iRet == -1)
	{
		// fprintf(_gpFile, "ChoosePixelFormat failed...\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -2)
	{
		// fprintf(_gpFile, "SetPixelFormat failed...\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -3)
	{
		// fprintf(_gpFile, "wglCreateContext failed...\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -4)
	{
		// fprintf(_gpFile, "wglMakeCurrent failed...\n");
		DestroyWindow(hwnd);
	}
	else
	{
		// fprintf(_gpFile, "initialize() successful...\n");
	}

	// show the window
	ShowWindow(hwnd, SW_NORMAL);

	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
}

void acewmDestroyWindow(void)
{
    // 
}

void acewmFullScreen()
{
    if (!_gbFullscreen)
        ToggleFullscreen();
}

void acewmExitFullScreen()
{
    if (_gbFullscreen)
        ToggleFullscreen();
}

void acewmInitializeCallback(InitializeCallback callback)
{
    _initializeCallback = callback;
}

void acewmUninitiiizeCallback(UninitializeCallback callback)
{
    _uninitializeCallback = callback;
}


// input callbacks
void acewmKeyboardCallback(KeyboardCallback callback)
{
    _keyboardCallback = callback;
}

void acewmMouseMoveCallback(MouseMoveCallback callback)
{
    _mouseMoveCallback = callback;
}

void acewmMouseClickCallback(MouseClickCallback callback)
{
    _mouseClickCallback = callback;
}

// draw and update
void acewmDisplayCallback(DisplayCallback callback)
{
    _displayCallback = callback;
}
void acewmUpdateCallback(UpdateCallback callback)
{
    _updateCallback = callback;
}

// swap buffers
void acewmReshapeCallback(ReshapeCallback callback)
{
    _reshapeCallback = callback;
}

void acewmSwapBuffers(void)
{
    SwapBuffers(ghdc);
}
