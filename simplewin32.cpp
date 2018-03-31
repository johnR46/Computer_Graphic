// simplewin32.cpp : Defines the entry point for the application.
//
#include <stdio.h>
#include    "simplewin32.h"
#define     MAX_LOADSTRING  100

// Global Variables:
HINSTANCE   hInst;                          // current instance
char        szTitle [MAX_LOADSTRING];       // The title bar text
char        szWindowClass [MAX_LOADSTRING]; // the main window class name

// Forward declarations of functions included in this code module:
ATOM                    RegisterMainClass (HINSTANCE hInstance);
BOOL                    InitInstance (HINSTANCE, int);
LRESULT CALLBACK        WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK        About (HWND, UINT, WPARAM, LPARAM);

HWND    hWndText;
char    szText [241];
unsigned char	*image	= NULL;			// image array
long			 bpp, cx = 0, cy = 0;	// image dimension
BITMAPINFO		 bi;

int APIENTRY _tWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPTSTR lpCmdLine,
                        int nCmdShow)
{
    MSG     msg;
    HACCEL  hAccelTable;

    // Initialize global strings
    strcpy (szTitle, "Computer Graphic 423406");
    strcpy (szWindowClass, "simplewin32");
    RegisterMainClass (hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow)) 
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators (hInstance, MAKEINTRESOURCE (IDC_SIMPLEWIN32));

    // Main message loop:
    while (GetMessage (&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM RegisterMainClass (HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;

    wcex.cbSize = sizeof (WNDCLASSEX); 

    wcex.style              = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc        = (WNDPROC)WndProc;
    wcex.cbClsExtra         = 0;
    wcex.cbWndExtra         = 0;
    wcex.hInstance          = hInstance;
    wcex.hIcon              = LoadIcon (hInstance, (LPCTSTR) IDI_SIMPLEWIN32);
    wcex.hCursor            = LoadCursor (NULL, IDC_ARROW);
    wcex.hbrBackground      = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName       = (LPCTSTR) IDC_SIMPLEWIN32;
    wcex.lpszClassName      = szWindowClass;
    wcex.hIconSm            = LoadIcon (wcex.hInstance, (LPCTSTR) IDI_SMALL);

    return RegisterClassEx (&wcex);
}

BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst   = hInstance; // Store instance handle in our global variable
    hWnd    = CreateWindow (szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                            0, 0, 640, 480, NULL, NULL, hInstance, NULL);

//    hWndText = CreateWindow ("STATIC", "0", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_RIGHT,
//               10, 10, 155, 20, hWnd, NULL, hInstance, NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    return TRUE;
}

void mydraw (HDC hdc)
{
	if (image == NULL) return;

	SetDIBitsToDevice (hdc, 0, 0, cx, cy, 0, 0, 0, cy, 
					   image, &bi, DIB_RGB_COLORS);
}

void setpixel (unsigned char *ig, int w, int x, int y, int r, int g, int b)
{
	ig [3*(x + y*w) + 0] = b;
	ig [3*(x + y*w) + 1] = g;
	ig [3*(x + y*w) + 2] = r;
}

void lineDDA (int x1, int y1, int x2, int y2)
{
	int	dx, dy, steps, k;
}

void process (unsigned char *ig, long w, long h)
{
//	int	r = 0, g = 255, b = 0;
	int x, y, k;
	
//	setpixel (ig, w, 10, 10, 255, 0, 0);
//	setpixel (ig, w, 11, 10, 255, 0, 0);
//	setpixel (ig, w, 10, 11, 255, 0, 0);
//	setpixel (ig, w, 11, 11, 255, 0, 0);


	for (y = 0; y < h; y ++)
		for (x = 0; x < w; x ++) {
			ig [3*(x + y*w) + 0] = 0;
			ig [3*(x + y*w) + 1] = x%64;
			ig [3*(x + y*w) + 2] = 0;
		}

//	lineDDA (5, 6, 120, 80);	// x1, y1, x2, y2
//	lineDDA (5, 6, 120, 80);	// x1, y1, x2, y2
}

void initfbuffer (int w, int h)
{
	bi.bmiHeader.biSize			= sizeof (BITMAPINFOHEADER);
	bi.bmiHeader.biWidth		= w;
	bi.bmiHeader.biHeight		= -h;
	bi.bmiHeader.biPlanes		= 1;
	bi.bmiHeader.biBitCount		= 24;
	bi.bmiHeader.biCompression	= BI_RGB;
	bi.bmiHeader.biSizeImage	= w*h*3;

	bi.bmiHeader.biXPelsPerMeter	= 0;
	bi.bmiHeader.biYPelsPerMeter	= 0;
	bi.bmiHeader.biClrUsed			= 0;
	bi.bmiHeader.biClrImportant		= 0;

	cx		= w;
	cy		= h;
	image	= (unsigned char *) malloc (cx*cy*3);
	memset (image, 255, w*h*3);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int         wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC         hdc;

    switch (message) 
    {
        case WM_COMMAND :   wmId    = LOWORD (wParam);
                            wmEvent = HIWORD (wParam); 

                            // Parse the menu selections:
                            switch (wmId)
                            {
                                case IDM_ABOUT  :   DialogBox (hInst, (LPCTSTR) IDD_ABOUTBOX, hWnd, (DLGPROC) About);
                                                    break;

								case IDM_EXIT   :   initfbuffer (320, 240);
													process (image, 320, 240);
													hdc = GetDC (hWnd);
													mydraw (hdc);
													ReleaseDC (hWnd, hdc);
													break;
                                                       
                                default         :   
                                                    return DefWindowProc(hWnd, message, wParam, lParam);
                            }
                            break;

		case WM_LBUTTONDOWN	:	DialogBox (hInst, (LPCTSTR) IDD_ABOUTBOX, hWnd, (DLGPROC) About);
								break;

		case WM_PAINT   :   hdc = BeginPaint (hWnd, &ps);
                            mydraw (hdc);
                            EndPaint (hWnd, &ps);
                            break;

        case WM_DESTROY :	if (image != NULL) free (image);
							PostQuitMessage (0);
                            break;

        default         :   return DefWindowProc (hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
LRESULT CALLBACK About (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG  :   return TRUE;

        case WM_COMMAND     :   if (LOWORD (wParam) == IDOK || LOWORD (wParam) == IDCANCEL)
                                {
                                    EndDialog (hDlg, LOWORD (wParam));
                                    return TRUE;
                                }
                                break;
    }
    return FALSE;
}

LRESULT CALLBACK Event (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG  :   return TRUE;

        case WM_COMMAND     :   if (LOWORD (wParam) == IDOK || LOWORD (wParam) == IDCANCEL)
                                {
                                    EndDialog (hDlg, LOWORD (wParam));
                                    return TRUE;
                                }
                                break;
    }
    return FALSE;
}

