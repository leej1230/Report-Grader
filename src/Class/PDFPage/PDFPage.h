#pragma once
#include <vector>

class PDFPage
{
public:
	PDFPage() {};
	
	// Creates blank image based on page width and height
	PDFPage(int pageWidth, int pageHeight);

	int GetPageWidth() { return m_pageWidth; }
	int GetPageHeight() { return m_pageHeight; }
	void SetPageWidth(int pageWidth) { m_pageWidth = pageWidth; }
	void SetPageHeight(int pageHeight) { m_pageHeight = pageHeight; }
	std::vector<uint8_t> GetPageBuffer() { return m_pageBuffer; }
	void SetPageBuffer(std::vector<uint8_t> buffer) { m_pageBuffer = buffer; }
	void SetIsTransparent(bool isTransparent) { m_isTransparent = isTransparent; }
private:
	int m_pageWidth;
	int m_pageHeight;
	std::vector<uint8_t> m_pageBuffer;

	// Is there alpha channel
	bool m_isTransparent;
};