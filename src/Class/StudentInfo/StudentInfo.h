#pragma once
#include <string>
#include <unordered_map>

class StudentInfo
{
public:
	StudentInfo(){}

	// �Q�b�^�[
	std::string GetStudentInfo(std::string parameter) { return studentInfo.find(parameter) != studentInfo.end() ? studentInfo[parameter] : "null"; }

	// �Z�b�^�[
	void SetStudentInfo(std::string parameter, std::string value) { studentInfo[parameter] = value; }
private:
	std::unordered_map<std::string, std::string> studentInfo;
};