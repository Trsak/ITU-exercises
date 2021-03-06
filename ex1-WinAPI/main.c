#include <windows.h>
#include <string.h>
#include <stdio.h>


// Global variable
HINSTANCE hInst;
UINT MessageCount = 0;
UINT Count = 0;

// Function prototypes.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void onPaint(HWND hWnd);


// Application entry point. This is the same as main() in standart C.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	WNDCLASS wcx;          // register class
	HWND hWnd;

	hInst = hInstance;     // Save the application-instance handle.
		// Fill in the window class structure with parameters that describe the main window.

	wcx.style = CS_HREDRAW | CS_VREDRAW;              // redraw if size changes
	wcx.lpfnWndProc = (WNDPROC)MainWndProc;                    // points to window procedure
	wcx.cbClsExtra = 0;                               // no extra class memory
	wcx.cbWndExtra = 0;                               // no extra window memory
	wcx.hInstance = hInstance;                        // handle to instance
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);      // predefined app. icon
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);                                   // predefined arrow
	wcx.hbrBackground = GetStockObject(WHITE_BRUSH);  // white background brush
	wcx.lpszMenuName = (LPCSTR) "MainMenu";                   // name of menu resource
	wcx.lpszClassName = (LPCSTR) "MainWClass";                 // name of window class

	// Register the window class.

	if (!RegisterClass(&wcx)) return FALSE;

	// create window of registered class

	hWnd = CreateWindow(
		"MainWClass",        // name of window class
		"ITU",       // title-bar string
		WS_OVERLAPPEDWINDOW, // top-level window
		GetSystemMetrics(SM_CXSCREEN) / 2 - 320,                  // default horizontal position
		GetSystemMetrics(SM_CYSCREEN) / 2 - 240,                 // default vertical position
		640,                 // default width
		480,                 // default height
		(HWND)NULL,         // no owner window
		(HMENU)NULL,        // use class menu
		hInstance,           // handle to application instance
		(LPVOID)NULL);      // no window-creation data
	if (!hWnd) return FALSE;

	// Show the window and send a WM_PAINT message to the window procedure.
	// Record the current cursor position.

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// loop of message processing

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

// **************************************************************** //
LRESULT CALLBACK MainWndProc(
	HWND hWnd,        // handle to window
	UINT uMsg,        // message identifier
	WPARAM wParam,    // first message parameter
	LPARAM lParam)    // second message parameter
{
	++MessageCount;
	InvalidateRect(hWnd, NULL, 0);

	switch (uMsg)
	{
	case WM_CREATE:
		// Initialize the window.
		return 0;

	case WM_SIZE:
		// Set the size and position of the window.
		return 0;

	case WM_DESTROY:
		// Clean up window-specific data objects.
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		// Paint the window's client area.
		onPaint(hWnd);

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

void onPaint(HWND hWnd)
{
	PAINTSTRUCT ps;                 // information can be used to paint the client area of a window owned by that application
	HDC         hDC;                // device context
	HBRUSH      brush;
	HPEN        Pen;


	hDC = BeginPaint(hWnd, &ps);    // prepares the specified window for 

	//Legs
	Pen = CreatePen(PS_SOLID, 10, RGB(0, 153, 153));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(0, 153, 153));
	//Left leg
	MoveToEx(hDC, 270, 250, NULL);
	LineTo(hDC, 250, 290);
	//Right leg
	MoveToEx(hDC, 270, 250, NULL);
	LineTo(hDC, 290, 290);

	//Arms
	Pen = CreatePen(PS_SOLID, 10, RGB(0, 153, 153));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(0, 153, 153));
	//Left arm
	MoveToEx(hDC, 260, 210, NULL);
	LineTo(hDC, 250, 230);
	//Right arm
	MoveToEx(hDC, 280, 210, NULL);
	LineTo(hDC, 290, 230);

	//Body
	Pen = CreatePen(PS_SOLID, 1, RGB(0, 102, 204));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(0, 102, 204));
	SelectObject(hDC, brush);
	Rectangle(hDC, 260, 200, 280, 260);

	//Head
	Pen = CreatePen(PS_SOLID, 1, RGB(255, 153, 0));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(255, 153, 0));
	SelectObject(hDC, brush);
	Ellipse(hDC, 240, 140, 300, 200);

	//Mouth
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hDC, brush);
	MoveToEx(hDC, 260, 180, NULL);
	LineTo(hDC, 280, 180);

	//Eyes
	Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hDC, brush);
	//Left eye
	Ellipse(hDC, 250, 150, 270, 170);
	//Right eye
	Ellipse(hDC, 270, 150, 290, 170);

	//Lens
	Pen = CreatePen(PS_SOLID, 1, RGB(198, 140, 83));
	SelectObject(hDC, Pen);
	brush = CreateSolidBrush(RGB(198, 140, 83));
	SelectObject(hDC, brush);
	//Left len
	Ellipse(hDC, 258, 158, 263, 163);
	//Right len
	Ellipse(hDC, 278, 158, 283, 163);

	DeleteDC(hDC);                  // deletes the specified device context
	EndPaint(hWnd, &ps);            // marks the end of painting in the specified window
}
