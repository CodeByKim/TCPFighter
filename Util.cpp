#include "Util.h"

Util& Util::GetInstance()
{
	static Util instance;
	return instance;
}

void Util::ShowMessageBox(std::wstring_view message)
{
	MessageBox(NULL, message.data(), L"Log", 0);
}

void Util::PrintLog(std::wstring_view message)
{
	wchar_t str[256];
	wsprintf(str, L"[LOG] : %s\n", message.data());
	OutputDebugString(str);
}

void Util::PrintError(std::wstring_view message)
{
	wchar_t str[256];
	wsprintf(str, L"[ERROR] : %s\n", message.data());
	OutputDebugString(str);
}

void Util::PrintError(std::wstring_view message, int errorCode)
{
	wchar_t str[256];
	wsprintf(str, L"[ERROR] : %s, ErrorCode : %d\n", message.data(), errorCode);
	OutputDebugString(str);
}