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
	CSVManager(PDFManager* pdfManager, std::function<void(std::string)> callback) : m_PDFManager(pdfManager), m_callback(callback) {};
	~CSVManager();
	bool LoadCSV(std::string filePath);
	std::vector<std::string> GetColumnNames();
	std::vector<std::string> GetValuesByColumn(std::string columnName);

	// Draws ImGui table
	// Has radio button to select pdf
	// Student Info
	// Column to write score
	// In future, add column
	void Draw();

	void SetPDFManager(PDFManager* pdfManager) { m_PDFManager = pdfManager; }

	void SetCallback(std::function<void(std::string)> callback) { m_callback = callback; }

	void PickNextStudent();
	void PickPreviousStudent();
private:
	rapidcsv::Document m_document;

	void UpdatePDFPreview(int i);

	//! 現在選択中のラジオボタンのインデックス(0から)
	std::unordered_map<std::string, StudentInfo> m_studentIDtoInfo;
	int m_selectedPDF = -1;
	PDFManager* m_PDFManager = nullptr;

	std::function<void(std::string)> m_callback;
};

