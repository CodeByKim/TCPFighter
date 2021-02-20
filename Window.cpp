#include "Window.h"
#include "Util.h"

Window::Window()
{
	Util::GetInstance().ShowMessageBox(L"Ctor() !");
}

Window::~Window()
{

}

bool Window::Create()
{
	Util::GetInstance().PrintLog(L"Create !");
	return true;
}

void Window::Run()
{
	Util::GetInstance().PrintError(L"Run !", 100);
}