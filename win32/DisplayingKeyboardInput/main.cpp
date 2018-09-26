#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <strsafe.h>

#define BUFSIZE 65535
#define SHIFTED 0x8000

/*  Declare Windows procedure  */
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
char * str = "Hello, Windows 10!";

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
    wincl.lpfnWndProc = WndProc;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
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
           _T("Petzold Test"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
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

LRESULT CALLBACK WndProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                   // handle to device context
    TEXTMETRIC tm;             // structure for text metrics
    static DWORD dwCharX;      // average width of characters
    static DWORD dwCharY;      // height of characters
    static DWORD dwClientX;    // width of client area
    static DWORD dwClientY;    // height of client area
    static DWORD dwLineLen;    // line length
    static DWORD dwLines;      // text lines in client area
    static int nCaretPosX = 0; // horizontal position of caret
    static int nCaretPosY = 0; // vertical position of caret
    static int nCharWidth = 0; // width of a character
    static int cch = 0;        // characters in buffer
    static int nCurChar = 0;   // index of current character
    static PTCHAR pchInputBuf; // input buffer
    int i, j;                  // loop counters
    int cCR = 0;               // count of carriage returns
    int nCRIndex = 0;          // index of last carriage return
    int nVirtKey;              // virtual-key code
    TCHAR szBuf[128];          // temporary buffer
    TCHAR ch;                  // current character
    PAINTSTRUCT ps;            // required by BeginPaint
    RECT rc;                   // output rectangle for DrawText
    SIZE sz;                   // string dimensions
    COLORREF crPrevText;       // previous text color
    COLORREF crPrevBk;         // previous background color
    size_t * pcch;
    HRESULT hResult;

    switch (uMsg)
    {
        case WM_CREATE:

            // Get the metrics of the current font.

            hdc = GetDC(hwndMain);
            GetTextMetrics(hdc, &tm);
            ReleaseDC(hwndMain, hdc);

            // Save the average character width and height.

            dwCharX = tm.tmAveCharWidth;
            dwCharY = tm.tmHeight;

            // Allocate a buffer to store keyboard input.

            pchInputBuf = (LPTSTR) GlobalAlloc(GPTR,
                BUFSIZE * sizeof(TCHAR));
            return 0;

        case WM_SIZE:

            // Save the new width and height of the client area.

            dwClientX = LOWORD(lParam);
            dwClientY = HIWORD(lParam);

            // Calculate the maximum width of a line and the
            // maximum number of lines in the client area.

            dwLineLen = dwClientX - dwCharX;
            dwLines = dwClientY / dwCharY;
            break;


        case WM_SETFOCUS:

            // Create, position, and display the caret when the
            // window receives the keyboard focus.

            CreateCaret(hwndMain, (HBITMAP) 1, 0, dwCharY);
            SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            ShowCaret(hwndMain);
            break;

        case WM_KILLFOCUS:

            // Hide and destroy the caret when the window loses the
            // keyboard focus.

            HideCaret(hwndMain);
            DestroyCaret();
            break;

        case WM_CHAR:
        // check if current location is close enough to the
        // end of the buffer that a buffer overflow may
        // occur. If so, add null and display contents.
    if (cch > BUFSIZE-5)
    {
        pchInputBuf[cch] = 0x00;
        SendMessage(hwndMain, WM_PAINT, 0, 0);
    }
            switch (wParam)
            {
                case 0x08:  // backspace
                case 0x0A:  // linefeed
                case 0x1B:  // escape
                    MessageBeep((UINT) -1);
                    return 0;

                case 0x09:  // tab

                    // Convert tabs to four consecutive spaces.

                    for (i = 0; i < 4; i++)
                        SendMessage(hwndMain, WM_CHAR, 0x20, 0);
                    return 0;

                case 0x0D:  // carriage return

                    // Record the carriage return and position the
                    // caret at the beginning of the new line.

                    pchInputBuf[cch++] = 0x0D;
                    nCaretPosX = 0;
                    nCaretPosY += 1;
                    break;

                default:    // displayable character

                    ch = (TCHAR) wParam;
                    HideCaret(hwndMain);

                    // Retrieve the character's width and output
                    // the character.

                    hdc = GetDC(hwndMain);
                    GetCharWidth32(hdc, (UINT) wParam, (UINT) wParam,
                        &nCharWidth);
                    TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY,
                        &ch, 1);
                    ReleaseDC(hwndMain, hdc);

                    // Store the character in the buffer.

                    pchInputBuf[cch++] = ch;

                    // Calculate the new horizontal position of the
                    // caret. If the position exceeds the maximum,
                    // insert a carriage return and move the caret
                    // to the beginning of the next line.

                    nCaretPosX += nCharWidth;
                    if ((DWORD) nCaretPosX > dwLineLen)
                    {
                        nCaretPosX = 0;
                        pchInputBuf[cch++] = 0x0D;
                        ++nCaretPosY;
                    }
                    nCurChar = cch;
                    ShowCaret(hwndMain);
                    break;
            }
            SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            break;

        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_LEFT:   // LEFT ARROW

                    // The caret can move only to the beginning of
                    // the current line.

                    if (nCaretPosX > 0)
                    {
                        HideCaret(hwndMain);

                        // Retrieve the character to the left of
                        // the caret, calculate the character's
                        // width, then subtract the width from the
                        // current horizontal position of the caret
                        // to obtain the new position.

                        ch = pchInputBuf[--nCurChar];
                        hdc = GetDC(hwndMain);
                        GetCharWidth32(hdc, ch, ch, &nCharWidth);
                        ReleaseDC(hwndMain, hdc);
                        nCaretPosX = max(nCaretPosX - nCharWidth,
                            0);
                        ShowCaret(hwndMain);
                    }
                    break;

                case VK_RIGHT:  // RIGHT ARROW

                    // Caret moves to the right or, when a carriage
                    // return is encountered, to the beginning of
                    // the next line.

                    if (nCurChar < cch)
                    {
                        HideCaret(hwndMain);

                        // Retrieve the character to the right of
                        // the caret. If it's a carriage return,
                        // position the caret at the beginning of
                        // the next line.

                        ch = pchInputBuf[nCurChar];
                        if (ch == 0x0D)
                        {
                            nCaretPosX = 0;
                            nCaretPosY++;
                        }

                        // If the character isn't a carriage
                        // return, check to see whether the SHIFT
                        // key is down. If it is, invert the text
                        // colors and output the character.

                        else
                        {
                            hdc = GetDC(hwndMain);
                            nVirtKey = GetKeyState(VK_SHIFT);
                            if (nVirtKey & SHIFTED)
                            {
                                crPrevText = SetTextColor(hdc,
                                    RGB(255, 255, 255));
                                crPrevBk = SetBkColor(hdc,
                                    RGB(0,0,0));
                                TextOut(hdc, nCaretPosX,
                                    nCaretPosY * dwCharY,
                                    &ch, 1);
                                SetTextColor(hdc, crPrevText);
                                SetBkColor(hdc, crPrevBk);
                            }

                            // Get the width of the character and
                            // calculate the new horizontal
                            // position of the caret.

                            GetCharWidth32(hdc, ch, ch, &nCharWidth);
                            ReleaseDC(hwndMain, hdc);
                            nCaretPosX = nCaretPosX + nCharWidth;
                        }
                        nCurChar++;
                        ShowCaret(hwndMain);
                        break;
                    }
                    break;

                case VK_UP:     // UP ARROW
                case VK_DOWN:   // DOWN ARROW
                    MessageBeep((UINT) -1);
                    return 0;

                case VK_HOME:   // HOME

                    // Set the caret's position to the upper left
                    // corner of the client area.

                    nCaretPosX = nCaretPosY = 0;
                    nCurChar = 0;
                    break;

                case VK_END:    // END

                    // Move the caret to the end of the text.

                    for (i=0; i < cch; i++)
                    {
                        // Count the carriage returns and save the
                        // index of the last one.

                        if (pchInputBuf[i] == 0x0D)
                        {
                            cCR++;
                            nCRIndex = i + 1;
                        }
                    }
                    nCaretPosY = cCR;

                    // Copy all text between the last carriage
                    // return and the end of the keyboard input
                    // buffer to a temporary buffer.

                    for (i = nCRIndex, j = 0; i < cch; i++, j++)
                        szBuf[j] = pchInputBuf[i];
                    szBuf[j] = TEXT('\0');

                    // Retrieve the text extent and use it
                    // to set the horizontal position of the
                    // caret.

                    hdc = GetDC(hwndMain);
                    hResult = StringCchLength(szBuf, 128, pcch);
                    if (FAILED(hResult))
                    {
                    // TODO: write error handler
                    }
                    GetTextExtentPoint32(hdc, szBuf, *pcch,
                        &sz);
                    nCaretPosX = sz.cx;
                    ReleaseDC(hwndMain, hdc);
                    nCurChar = cch;
                    break;

                default:
                    break;
            }
            SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            break;

        case WM_PAINT:
            if (cch == 0)       // nothing in input buffer
                break;

            hdc = BeginPaint(hwndMain, &ps);
            HideCaret(hwndMain);

            // Set the clipping rectangle, and then draw the text
            // into it.

            SetRect(&rc, 0, 0, dwLineLen, dwClientY);
            DrawText(hdc, pchInputBuf, -1, &rc, DT_LEFT);

            ShowCaret(hwndMain);
            EndPaint(hwndMain, &ps);
            break;

        // Process other messages.

        case WM_DESTROY:
            PostQuitMessage(0);

            // Free the input buffer.

            GlobalFree((HGLOBAL) pchInputBuf);
            UnregisterHotKey(hwndMain, 0xAAAA);
            break;

        default:
            return DefWindowProc(hwndMain, uMsg, wParam, lParam);
    }
    return NULL;
}
