#include "CommonLibrary.h"
#include "TCPFighter.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    TCPFighter game(hInstance, nCmdShow);
    game.Run();
}

