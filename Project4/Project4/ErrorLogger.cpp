#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(string message)
{
	string error_message = "Error: " + message;
	// ª�� error message 
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, string message)
{

	_com_error error(hr);// comdef������Ͽ��� �޾ƿ�
	wstring error_message = L"Error: " + StringConverter::StringToWide(message) + L"\n" + error.ErrorMessage();
	// �� error message
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);

}