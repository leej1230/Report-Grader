#pragma once

#include "rapidcsv.h"
#include "../StudentInfo/StudentInfo.h"
#include <string>
#include <vector>

class CSVManager
{
public:
	CSVManager() {};
	~CSVManager();
	bool LoadCSV(std::string filePath);
	std::vector<std::string> GetColumnNames();
	std::vector<std::string> GetValuesByColumn(std::string columnName);

	void Draw();
private:
	rapidcsv::Document m_document;
	std::unordered_map<std::string, StudentInfo> m_studentIDtoInfo;
};

