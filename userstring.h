
#pragma once

#ifdef __WXMSW__

#include <wx/string.h>
typedef wxString String;

inline String& trimWhiteSpace(String& str){
	while (int pos = str.find_first_of(" \n\r\t") != std::string::npos)
		str.erase(pos, 1);
	return str;
}

inline String& leftTrim(String& str){
	int pos = str.find_first_not_of(" \n\r\t");
	str.erase(0, pos);
	return str;
}

#else

#include <string>

#ifdef UNICODE

typedef std::wstring String;

#else

typedef std::string String;

#endif


#endif