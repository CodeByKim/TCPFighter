#include "Window.h"
#include "Util.h"

Window* app = nullptr;

Window::Window(HINSTANCE hInstance, int nCmdShow)
    : mhInstance(hInstance)
    , mScreenSize{ SCREEN_WIDTH, SCREEN_HEIGHT }
    , mIsFocus(false)
{
    if (!RegisterWindowClass())
    {
        Util::GetInstance().ShowMessageBox(L"RegisterWindowClass() Error");
        return;
    }

    if (!Create(nCmdShow))
    {
        Util::GetInstance().ShowMessageBox(L"Create() Error");
        return;
    }

    timeBeginPeriod(1);
    app = this;
}

Window::~Window()
{
    Util::GetInstance().PrintLog(L"Window : dtor()");
    timeEndPeriod(1);
}

void Window::SetScreenSize(int screenWidth, int screenHeight)
{
    mScreenSize.width = screenWidth;
    mScreenSize.height = screenHeight;

    RECT rectWindow = { 0, 0, screenWidth, screenHeight };
    AdjustWindowRect(&rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(mhWnd,
        HWND_TOPMOST,
        100,
        100,
        rectWindow.right - rectWindow.left,
        rectWindow.bottom - rectWindow.top,
        SWP_NOMOVE | SWP_NOZORDER);
}

bool Window::Create(int nCmdShow)
{ 
    mhWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mhInstance, nullptr);

    if (!mhWnd)
    {
        return false;
    }

    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return true;
}

void Window::Run()
{
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            FrameUpdate();
        }
    }
}

bool Window::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Window::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = mhInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = WINDOWCLASS_NAME;
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}

bool Window::IsFocus()
{
    return mIsFocus;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (app != nullptr)
    {
        app->ProcessUserWindowMessage(hWnd, message, wParam, lParam);
    }    

    switch (message)
    {
    case WM_SETFOCUS:
        if (app != nullptr)
            app->mIsFocus = true;
        break;
    case WM_KILLFOCUS:
        if (app != nullptr)
            app->mIsFocus = false;
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}