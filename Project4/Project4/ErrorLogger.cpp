#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(string message)
{
	string error_message = "Error: " + message;
	// 짧은 error message 
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, string message)
{

	_com_error error(hr);// comdef헤더파일에서 받아옴
	wstring error_message = L"Error: " + StringConverter::StringToWide(message) + L"\n" + error.ErrorMessage();
	// 긴 error message
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);

}