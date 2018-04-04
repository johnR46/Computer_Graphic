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



void lineDDA (int x1, int y1, int x2, int y2)
{
	int	dx, dy, steps, k;
}
void setpixel(unsigned char *ig, int w, int x, int y, int r, int g, int b)
{
	ig[3 * (x + y * w) + 0] = b;
	ig[3 * (x + y * w) + 1] = g;
	ig[3 * (x + y * w) + 2] = r;
}

void process (unsigned char *ig, long w, long h)
{
//	int	r = 0, g = 255, b = 0;
	int x, y, k;
	
//	setpixel (ig, w, 10, 10, 255, 0, 0);
//	setpixel (ig, w, 11, 10, 255, 0, 0);
//	setpixel (ig, w, 10, 11, 255, 0, 0);
//	setpixel (ig, w, 11, 11, 255, 0, 0);



	// y = h
	// x = w 

	// x = 360
	// y = 240

	for (y = 0; y < h; y ++)
	for (x = 0; x < w; x ++) {
			setpixel(ig, w, x, y, 255, 255, 255);	
		}

	for (y = 0; y < 10; y++)
		for (x = 120; x < 200; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}

	for (y = 10; y < 30; y++)
		for (x = 70; x < 120; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	
	for (y = 10; y < 70; y++)
		for (x = 120; x < 200; x++) {
			setpixel(ig, w, x, y, 0, 180, 200);
		}

	for (y = 10; y < 30; y++)
		for (x = 200; x < 250; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}

	for (y = 30; y < 50; y++)
		for (x = 70; x < 120; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 30; y < 50; y++)
		for (x = 200; x <250; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 50; y < 70; y++)
		for (x = 200; x <270; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 50; y < 70; y++)
		for (x = 50; x < 120; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 30; y < 50; y++)
		for (x =50 ; x <70; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 30; y < 50; y++)
		for (x =50 ; x <70; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 30; y < 50; y++)
		for (x = 250; x <270; x++) {
				setpixel(ig, w, x, y, 0, 0, 0);
			}
	for (y = 50; y < 70; y++)
		for (x = 30; x <50; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 50; y < 70; y++)
		for (x = 270; x <290; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 70; y < 90; y++)
		for (x = 10; x <30; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 70; y < 90; y++)
		for (x = 290; x <310; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 90; y < 110; y++)
		for (x = 10; x <30; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 90; y < 110; y++)
		for (x = 290; x <310; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 70; y < 90; y++)
		for (x = 30; x <120; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 70; y < 90; y++)
		for (x = 200; x <290; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 90; y < 110; y++)
		for (x = 30; x <120; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 90; y < 110; y++)
		for (x = 200; x <290; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 70; y < 90; y++)
		for (x = 120; x <200; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 90; y < 110; y++)
		for (x = 120; x <200; x++) {
			setpixel(ig, w, x, y, 0, 180, 200);
		}
	for (y = 110; y < 190; y++)
		for (x = 0; x <15; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 190; y++)
		for (x = 305; x <320; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 130; y++)
		for (x = 100; x <220; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 130; y < 150; y++)
		for (x = 120; x <200; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 150; y < 180; y++)
		for (x = 80; x <120; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 150; y < 180; y++)
		for (x = 200; x <240; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 210; y++)
		for (x = 30; x <45; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 210; y++)
		for (x = 275; x <290; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 190; y < 220; y++)
		for (x = 80; x <240; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 220; y < 230; y++)
		for (x = 100; x <220; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 210; y++)
		for (x = 30; x <45; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 180; y < 200; y++)
		for (x = 290; x <310; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 180; y < 200; y++)
		for (x = 15; x <30; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 250; y < 265; y++)
		for (x = 90; x <230; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 200; y < 220; y++)
		for (x = 30; x <45; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 200; y < 220; y++)
		for (x = 275; x <290; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}

	for (y = 220; y < 235; y++)
		for (x = 260; x <275; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 220; y < 235; y++)
		for (x = 45; x <60; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 235; y < 250; y++)
		for (x = 245; x <260; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 235; y < 250; y++)
		for (x = 60; x <75; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	
	for (y = 250; y < 260; y++)
		for (x = 230; x <245; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 250; y < 260; y++)
		for (x = 75; x <90; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 260; y < 265; y++)
		for (x = 215; x <230; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 260; y < 265; y++)
		for (x = 90; x <105; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 130; y++)
		for (x = 250; x <275; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 130; y++)
		for (x = 45; x <70; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 0; y < 110; y++)
		for (x = 120; x <130; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 0; y < 110; y++)
		for (x = 190; x <200; x++) {
			setpixel(ig, w, x, y, 0, 0, 0);
		}
	for (y = 110; y < 180; y++)
		for (x = 15; x <30; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	for (y = 110; y < 180; y++)
		for (x = 290; x <305; x++) {
			setpixel(ig, w, x, y, 0, 0, 200);
		}
	
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

								case IDM_EXIT   :   initfbuffer (320, 280);
													process (image, 320, 280);
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

