#include "Window.h"
#include "Util.h"

Window::Window(HINSTANCE hInstance, int nCmdShow)
    : mhInstance(hInstance)
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
}

Window::~Window()
{
    Util::GetInstance().PrintLog(L"Window : dtor()");
    timeEndPeriod(1);
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

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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