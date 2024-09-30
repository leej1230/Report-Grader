#pragma once

#include <Windows.h>
#include <string>

// QlŒ³
// https://sayahamitt.net/utf8%E3%81%AAstring%E5%85%A5%E3%82%8C%E3%81%9F%E3%82%89shiftjis%E3%81%AAstring%E5%87%BA%E3%81%A6%E3%81%8F%E3%82%8B%E9%96%A2%E6%95%B0%E4%BD%9C%E3%81%A3%E3%81%9F/

namespace Utility {
	// •¶š‰»‚¯‚µ‚½•¶š—ñ‚ğ–ß‚·
	std::string DecodeGarble(std::string garbleStr);
	// •¶š—ñ‚ğ•¶š‰»‚¯‚³‚¹‚é
	std::string EncodeGarble(std::string rawStr);
}