#pragma once

#include <string>
#include <vector>
#include <fpdf_doc.h>
#include <fpdf_edit.h>
#include <cpp/fpdf_scopers.h>
#include <fpdfview.h>
#include "PDFPage/PDFPage.h"

class PDFManager
{
public:
	PDFManager() {};

	void LoadPDFFromStringPath(std::string filePath);

	int GetPageCount() { return FPDF_GetPageCount(m_pdfDocument); }
	std::vector<PDFPage> GetPagePreview();
private:
	std::vector<uint8_t> m_pdfBitmaps;
	std::vector<uint8_t> m_buffer;
	std::string m_pdfPath;
	std::vector<uint8_t> m_documentBuffer;
	FPDF_DOCUMENT m_pdfDocument;
};