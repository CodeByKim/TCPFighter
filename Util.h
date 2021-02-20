#pragma once

#include "CommonLibrary.h"

class Util
{
public:
	static Util& GetInstance();
	void ShowMessageBox(std::wstring_view message);
	void PrintLog(std::wstring_view message);
	void PrintError(std::wstring_view message);
	void PrintError(std::wstring_view message, int errorCode);

private:

};

