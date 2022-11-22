#pragma once
#include "StringConverter.h"
#include <windows.h>

class ErrorLogger
{
public:
	static void Log(string message);
	static void Log(HRESULT hr, string message);
};
