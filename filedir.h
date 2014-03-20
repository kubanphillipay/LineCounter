
#include "userstring.h"
#include <windows.h>
#include <iostream>
#include <vector>

#pragma warning (disable : 4786)
#pragma once
#ifndef _fileDir_
#define _fileDir_


struct buffer {

	buffer(String in){
		buf.assign(in.begin(), in.end());
		buf.push_back('\0');
	}

	buffer& setValue(String in){
		buf.clear();
		buf.assign(in.begin(), in.end());
		buf.push_back('\0');
	}

	operator char*(){
		return &buf[0];
	}

	std::vector<char> buf;

};




inline std::vector<buffer> getFullPath(std::vector<String>& fileNames, String directory){
	std::vector<buffer> paths;
	for (unsigned index = 0; index < fileNames.size(); ++index){
		String temp = fileNames[index];
		temp.insert(0, directory);
		paths.push_back(temp);
	}
	return paths;
}

inline std::vector<buffer> getPatternName(std::vector<String>& fileNames){
	std::vector<buffer> names;
	for (unsigned index = 0; index < fileNames.size(); ++index){
		String temp = fileNames[index];
		temp.erase(temp.find_last_of('.'), temp.size());
		names.push_back(buffer(temp));
	}
	return names;
}

inline std::vector<String> stripFullPath(std::vector<String>& fileNames){
	std::vector<String> names;
	for (unsigned index = 0; index < fileNames.size(); ++index){
		String temp = fileNames[index];
		temp.erase(temp.find_last_of('.'), temp.size());
		temp.erase(0, temp.find_last_of('\\') + 1);
		names.push_back(temp);
	}
	return names;
}

inline String stripFullPath(String& fileNames){
	String temp = fileNames;
	temp.erase(temp.find_last_of('.'), temp.size());
	temp.erase(0, temp.find_last_of('\\') + 1);
	return temp;
}

inline std::vector<String> listFiles(String directory, String filter = "*")
{
	String name = directory + filter;
	DWORD d, f;
	WIN32_FIND_DATA FindFileData;
	std::vector<String> listFileNames;
	//wchar_t * FileName = std::string2wchar_t(directoryName);

	
	HANDLE hFind = FindFirstFile(name.c_str(), &FindFileData);
	if( hFind == INVALID_HANDLE_VALUE ){
		std::cout << name << std::endl;
		std::cout << "Error Loading Data" << std::endl;
		return listFileNames;
	}

	//HANDLE hFind = FindFirstFile(FileName, &FindFileData);
	d = FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	f = FindFileData.dwFileAttributes & ( FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY );
	
	if (d)
		listFileNames.push_back(String(FindFileData.cFileName).append("Dir"));

	else if (f)
		listFileNames.push_back(String(directory).append(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData)) {
		d = FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		f = FindFileData.dwFileAttributes & ( FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY );
		if (d)
			listFileNames.push_back(String(FindFileData.cFileName).append("Dir"));

		else if (f)
			listFileNames.push_back(String(directory).append(FindFileData.cFileName));

	}
	return listFileNames;
}


#endif // _fileDir_
