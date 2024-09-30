#include "CSVManager.h"
#include "imgui.h"
#include "../../Utils/Utils.h"

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

		std::vector<std::string> m_studentIDs = m_document.GetColumn<std::string>(Utility::EncodeGarble("# äwê–î‘çÜ"));

		int rows = m_document.GetRowCount();
		for (int i = 0; i < rows; ++i) {
			std::vector<std::string> row = m_document.GetRow<std::string>(i);
			std::string rRole = Utility::DecodeGarble(row[0]);
			if (rRole != "óöèCê∂") continue;

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

CSVManager::~CSVManager()
{
	m_document.Clear();
	m_studentIDtoInfo.clear();
}