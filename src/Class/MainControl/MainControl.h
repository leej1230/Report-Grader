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
	/*!
	* @brief ファイルを読み込むためのGUIと必要に応じて
	*/
	void Draw();
	MainControl(PDFManager* pdfManager);
private:
	std::string m_PDFPath = "null";
	std::string m_CSVPath = "null";
	std::vector<std::wstring> pdfFiles;
	void RequestDrawPdf(std::string studentID);

	void GetPDFDirPath();

	void GetCSVFilePath();
	bool m_showStudentTable = false;
	bool m_showScorePopup = false;
	void DrawStudentTable();
	void UpdateFileList(std::wstring filename);
	std::unordered_map<std::string, std::string> studentIDtoFileName;
	const std::regex fileNamePattern = std::regex(R"(^[^@]*@[^@]*@[^@\n]*$)");
	bool GetPDFFilePath(std::string studentID, std::string& fullPath);
	CSVManager* m_CSVManager = nullptr;
	PDFManager* m_PDFManager = nullptr;
};