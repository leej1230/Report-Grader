#include "MainControl.h"

void MainControl::UpdateFileList(std::wstring filename) {
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, filename.c_str(), -1, (char*)NULL, 0, NULL, NULL);
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	WideCharToMultiByte(CP_OEMCP, 0, filename.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string fileNameStr(cpMultiByte, cpMultiByte + iBufferSize - 1);

	// 正義表現によるファイル名チェック
	if (std::regex_match(fileNameStr, fileNamePattern)) {
		std::stringstream ss(fileNameStr);
		std::string studentID;
		if(std::getline(ss, studentID, '@'))
			studentIDtoFileName[studentID] = fileNameStr;
	}
}

bool MainControl::GetPDFFilePath(std::string studentID, std::string &fullPath) {
	if (studentIDtoFileName.find(studentID) != studentIDtoFileName.end()) {
		fullPath = m_PDFPath + "\\" + studentIDtoFileName[studentID];
		return true;
	}
	return false;
}

void MainControl::RequestDrawPdf(std::string studentID) {
	std::string filePath;
	if (GetPDFFilePath(studentID, filePath)) {
		m_PDFManager->UpdatePDFPreview(filePath);
	}
	else {
		m_PDFManager->UpdatePDFPreview("");
	}
}

void MainControl::GetPDFDirPath() {
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_PickFolder(NULL, &outPath);

	if (result == NFD_OKAY) {
		m_PDFPath = outPath;
		bool check = std::filesystem::exists(m_PDFPath);
		pdfFiles.clear();
		for (const auto& entry : std::filesystem::directory_iterator(m_PDFPath.c_str()))
			UpdateFileList(entry.path().filename().wstring());
		//pdfFiles.push_back(entry.path().filename().wstring());
	}
	else if (result == NFD_CANCEL) {
		m_PDFPath = "null";
	}
	else {
		printf("Error: %s\n", NFD_GetError());
	}
}

void MainControl::GetCSVFilePath() {
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("csv", NULL, &outPath);

	if (result == NFD_OKAY) {
		m_CSVPath = outPath;
		bool check = std::filesystem::exists(m_CSVPath);
		if (check) m_CSVManager->LoadCSV(m_CSVPath.c_str());
		m_showStudentTable = true;
	}
	else if (result == NFD_CANCEL) {
		m_CSVPath = "null";
	}
	else {
		printf("Error: %s\n", NFD_GetError());
	}
}

void MainControl::Draw()
{
	ImGui::Begin("Main Control");

	// PDFのディレクトリを開く
	if (ImGui::Button("Open Directory")) {
		GetPDFDirPath();
	}
	ImGui::Text(u8"Currently opened directory: %s", m_PDFPath.c_str());
	
	//PDFのファイル一覧を書き出す
	//for (const auto& pdfFile : pdfFiles) {
	//	std::wstring wstr = pdfFile;
	//	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	//	std::string str(size_needed, 0);
	//	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
	//	ImGui::Text("%s", str.c_str());
	//}

	// CSVファイルを開く
	if (ImGui::Button("Open CSV")) {
		GetCSVFilePath();
	}
	ImGui::Text(u8"Currently opened CSV: %s", m_CSVPath.c_str());

	ImGui::End();

	// 生徒のテーブルを描画
	m_CSVManager->Draw();
}

MainControl::MainControl(PDFManager* pdfManager) : m_PDFManager(pdfManager) {
	m_CSVManager = new CSVManager(pdfManager, [this](std::string studentID) { RequestDrawPdf(studentID); });
}