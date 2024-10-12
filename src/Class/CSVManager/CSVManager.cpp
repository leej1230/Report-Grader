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
		m_columnNames = columns;
		//for (auto& column : columns) m_columnNames.push_back(Utility::DecodeGarble(column));

		std::vector<std::string> m_studentIDs = m_document.GetColumn<std::string>("# 学籍番号");

		int rows = m_document.GetRowCount();
		for (int i = 0; i < rows; ++i) {
			std::vector<std::string> row = m_document.GetRow<std::string>(i);
			std::string rRole = row[0];
			if (rRole != "履修生") continue;

			StudentInfo newStudent;
			for (int i = 0; i < row.size(); ++i) {
				newStudent.SetStudentInfo(m_columnNames[i], row[i]);
			}
			std::string studentID = newStudent.GetStudentInfo("# 学籍番号");

			m_studentIDtoRowIdx[studentID] = i;
			/*
			std::string studentUserID = row[1];
			std::string studentID = row[2];
			std::string studentName = row[3];
			std::string studentNameEnglish = row[4];
			std::string studentEmail = row[5];
			std::string studentTotalScore = row[6];
			std::string studentEvaluation = row[7];
			std::string studentComment = row[8];
			std::string submissionStatus = row[9];
			std::string submissionDate = row[10];
			std::string submissionCount = row[11];
			std::string fileName1 = row[12];
			//std::string fileName2 = row[13];
			//std::string fileName3 = row[14];
			StudentInfo studentInfo(
				studentUserID,
				studentID,
				studentName,
				studentNameEnglish,
				studentEmail,
				studentTotalScore,
				studentEvaluation,
				studentComment,
				submissionStatus,
				submissionDate,
				submissionCount,
				fileName1
				//fileName2,
				//fileName3
			);
			*/
			m_studentIDtoInfo.emplace(studentID, newStudent);
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
		m_callback(studentID);
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

	if (m_columnNames.empty()) {
		ImGui::Text("No CSV loaded");
		ImGui::End();
		return;
	}
	if (ImGui::BeginTable("StudentTable", m_columnNames.size())) {
		ImGui::TableSetupColumn("PDF", ImGuiTableColumnFlags_WidthStretch);
		for (int i = 1; i < m_columnNames.size(); ++i) {
			ImGui::TableSetupColumn(m_columnNames[i].c_str(), ImGuiTableColumnFlags_WidthStretch);
		}
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

			for (int j = 1; j < m_columnNames.size(); ++j) {
				ImGui::TableNextColumn();
				ImGui::Text(studentInfo.GetStudentInfo(m_columnNames[j]).c_str());
			}
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentUserID().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentID().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentName().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentNameEn().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentEmail().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentTotalScore().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentEvaluation().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetStudentComment().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetSubmissionStatus().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetSubmissionDate().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetSubmissionCount().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetFileName1().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetFileName2().c_str());
			//ImGui::TableNextColumn();
			//ImGui::Text(studentInfo.GetFileName3().c_str());
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

void CSVManager::DrawScorePopup() {
	ImGui::Begin("Score Popup");

	if (m_currentStudent) {
		//int currScore = std::stoi(m_currentStudent->GetStudentTotalScore());
		//if (ImGui::InputInt("Score", &currScore)) {
		//	auto& [studentID, studentInfo] = *std::next(m_studentIDtoInfo.begin(), m_selectedPDF);
		//	studentInfo.SetStudentTotalScore(std::to_string(currScore));
		//	UpdateScore(studentID, std::to_string(currScore));
		//}

		if (ImGui::Button("Previous")) {
			PickPreviousStudent();
		}
		ImGui::SameLine();
		if (ImGui::Button("Next")) {
			PickNextStudent();
		}
	}
	else {
		ImGui::Text("No student selected");
	}

	ImGui::End();
}

void CSVManager::Draw() {
	DrawTable();
	DrawScorePopup();
}


CSVManager::~CSVManager()
{
	m_document.Clear();
	m_studentIDtoInfo.clear();
}