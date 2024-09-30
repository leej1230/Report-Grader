#include "Utils.h"

std::string Utility::DecodeGarble(std::string garbleStr) {
	int n = MultiByteToWideChar(CP_UTF8, 0, garbleStr.c_str(), garbleStr.size() + 1, NULL, 0);
	wchar_t* bufUnicode = new wchar_t[n];
	MultiByteToWideChar(CP_UTF8, 0, garbleStr.c_str(), garbleStr.size() + 1, bufUnicode, n);
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
	char* bufShiftJis = new char[lengthSJis];
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, n + 1, bufShiftJis, lengthSJis, NULL, NULL);
	std::string str(bufShiftJis);
	return str;
}

std::string Utility::EncodeGarble(std::string rawStr) {
	int n = MultiByteToWideChar(CP_THREAD_ACP, 0, rawStr.c_str(), rawStr.size() + 1, NULL, 0);
	wchar_t* bufUnicode = new wchar_t[n];
	MultiByteToWideChar(CP_THREAD_ACP, 0, rawStr.c_str(), rawStr.size() + 1, bufUnicode, n);
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
	char* bufUTF8 = new char[lengthUTF8];
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, n + 1, bufUTF8, lengthUTF8, NULL, NULL);
	std::string str(bufUTF8);
	return str;
}