#pragma once
#include <string>

class StudentInfo
{
public:
	StudentInfo(std::string studentUserID, std::string studentID, std::string studentName, std::string studentNameEn, std::string studentEmail, std::string submissionStatus, std::string submissionDate, std::string score)
		: m_studentUserID(studentUserID), m_studentID(studentID), m_studentName(studentName), m_studentNameEn(studentNameEn), m_studentEmail(studentEmail), m_submissionStatus(submissionStatus), m_submissionDate(submissionDate), m_score(score) {};

	// ゲッター
	std::string GetStudentUserID() { return m_studentUserID; }
	std::string GetStudentID() { return m_studentID; }
	std::string GetStudentName() { return m_studentName; }
	std::string GetStudentNameEn() { return m_studentNameEn; }
	std::string GetStudentEmail() { return m_studentEmail; }
	std::string GetSubmissionStatus() { return m_submissionStatus; }
	std::string GetSubmissionDate() { return m_submissionDate; }
	std::string GetScore() { return m_score; }

	// セッター
	void SetStudentUserID(std::string studentUserID) { m_studentUserID = studentUserID; }
	void SetStudentID(std::string studentID) { m_studentID = studentID; }
	void SetStudentName(std::string studentName) { m_studentName = studentName; }
	void SetStudentNameEn(std::string studentNameEn) { m_studentNameEn = studentNameEn; }
	void SetStudentEmail(std::string studentEmail) { m_studentEmail = studentEmail; }
	void SetSubmissionStatus(std::string submissionStatus) { m_submissionStatus = submissionStatus; }
	void SetSubmissionDate(std::string submissionDate) { m_submissionDate = submissionDate; }
	void SetScore(std::string score) { m_score = score; }
private:
	std::string m_studentUserID;
	std::string m_studentID;
	std::string m_studentName;
	std::string m_studentNameEn;
	std::string m_studentEmail;
	std::string m_submissionStatus;
	std::string m_submissionDate;
	std::string m_score;
};