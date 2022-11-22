#pragma once
#include <string>

using namespace std;

class StringConverter
{
public:
	// singletone
	static wstring StringToWide(string str);
};
