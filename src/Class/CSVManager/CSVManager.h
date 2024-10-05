#pragma once

#include "rapidcsv.h"
#include "../StudentInfo/StudentInfo.h"
#include <imgui.h>
#include <string>
#include <vector>
#include "../PDFManager.h"

class CSVManager
{
public:
	CSVManager() {};
	~CSVManager();
	bool LoadCSV(std::string filePath);
	std::vector<std::string> GetColumnNames();
	std::vector<std::string> GetValuesByColumn(std::string columnName);

	// Draws ImGui table
	// Has radio button to select pdf
	// Student Info
	// Column to write score
	// In future, add column
	void DrawTable();

	void SetPDFManager(PDFManager* pdfManager) { m_PDFManager = pdfManager; }

	void SetCallback(std::function<void(std::string)> callback) { m_callback = callback; }
private:
	rapidcsv::Document m_document;

	//! 現在選択中のラジオボタンのインデックス(0から)
	std::unordered_map<std::string, StudentInfo> m_studentIDtoInfo;
	int m_selectedPDF;
	PDFManager* m_PDFManager;

	std::function<void(std::string)> m_callback;
};

