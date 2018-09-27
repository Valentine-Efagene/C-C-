#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include "KeyboardTester.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char *replaceWord(const char *, const char *, const char *);
char *replaceChar(char *, char, char);
void display(char *, HWND);
char *replaceChar(char *, char);
char * str = "abcdefghijklmnopqrstuvwxyz0123456789-]\/\.[`;\'_TAB_PAGEUP_ESC_DEL_ENTER_UP_DOWN_RIGHT_LEFT_HOME_END_BACKSPACE_F1_F2_F3";

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;// | CS_VREDRAW|CS_HREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           TEXT_WIDTH + 70,                 /* The programs width */
           TEXT_HEIGHT + 80,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR ch;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            display(str, hwnd);

        case WM_CHAR:
            switch (wParam){
            case 0x5B:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x3B:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x5C:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x2F:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x2D:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x2C:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case 0x60:
                str = replaceChar(str, (char) wParam, '_');
                display(str, hwnd);
                break;
            case VK_BACK:
                str = replaceWord(str, "BACKSPACE", "_");
                display(str, hwnd);
                break;
            case VK_TAB:
                str = replaceWord(str, "TAB", "_");
                display(str, hwnd);
                break;
            case VK_MENU:
                str = replaceWord(str, "ALT", "_");
                display(str, hwnd);
                break;
            case VK_CAPITAL:
                str = replaceWord(str, "CAPSLOCK", "_");
                display(str, hwnd);
                break;
            case VK_HOME:
                str = replaceWord(str, "HOME", "_");
                display(str, hwnd);
                break;
            case VK_PRIOR:
                str = replaceWord(str, "PAGEUP", "_");
                display(str, hwnd);
                break;
            case VK_END:
                str = replaceWord(str, "END", "_");
                display(str, hwnd);
                break;
            case VK_LEFT:
                str = replaceWord(str, "LEFT", "_");
                display(str, hwnd);
                break;
            case VK_RIGHT:
                str = replaceWord(str, "RIGHT", "_");
                display(str, hwnd);
                break;
            case VK_UP:
                str = replaceWord(str, "UP", "_");
                display(str, hwnd);
                break;
            case VK_DOWN:
                str = replaceWord(str, "DOWN", "_");
                display(str, hwnd);
                break;
            case VK_DELETE:
                str = replaceWord(str, "DELETE", "_");
                display(str, hwnd);
                break;
            case VK_F1:
                str = replaceWord(str, "F1", "_");
                display(str, hwnd);
                break;
            case VK_F2:
                str = replaceWord(str, "F2", "_");
                display(str, hwnd);
                break;
            case VK_F3:
                str = replaceWord(str, "F3", "_");
                display(str, hwnd);
                break;
            case VK_F4:
                str = replaceWord(str, "F4", "_");
                display(str, hwnd);
                break;
            case VK_F5:
                str = replaceWord(str, "F5", "_");
                display(str, hwnd);
                break;
            case VK_F6:
                str = replaceWord(str, "F6", "_");
                display(str, hwnd);
                break;
            case VK_F7:
                str = replaceWord(str, "F7", "_");
                display(str, hwnd);
                break;
            default:
                if((wParam > 61 && wParam < 123) || (wParam > 47 && wParam < 58)) {
                    str = replaceChar(str, (char) wParam, '_');
                    printf("%s  %d\n", str, strlen(str));
                    display(str, hwnd);
                }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

