#include "PDFManager.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <numeric>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

void PDFManager::LoadPDFFromStringPath(std::string filePath)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, NULL, 0);
	std::wstring wFilePath(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, &wFilePath[0], size_needed);

	std::ifstream file(filePath, std::ios::binary|std::ios::ate);
	if (!file.is_open()) {
		std::cout << "Error: Could not open file" << std::endl;
		return;
	}

	// 日本語のファイル名も読み込めるようにするためにメモリにファイルを読み込む
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<uint8_t> buffer(fileSize);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
		std::cout << "Couldn't Read file" << std::endl;
	}

	m_documentBuffer = buffer;

	m_pdfPath = filePath;

	// pdfのドキュメントをメモリから読み込む
	m_pdfDocument = FPDF_LoadMemDocument(m_documentBuffer.data(), m_documentBuffer.size(), nullptr);
}

std::vector<PDFPage> PDFManager::GetPagePreview()
{
	std::vector<PDFPage> blankRes = std::vector<PDFPage>({ PDFPage(10, 10) });
	std::vector<PDFPage> res;

	if (m_pdfPath == "") return blankRes;

	const int pdfPageCount = GetPageCount();
	for (int i = 0; i < pdfPageCount; ++i)
	{
		std::vector<uint8_t> bitmapData;

		FPDF_PAGE page = FPDF_LoadPage(m_pdfDocument, i);
		if (!page) {
			std::cout << "Error: Could not load page" << std::endl;
			return blankRes;
		}

		const int pageWidth = FPDF_GetPageWidth(page);
		const int pageHeight = FPDF_GetPageHeight(page);
		int stride = pageWidth * 4;
		std::uint8_t* data = new std::uint8_t[pageWidth * pageHeight * 4];

		FPDF_BITMAP bitmap = FPDFBitmap_CreateEx(pageWidth, pageHeight, FPDFBitmap_BGRA, data, stride);
		int isAlpha = FPDFPage_HasTransparency(page) ? 1 : 0;

		if (bitmap) {
			FPDF_DWORD fill_color = isAlpha ? 0x00000000 : 0xFFFFFFFF;
			FPDFBitmap_FillRect(bitmap, 0, 0, pageWidth, pageHeight, fill_color);

			int rotation = 0;
			int flags = FPDF_ANNOT;
			FPDF_RenderPageBitmap(bitmap, page, 0, 0, pageWidth, pageHeight,
				rotation, flags);

			int stride = FPDFBitmap_GetStride(bitmap);
			void* buf = FPDFBitmap_GetBuffer(bitmap);
			uint8_t* buffer = reinterpret_cast<uint8_t*>(buf);

			PDFPage newPage;
			newPage.SetIsTransparent(isAlpha);
			newPage.SetPageWidth(pageWidth);
			newPage.SetPageHeight(pageHeight);
			newPage.SetPageBuffer(std::vector<uint8_t>(buffer, buffer + pageWidth * pageHeight * 4));
			res.push_back(newPage);
		}

		FPDFBitmap_Destroy(bitmap);
		FPDF_ClosePage(page);
	}

	return res;
}

bool PDFManager::LoadTextureFromMemory(std::vector<uint8_t> vec, GLuint* out_texture, int image_width, int image_height)
{
	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, vec.data());

	*out_texture = image_texture;

	return true;
}

void PDFManager::UpdatePDFPreview(std::string filePath)
{
	m_pdfPages.clear();
	m_textureIDs.clear();
	m_pdfPath = "";

	LoadPDFFromStringPath(filePath);
	m_pdfPages = GetPagePreview();
	for (auto& pdfPage : m_pdfPages) {
		GLuint textureID = 0;
		GLsizei pageWidth = pdfPage.GetPageWidth();
		GLsizei pageHeight = pdfPage.GetPageHeight();
		LoadTextureFromMemory(pdfPage.GetPageBuffer(), &textureID, pageWidth, pageHeight);
		m_textureIDs.push_back(textureID);
	}
}

void PDFManager::Draw()
{
	ImGui::Begin("PDF Preview");
	ImGui::SliderFloat("Scale", &m_ZoomScale, 0.5f, 2.0f);

	ImGui::BeginChild("PDF Preview", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	int pageCount = m_pdfPages.size();
	for (int i = 0; i < pageCount; ++i) {
		ImGui::Image((void*)(intptr_t)m_textureIDs[i], ImVec2(m_pdfPages[i].GetPageWidth() * m_ZoomScale, m_pdfPages[i].GetPageHeight() * m_ZoomScale));
	}
	ImGui::EndChild();

	ImGui::End();
}
