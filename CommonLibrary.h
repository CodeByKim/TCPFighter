#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "winmm.lib")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include <functional>
#include <chrono>
#include <queue>
#include <filesystem>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <timeapi.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 25000
#define BUFFER_SIZE 1024
#define RING_BUFFER_SIZE 10000

#define WINDOWCLASS_NAME L"TCPFighter"
#define UM_SOCKET (WM_USER + 1)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define COLOR_BIT 32

struct Position2D
{
	int x;
	int y;
};

struct BmpImageData
{
	BYTE* image;
	int width;
	int height;
	int pitch;
};

struct ScreenSize
{
	int width;
	int height;
};

#define dfPACKET_MOVE_DIR_LL					0
#define dfPACKET_MOVE_DIR_LU					1
#define dfPACKET_MOVE_DIR_UU					2
#define dfPACKET_MOVE_DIR_RU					3
#define dfPACKET_MOVE_DIR_RR					4
#define dfPACKET_MOVE_DIR_RD					5
#define dfPACKET_MOVE_DIR_DD					6
#define dfPACKET_MOVE_DIR_LD					7
