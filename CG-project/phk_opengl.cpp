#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "phk_opengl.h"

#define clamp(x) x = x > 360.0f ? x-360.0f : x < -360.0f ? x+=360.0f : x

LRESULT CALLBACK /*_export*/ phkOpenGLDefWndProc (HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

static char lpszphkOpenGLengine [] = "PHK_OPENGL_WRAPPER";

phkOpenGLengine::phkOpenGLengine ()
{
    m_hWnd      = NULL;
    m_hParent   = NULL;
    m_nId       = 0;
    m_nDrag     = 0;
    m_atom      = 0;

    m_hDC       = NULL;
    m_hRC       = NULL;

    m_px        = 0.0f;
    m_py        = 0.0f;

    m_rot [0]   = 0.0f;
    m_rot [1]   = 0.0f;

    m_nmesh     = 0;

    m_fDir      = 1.0f;

	m_isanimate	= 0;
}

void phkOpenGLengine::purge (void)
{
    long    i;
    
    for (i = 0; i < MAX_SURFACES; i ++)
    {
        if (m_nListCreated [i]) ::glDeleteLists (i + 1, 1);
        m_nListCreated [i]  = 0;
    }

    if (m_hRC)
    {
        wglMakeCurrent (NULL, NULL);
        wglDeleteContext (m_hRC);
    }
    if (m_hWnd && m_hDC)
    {
        ReleaseDC (m_hWnd, m_hDC);
    }

    m_hDC           = NULL;
    m_hRC           = NULL;

//   MessageBox (NULL, "OpenGL context is succesfully cleaned", "Exit OpenGL", MB_OK);
}

phkOpenGLengine::~phkOpenGLengine ()
{
    if (m_hWnd) DestroyWindow (m_hWnd);

    m_hWnd      = NULL;
    m_hParent   = NULL;
    m_nId       = 0;
    m_atom      = 0;
}

void phkOpenGLengine::registerClass (HINSTANCE hInst)
{
   WNDCLASS     wndclass;

    if (!GetClassInfo (hInst, lpszphkOpenGLengine, &wndclass))
   {
        wndclass.style         = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc   = (WNDPROC) ::phkOpenGLDefWndProc;
        wndclass.cbClsExtra    = 0;
        wndclass.cbWndExtra    = sizeof (phkOpenGLengine *);
        wndclass.hInstance     = hInst;
        wndclass.hIcon         = NULL;
        wndclass.hCursor       = LoadCursor (NULL, IDC_CROSS);
        wndclass.hbrBackground = (HBRUSH) 0;
        wndclass.lpszMenuName  = NULL;
        wndclass.lpszClassName = lpszphkOpenGLengine;

        m_atom = RegisterClass (&wndclass);
   }
}

void phkOpenGLengine::unregisterClass (HINSTANCE hInst)
{
    WNDCLASS     wndclass;

    if (GetClassInfo (hInst, lpszphkOpenGLengine, &wndclass))
    UnregisterClass (lpszphkOpenGLengine, hInst);
}

void phkOpenGLengine::Create (HWND hwndParent, int id, LPRECT rc)
{
    m_hWnd  = CreateWindow (lpszphkOpenGLengine, NULL,
                            WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                            rc->left, rc->top, rc->right, rc->bottom,
                            hwndParent, (HMENU) id, NULL, this);
    m_nId       = id;
    m_hParent   = hwndParent;

    initopengl ();
}


void phkOpenGLengine::resize (int cx, int cy)
{
    ::glMatrixMode (GL_PROJECTION);
    ::glLoadIdentity ();

    ::gluPerspective (30.0, (float) cx/cy, 0.001, 40.0);
    ::glViewport (0, 0, cx, cy);

    ::glMatrixMode (GL_MODELVIEW);
    ::glLoadIdentity ();

	::glEnable (GL_DEPTH_TEST);
    ::glDepthFunc (GL_LESS);
}



void phkOpenGLengine::drawaxes (void)
{
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
									  // Top face (y = 1.0f)
									  // Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube

}

void phkOpenGLengine::mouse_update (float cx, float cy)
{
    m_rot [0] += ((cy - m_py) * 0.1f);
    m_rot [1] -= ((cx - m_px) * 0.1f);

    m_px = cx;
    m_py = cy;

    clamp (m_rot[0]);
    clamp (m_rot[1]);
}

void phkOpenGLengine::recoverRigidDisplay (void)
{
    ::glTranslatef (-0.5f, -0.5f, -3.00f);
    ::glRotatef (m_rot [0], 1.0f, 0.0f, 0.0f);
    ::glRotatef (m_rot [1], 0.0f, 1.0f, 0.0f);
}

void phkOpenGLengine::display (void)
{
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glPushMatrix ();

    recoverRigidDisplay ();

	drawaxes ();

    ::glFlush();
    ::glPopMatrix ();

    ::SwapBuffers (m_hDC);          /* nop if singlebuffered */
}

void phkOpenGLengine::initopengl (void)
{
    PIXELFORMATDESCRIPTOR   pfd;
    int                     format;
    RECT                    rcclient;

    m_hDC   =   GetDC (m_hWnd);

    // set the pixel format for the DC
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize       = sizeof (pfd);
    pfd.nVersion    = 1;
    pfd.dwFlags     = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType  = PFD_TYPE_RGBA;
    pfd.cColorBits  = 16;
    pfd.cDepthBits  = 32;
    pfd.iLayerType  = PFD_MAIN_PLANE;

    format = ChoosePixelFormat (m_hDC, &pfd);
    SetPixelFormat (m_hDC, format, &pfd);

    // create the render context (RC)
    m_hRC = wglCreateContext (m_hDC);

    // make it the current render context
    wglMakeCurrent (m_hDC, m_hRC);

    GetClientRect (m_hWnd, &rcclient);

//  ::glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
    resize (rcclient.right, rcclient.bottom);
    initlighting ();
}

void phkOpenGLengine::initlighting (void)
{
    //  initalize light
    GLfloat ambient [4]     = {  0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse [4]     = {  0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat position0 []    = { -0.2f, 0.5f, +5.0f, 0.0f };
    GLfloat position1 []    = { -0.2f, 0.5f, -5.0f, 0.0f };

    GLfloat materialShininess [1]   = { 8.0f };

    // enable all the lighting & depth effects
    ::glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);
    ::glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    ::glLightfv (GL_LIGHT0, GL_POSITION, position0);

    ::glLightfv (GL_LIGHT1, GL_AMBIENT, ambient);
    ::glLightfv (GL_LIGHT1, GL_DIFFUSE, diffuse);
    ::glLightfv (GL_LIGHT1, GL_POSITION, position1);

    ::glShadeModel (GL_FLAT);
    ::glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    ::glEnable (GL_LIGHTING);
    ::glEnable (GL_LIGHT0);
    ::glEnable (GL_LIGHT1);

    ::glEnable (GL_BLEND);
    ::glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ::glEnable (GL_LINE_SMOOTH);
}

void phkOpenGLengine::getscreenshot (unsigned char *lpimage, int cX, int cY)
{
    ::glReadPixels (0, 0, cX, cY, GL_RGB, GL_UNSIGNED_BYTE, lpimage);
}

LRESULT phkOpenGLengine::WndProc (UINT iMessage, WPARAM wParam, LPARAM lParam)
{
//  static PAINTSTRUCT ps;

    switch (iMessage)
    {
        case WM_CREATE      :
                                break;

		case WM_TIMER		:	if (m_isanimate)
								{
									m_rot [0] += 1.0f*(rand ()/RAND_MAX) - 0.5f;
									m_rot [1] -= 1.0f*(rand ()/RAND_MAX) - 0.5f;

									clamp (m_rot[0]);
									clamp (m_rot[1]);
									display ();
								}
								break;

        case WM_PAINT       :   display ();
                                break;

        case WM_SIZE        :   resize (LOWORD(lParam), HIWORD(lParam));
                                PostMessage (m_hWnd, WM_PAINT, 0, 0);
                                break;

        case WM_LBUTTONDOWN :   SetCapture (m_hWnd);
                                m_px    =   (float) LOWORD (lParam);
                                m_py    =   (float) HIWORD (lParam);
                                m_nDrag = 1;
                                break;

        case WM_LBUTTONUP   :   ReleaseCapture ();
                                m_px    = 0.0f;
                                m_py    = 0.0f;
                                m_nDrag = 0;
                                break;

        case WM_MOUSEMOVE   :   if (m_nDrag)
                                {
                                    int mx, my;

                                    mx = LOWORD (lParam);
                                    my = HIWORD (lParam);

                                    if (mx & (1 << 15)) mx -= (1 << 16);
                                    if (my & (1 << 15)) my -= (1 << 16);

                                    mouse_update ((float) mx, (float) my);
                                    display ();
                                }
                                break;

        case WM_DESTROY     :   purge ();
                                break;
        default             :
            return DefWindowProc (m_hWnd, iMessage, wParam, lParam);
    }

    return 0;
}

// If data pointers are near pointers
#if defined(__SMALL__) || defined(__MEDIUM__)
inline phkOpenGLengine *GetPointer (HWND hWnd)
{
    return (phkOpenGLengine *) GetWindowWord (hWnd, 0);
}
inline void SetPointer (HWND hWnd, phkOpenGLengine *pOpenGL)
{
    SetWindowWord (hWnd, 0, (WORD) pOpenGL );
}

// else pointers are far
#elif defined(__LARGE__) || defined(__COMPACT__) || defined(__FLAT__)
inline phkOpenGLengine *GetPointer (HWND hWnd)
{
    return (phkOpenGLengine *) GetWindowLong (hWnd, 0);
}

inline void SetPointer (HWND hWnd, phkOpenGLengine *pOpenGL)
{
    SetWindowLong (hWnd, 0, (LONG) pOpenGL);
}

//#else
////    #error Choose another memory model!
#endif

LRESULT FAR PASCAL /*_export*/ phkOpenGLDefWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    phkOpenGLengine *pOpenGL = GetPointer (hwnd);

    switch (message)
    {
        case WM_CREATE  :   if (!pOpenGL)
                            {
                                LPCREATESTRUCT lpcs;

                                lpcs        = (LPCREATESTRUCT) lParam;
                                pOpenGL = (phkOpenGLengine *) lpcs->lpCreateParams;

                                // Store a pointer to this object in the window's extra bytes;
                                // this will enable us to access this object (and its member
                                // functions) in WndProc where we are
                                // given only a handle to identify the window.
                                SetPointer (hwnd, pOpenGL);
                                // Now let the object perform whatever
                                // initialization it needs for WM_CREATE in its own
                                // WndProc.
                                return pOpenGL->WndProc (message, wParam, lParam);
                            }
                            break;

        default         :   if (pOpenGL) pOpenGL->WndProc (message, wParam, lParam);
                            break;
   }

   return DefWindowProc (hwnd, message, wParam, lParam);
}

