#pragma once

#include <string>
#include <vector>
#include <fpdf_doc.h>
#include <fpdf_edit.h>
#include <cpp/fpdf_scopers.h>
#include <fpdfview.h>
#include "PDFPage/PDFPage.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class PDFManager
{
public:
	PDFManager() {};

	void LoadPDFFromStringPath(std::string filePath);

	int GetPageCount() { return FPDF_GetPageCount(m_pdfDocument); }
	std::vector<PDFPage> GetPagePreview();
	void UpdatePDFPreview(std::string filePath);
	void Draw();
private:
	bool LoadTextureFromMemory(std::vector<uint8_t> vec, GLuint* out_texture, int image_width, int image_height);
	std::vector<uint8_t> m_pdfBitmaps;
	std::vector<uint8_t> m_buffer;
	std::string m_pdfPath;
	std::string m_windowTitle = "PDF Preview###";
	std::vector<uint8_t> m_documentBuffer;
	FPDF_DOCUMENT m_pdfDocument;
	float m_ZoomScale = 1.0f;
	std::vector<PDFPage> m_pdfPages;
	std::vector<GLuint> m_textureIDs;
};