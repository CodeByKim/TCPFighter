#include "CommonLibrary.h"
#include "Game.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    Game app(hInstance, nCmdShow);
    app.Run();   
}

