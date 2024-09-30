#include "MainControl.h"

void MainControl::Draw()
{
	ImGui::Begin("Main Control");

	// Ask directory for PDFs
	if (ImGui::Button("Open Directory")) {
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_PickFolder(NULL, &outPath);

		if (result == NFD_OKAY) {
			m_PDFPath = outPath;
			bool check = std::filesystem::exists(m_PDFPath);
			pdfFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(m_PDFPath.c_str()))
				pdfFiles.push_back(entry.path().filename().wstring());
		}
		else if (result == NFD_CANCEL) {
			m_PDFPath = "null";
		}
		else {
			printf("Error: %s\n", NFD_GetError());
		}
	}
	ImGui::Text(u8"Currently opened directory: %s", m_PDFPath.c_str());
	for (const auto& pdfFile : pdfFiles) {
		std::wstring wstr = pdfFile;
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
		std::string str(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
		ImGui::Text("%s", str.c_str());
	}

	// Ask to locate CSV file
	if (ImGui::Button("Open CSV")) {
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog("csv", NULL, &outPath);

		if (result == NFD_OKAY) {
			m_CSVPath = outPath;
			bool check = std::filesystem::exists(m_CSVPath);
			if (check) m_CSVManager.LoadCSV(m_CSVPath.c_str());
		}
		else if (result == NFD_CANCEL) {
			m_CSVPath = "null";
		}
		else {
			printf("Error: %s\n", NFD_GetError());
		}
	}

	ImGui::End();

	if (m_showStudentTable) DrawStudentTable();
}

void MainControl::DrawStudentTable()
{
	ImGui::Begin("Student Table");

	ImGui::End();
}