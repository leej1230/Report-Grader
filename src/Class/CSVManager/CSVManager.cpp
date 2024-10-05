#include "CSVManager.h"
#include "../../Utils/Utils.h"

bool CSVManager::UpdateScore(std::string studentID, std::string newScore) {
	try {
		m_document.SetCell<std::string>(6, m_studentIDtoRowIdx[studentID], newScore);
	}
	catch (const std::exception& e) {
		return false;
	}
	m_document.Save();
	return true;
}

bool CSVManager::LoadCSV(std::string filePath)
{
	try {
		m_document = rapidcsv::Document(filePath, rapidcsv::LabelParams(6, -1));
		
		std::vector<std::string> columns = m_document.GetColumnNames();
		std::vector<std::string> columnsShiftJIS;
		std::vector<std::string> columnsUTF8;
		for (auto& column : columns) {
			columnsShiftJIS.push_back(Utility::DecodeGarble(column));
			columnsUTF8.push_back(Utility::EncodeGarble(Utility::DecodeGarble(column)));
		}

		std::vector<std::string> m_studentIDs = m_document.GetColumn<std::string>("# 学籍番号");

		int rows = m_document.GetRowCount();
		for (int i = 0; i < rows; ++i) {
			std::vector<std::string> row = m_document.GetRow<std::string>(i);
			std::string rRole = row[0];
			if (rRole != "履修生") continue;

			m_studentIDtoRowIdx[row[2]] = i;
			std::string rStudentUserID = Utility::DecodeGarble(row[1]);
			std::string rStudentID = Utility::DecodeGarble(row[2]);
			std::string rStudentName = Utility::DecodeGarble(row[3]);
			std::string rStudentNameEnglish = Utility::DecodeGarble(row[4]);
			std::string rEmail = Utility::DecodeGarble(row[5]);
			std::string rScore = Utility::DecodeGarble(row[6]);
			std::string rSubmissionStatus = Utility::DecodeGarble(row[9]);
			std::string rSubmissionDate = Utility::DecodeGarble(row[10]);
			StudentInfo studentInfo(rStudentUserID, rStudentID, rStudentName, rStudentNameEnglish, rEmail, rScore, rSubmissionStatus, rSubmissionDate);
			m_studentIDtoInfo.emplace(rStudentID, studentInfo);
		}
	}
	catch (const std::exception& e) {
		ImGui::OpenPopup("Error");
		ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Error: %s", e.what());
		if (ImGui::Button("OK")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
		return false;
	}

	return true;
}

void CSVManager::UpdatePDFPreview(int i) {
	if (m_callback) {
		auto& [studentID, studentInfo] = *std::next(m_studentIDtoInfo.begin(), i);
		m_callback(studentInfo.GetStudentID());
		m_currentStudent = &studentInfo;
	}
}

void CSVManager::PickNextStudent() {
	m_selectedPDF = (m_selectedPDF + 1) % m_studentIDtoInfo.size();
	UpdatePDFPreview(m_selectedPDF);
}

void CSVManager::PickPreviousStudent() {
	m_selectedPDF = (m_selectedPDF - 1 + m_studentIDtoInfo.size()) % m_studentIDtoInfo.size();
	UpdatePDFPreview(m_selectedPDF);
}

void CSVManager::DrawTable() {
	ImGui::Begin("Student Table");

	if (ImGui::BeginTable("StudentTable", 8)) {
		ImGui::TableSetupColumn("PDF", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("学籍番号", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("氏名", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("氏名(英語)", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("メールアドレス", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("点数", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("提出状況", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableSetupColumn("提出日", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableHeadersRow();

		for (int i = 0; i < m_studentIDtoInfo.size(); ++i) {
			auto& [studentID, studentInfo] = *std::next(m_studentIDtoInfo.begin(), i);

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::PushID(i);

			if (i == m_selectedPDF) {
				ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(60, 50, 120, 255));
			}
			else {
				ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 0, 0, 0));
			}

			if (ImGui::RadioButton("", &m_selectedPDF, i)) {
				// Set PDF
				UpdatePDFPreview(i);
			}
			ImGui::PopID();
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetStudentID().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetStudentName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetStudentNameEn().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetStudentEmail().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetScore().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetSubmissionStatus().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(studentInfo.GetSubmissionDate().c_str());
		}
		ImGui::EndTable();
	}

	if (ImGui::Button("Next")) {
		PickNextStudent();
	}

	if (ImGui::Button("Previous")) {
		PickPreviousStudent();
	}

	ImGui::End();
}

void CSVManager::DrawScorePopup() {
	ImGui::Begin("Score Popup");

	if (m_currentStudent) {
		int currScore = std::stoi(m_currentStudent->GetScore());
		if (ImGui::InputInt("Score: ", &currScore)) {
			auto& [studentID, studentInfo] = *std::next(m_studentIDtoInfo.begin(), m_selectedPDF);
			studentInfo.SetScore(std::to_string(currScore));
			UpdateScore(studentID, std::to_string(currScore));
		}
	}

	if (ImGui::Button("Previous")) {
		PickPreviousStudent();
	}
	ImGui::SameLine();
	if (ImGui::Button("Next")) {
		PickNextStudent();
	}

	ImGui::End();
}

void CSVManager::Draw() {
	DrawTable();
	if (*m_showScorePopup)
		DrawScorePopup();
}


CSVManager::~CSVManager()
{
	m_document.Clear();
	m_studentIDtoInfo.clear();
}