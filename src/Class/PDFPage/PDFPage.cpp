#include "PDFPage.h"

PDFPage::PDFPage(int pageWidth, int pageHeight)
{
	m_pageWidth = pageWidth;
	m_pageHeight = pageHeight;
	m_pageBuffer = std::vector<uint8_t>(pageWidth * pageHeight * 4, 255);
	m_isTransparent = true;
}