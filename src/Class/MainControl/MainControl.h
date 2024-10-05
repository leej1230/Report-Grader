#pragma once
#include <Windows.h>
#include "imgui.h"
#include "nfd.h"
#include <filesystem>
#include <string>
#include "stringapiset.h"
#include <vector>
#include <regex>
#include "../CSVManager/CSVManager.h"
#include "../PDFManager.h"

class MainControl {
public:
	void Draw();
	void SetPDFManager(PDFManager* pdfManager) {
		m_PDFManager = pdfManager;
		m_CSVManager.SetPDFManager(pdfManager);
		m_CSVManager.SetCallback([this](std::string studentID) { RequestDrawPdf(studentID); });
	}
private:
	std::string m_PDFPath = "null";
	std::string m_CSVPath = "null";
	std::vector<std::wstring> pdfFiles;
	void RequestDrawPdf(std::string studentID);
	bool m_showStudentTable = false;
	void DrawStudentTable();
	void UpdateFileList(std::wstring filename);
	std::unordered_map<std::string, std::string> studentIDtoFileName;
	const std::regex fileNamePattern = std::regex(R"(^[^@]*@[^@]*@[^@\n]*$)");
	bool GetPDFFilePath(std::string studentID, std::string& fullPath);
	CSVManager m_CSVManager;
	PDFManager* m_PDFManager;
};