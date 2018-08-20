#include <string>
#include <algorithm>



// 0x7f		0000 0000 0111 1111 
// 0x80		0000 0000 1000 0000

// 0x7FF	0000 0111 1111 1111				
// 0xF800	1111 1000 0000 0000


// 0x3F		0000 0000 0011 1111
// 0x7c0	0000 0111 1100 0000
// 0xfc0	0000 1111 1100 0000
// 0xf000	1111 0000 0000 0000 

// 0xDF		0000 0000 1101 1111
// 0xBF		0000 0000 1011 1111
// 0xEF		0000 0000 1110 1111

// 0x80		0000 0000 1000 0000
// 0xc0		0000 0000 1100 0000
// 0xE0		0000 0000 1110 0000
// 0xF0		0000 0000 1111 0000

std::string utf16_to_utf8(const std::wstring& utf16Str) {
	if (utf16Str.empty())
		return std::string("");

	std::string result;
	result.reserve(utf16Str.length());

	for (size_t i = 0; i < utf16Str.length(); i++) {

		unsigned short j = utf16Str[i];
		unsigned char * s = reinterpret_cast<unsigned char *>(&j);

		if (j <= 0x007F) {
			result.push_back(s[0]);
		}
		else if (j > 0x007F && j <= 0x7FF) {
			unsigned char s2 = j & 0x3F;
			unsigned char s1 = ((j & 0x7c0) >> 6);
			s2 |= 0x80;
			s1 |= 0xC0;
			result.push_back(s1);
			result.push_back(s2);
		}
		else if (j > 0x7FF && j < 0xFFFF) {
			unsigned char s1 = (j & 0xf000) >> 12;
			unsigned char s2 = (j & 0xfc0) >> 6;
			unsigned char s3 = j & 0x3f;

			s1 |= 0xE0;
			s2 |= 0x80;
			s3 |= 0x80;

			result.push_back(s1);
			result.push_back(s2);
			result.push_back(s3);
		}
	}
	return result;
}


std::wstring utf8_to_utf16(const std::string& utf8Str) {
	if (utf8Str.empty())
		return std::wstring(L"");

	std::wstring result;
	result.reserve(utf8Str.length());
	const size_t length = utf8Str.length();

	for (size_t i = 0; i < utf8Str.length(); i++) {

		unsigned char a = utf8Str[i];

		if (a <= 0x007F) {
			result.push_back(a);
		}
		else {
			unsigned short part1 = utf8Str[i];
			unsigned short part2 = i + 1 < length ? utf8Str[i + 1] : 0;
			unsigned short part3 = i + 2 < length ? utf8Str[i + 2] : 0;

			if ((part1 & 0xE0) == 0xc0) {
				if ((part2 & 0xC0) != 0x80)
					continue;

				part1 &= 0b11111;
				part1 <<= 6;
				part2 &= 0b111111;

				part1 |= part2;
				result.push_back(part1);
				i++;
			}
			else if ((part1 & 0xF0) == 0xE0) {

				if ((part2 & 0xC0) != 0x80 || (part3 & 0xC0) != 0x80)
					continue;

				part1 &= 0b1111;
				part1 <<= 12;

				part2 &= 0b111111;
				part2 <<= 6;

				part3 &= 0b111111;

				part1 = part1 | part2 | part3;

				result.push_back(part1);
				i += 2;
			}
		}
	}

	return result;
}





int utf_str_main()
{

	std::string s("abcdefg");
	reverse(s.begin(), s.end());

	std::wstring s1(L"abcdefg");

	std::string result = utf16_to_utf8(std::wstring(L"ABCDEFGHIJKLMNOPQRSTUVWSYZabcdefghijklmnopqrstuvwsyz1234567890-= "));

	std::string result1 = utf16_to_utf8(std::wstring(L"Ūn"));

	std::wstring result11 = utf8_to_utf16(result1);
	if (result11 == L"Ūn") {
		int i = 0;
	}

	std::string result2 = utf16_to_utf8(std::wstring(L"统一码"));
	std::wstring result22 = utf8_to_utf16(result2);
	if (result22 == L"统一码") {
		int i = 2;
	}

	return 0;
}
