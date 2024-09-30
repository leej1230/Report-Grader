#pragma once
#include <Windows.h>
#include "imgui.h"
#include "nfd.h"
#include <filesystem>
#include <string>
#include "stringapiset.h"
#include <vector>
#include "../CSVManager/CSVManager.h"

class MainControl {
public:
	void Draw();

private:
	std::string m_PDFPath = "null";
	std::string m_CSVPath = "null";
	std::vector<std::wstring> pdfFiles;
	bool m_showStudentTable = false;
	void DrawStudentTable();

	CSVManager m_CSVManager;
};