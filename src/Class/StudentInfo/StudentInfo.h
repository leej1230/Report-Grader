#pragma once
#include <string>

class StudentInfo
{
public:
	StudentInfo(
		std::string studentUserID, 
		std::string studentID, 
		std::string studentName, 
		std::string studentNameEn, 
		std::string studentEmail, 
		std::string studentTotalScore, 
		std::string studentEvaluation, 
		std::string studentComment, 
		std::string submissionStatus, 
		std::string submissionDate, 
		std::string submissionCount, 
		std::string fileName1, 
		std::string fileName2="null",
		std::string fileName3="null"
	)
	{
		m_studentUserID = studentUserID;
		m_studentID = studentID;
		m_studentName = studentName;
		m_studentNameEn = studentNameEn;
		m_studentEmail = studentEmail;
		m_studentTotalScore = studentTotalScore;
		m_studentEvaluation = studentEvaluation;
		m_studentComment = studentComment;
		m_submissionStatus = submissionStatus;
		m_submissionDate = submissionDate;
		m_submissionCount = submissionCount;
		m_fileName1 = fileName1;
		m_fileName2 = fileName2;
		m_fileName3 = fileName3;
	}

	// ゲッター
	std::string GetStudentUserID() { return m_studentUserID; }
	std::string GetStudentID() { return m_studentID; }
	std::string GetStudentName() { return m_studentName; }
	std::string GetStudentNameEn() { return m_studentNameEn; }
	std::string GetStudentEmail() { return m_studentEmail; }
	std::string GetStudentTotalScore() { return m_studentTotalScore; }
	std::string GetStudentEvaluation() { return m_studentEvaluation; }
	std::string GetStudentComment() { return m_studentComment; }
	std::string GetSubmissionStatus() { return m_submissionStatus; }
	std::string GetSubmissionDate() { return m_submissionDate; }
	std::string GetSubmissionCount() { return m_submissionCount; }
	std::string GetFileName1() { return m_fileName1; }
	std::string GetFileName2() { return m_fileName2; }
	std::string GetFileName3() { return m_fileName3; }

	// セッター
	void SetStudentUserID(std::string studentUserID) { m_studentUserID = studentUserID; }
	void SetStudentID(std::string studentID) { m_studentID = studentID; }
	void SetStudentName(std::string studentName) { m_studentName = studentName; }
	void SetStudentNameEn(std::string studentNameEn) { m_studentNameEn = studentNameEn; }
	void SetStudentEmail(std::string studentEmail) { m_studentEmail = studentEmail; }
	void SetStudentTotalScore(std::string studentTotalScore) { m_studentTotalScore = studentTotalScore; }
	void SetStudentEvaluation(std::string studentEvaluation) { m_studentEvaluation = studentEvaluation; }
	void SetStudentComment(std::string studentComment) { m_studentComment = studentComment; }
	void SetSubmissionStatus(std::string submissionStatus) { m_submissionStatus = submissionStatus; }
	void SetSubmissionDate(std::string submissionDate) { m_submissionDate = submissionDate; }
	void SetSubmissionCount(std::string submissionCount) { m_submissionCount = submissionCount; }
	void SetFileName1(std::string fileName1) { m_fileName1 = fileName1; }
	void SetFileName2(std::string fileName2) { m_fileName2 = fileName2; }
	void SetFileName3(std::string fileName3) { m_fileName3 = fileName3; }
private:
	std::string m_studentUserID;
	std::string m_studentID;
	std::string m_studentName;
	std::string m_studentNameEn;
	std::string m_studentEmail;
	std::string m_studentTotalScore;
	std::string m_studentEvaluation;
	std::string m_studentComment;
	std::string m_submissionStatus;
	std::string m_submissionDate;
	std::string m_submissionCount;
	std::string m_fileName1;
	std::string m_fileName2;
	std::string m_fileName3;
};