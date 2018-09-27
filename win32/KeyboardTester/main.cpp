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
char * str1 = "abcdefghijklmnopqrstuvwxyz0123456789-]\/\.[`;\'";
char * str2 = " TAB_PAGEUP_PAGEDOWN_ESC_DELETE_ENTER_UP_DOWN_RIGHT_LEFT_HOME_END BACKSPACE_PRINTSCREEN_INSERT_LWIN_SHIFT_CTRL F1_F2_F3_F4_F5_F6_F7_F8_F9_F10_F11_F12";

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
           _T("KEYBOARD TESTER"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           TEXT_WIDTH + 35,                 /* The programs width */
           TEXT1_POS_Y + TEXT_HEIGHT_1 + TEXT_HEIGHT_2 + 100,                 /* and height in pixels */
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
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            display(str1, hwnd);
            display2(str2, hwnd);

        case WM_KEYDOWN:
            printf("%c", (char)wParam);
            switch (wParam)
            {
                case VK_LEFT:
                    str2 = replaceWord(str2, "LEFT", "_");
                    display2(str2, hwnd);
                    break;

                case VK_RIGHT:
                    str2 = replaceWord(str2, "RIGHT", "_");
                    display2(str2, hwnd);
                    break;

                case VK_UP:
                    str2 = replaceWord(str2, "UP", "_");
                    display2(str2, hwnd);
                    break;

                case VK_DOWN:
                    str2 = replaceWord(str2, "DOWN", "_");
                    display2(str2, hwnd);
                    break;

                case VK_HOME:
                    str2 = replaceWord(str2, "HOME", "_");
                    display2(str2, hwnd);
                    break;

                case VK_END:
                    str2 = replaceWord(str2, "END", "_");
                    display2(str2, hwnd);
                    break;

                case VK_INSERT:
                    str2 = replaceWord(str2, "INSERT", "_");
                    display2(str2, hwnd);
                    break;

                case VK_DELETE:
                    str2 = replaceWord(str2, "DELETE", "_");
                    display2(str2, hwnd);
                    break;

                case VK_RETURN:
                    str2 = replaceWord(str2, "ENTER", "_");
                    display2(str2, hwnd);
                    break;

                case VK_ESCAPE:
                    str2 = replaceWord(str2, "ESC", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F1:
                    str2 = replaceWord(str2, "F1", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F2:
                    str2 = replaceWord(str2, "F2", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F3:
                    str2 = replaceWord(str2, "F3", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F4:
                    str2 = replaceWord(str2, "F4", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F5:
                    str2 = replaceWord(str2, "F5", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F6:
                    str2 = replaceWord(str2, "F6", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F7:
                    str2 = replaceWord(str2, "F7", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F8:
                    str2 = replaceWord(str2, "F8", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F9:
                    str2 = replaceWord(str2, "F9", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F10:
                    str2 = replaceWord(str2, "F10", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F11:
                    str2 = replaceWord(str2, "F11", "_");
                    display2(str2, hwnd);
                    break;

                case VK_F12:
                    str2 = replaceWord(str2, "F12", "_");
                    display2(str2, hwnd);
                    break;

                case VK_SNAPSHOT:
                    puts("printscreen");
                    str2 = replaceWord(str2, "PRINTSCREEN", "_");
                    display2(str2, hwnd);
                    break;

                case VK_TAB:
                    str2 = replaceWord(str2, "TAB", "_");
                    display2(str2, hwnd);
                    break;

                case VK_PRIOR:
                    str2 = replaceWord(str2, "PAGEUP", "_");
                    display2(str2, hwnd);
                    break;

                case VK_SPACE:
                    str2 = replaceWord(str2, "SPACE", "_");
                    display2(str2, hwnd);
                    break;

                case VK_BACK:
                    str2 = replaceWord(str2, "BACKSPACE", "_");
                    display2(str2, hwnd);
                    break;

                case VK_CONTROL:
                    str2 = replaceWord(str2, "CTRL", "_");
                    display2(str2, hwnd);
                    break;

                case VK_SHIFT:
                    str2 = replaceWord(str2, "SHIFT", "_");
                    display2(str2, hwnd);
                    break;

                case VK_NEXT:
                    str2 = replaceWord(str2, "PAGEDOWN", "_");
                    display2(str2, hwnd);
                    break;

                case VK_LWIN:
                    str2 = replaceWord(str2, "LWIN", "_");
                    display2(str2, hwnd);
                    break;

                // Process other non-character keystrokes.

                default:
                    break;
            }

        case WM_CHAR:
            switch (wParam){
            case 0x5B:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x3B:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x5C:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x2F:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x2D:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x2C:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case 0x60:
                str1 = replaceChar(str1, (char) wParam, '_');
                display(str1, hwnd);
                break;
            case VK_TAB:
                str1 = replaceWord(str1, "TAB", "_");
                display(str1, hwnd);
                break;
            default:
                if((wParam > 61 && wParam < 123) || (wParam > 47 && wParam < 58)) {
                    str1 = replaceChar(str1, (char) wParam, '_');
                    display(str1, hwnd);
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

