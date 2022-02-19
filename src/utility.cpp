#include "utility.hpp"

using namespace std;

string utility::wide_to_narrow(const wstring& wide_string) {
	if (wide_string.size() > 1000)
	{
		return string();
	}

	using convert_type = codecvt_utf8<wchar_t>;

	static wstring_convert<convert_type, wchar_t> converter;

	return string{ converter.to_bytes(wide_string) };
}
