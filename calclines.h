#pragma once

#include "userstring.h"
#include "filedir.h"
#include <iostream>
#include <vector>
#include <wx/textfile.h>

struct LineCountData {
	LineCountData(String name) : fileName(name) {	
		empty = 0;
		code = 0;
		comment = 0;
		lineCount = 0; 	
	}
	LineCountData& setEmpty(int empty) {
		this->empty = empty;
		return *this;
	}
	LineCountData& setCode(int code) {
		this->code = code;
		return *this;
	}
	LineCountData& setComment(int comment) {
		this->comment = comment;
		return *this;
	}
	void print(){
		using namespace std;
		cout << "File: " << fileName << endl;
		cout << "Total Lines: " << lineCount << endl;
		cout << "Code Lines:" << code << endl;
		cout << "Comment Lines:" << comment << endl;
		cout << "Empty Lines:" << empty << endl;
	}

	String fileName;
	unsigned empty;
	unsigned code;
	unsigned comment;
	unsigned lineCount;
};

LineCountData& calculateLineCountData(String& line, LineCountData& lineCountData, bool& comment_block);
std::vector<LineCountData> calculateLineCount(std::vector<String> fileNames);

inline std::vector<LineCountData> calculateLineCount(std::vector<String> fileNames){
	using namespace std;
	std::vector<LineCountData> lineCount;

	for (String str : fileNames){
		cout << "Processing:" << endl;
		String shortName = stripFullPath(str);
		cout << "  " << str << endl;	
		LineCountData lineCountData(shortName);

#ifdef __WXMSW__
		wxTextFile file;
		file.Open(str);

		if (!file.Exists()){
			cout << "Error file does not exist" << endl;
			return lineCount;
		}
		
		bool comment_block = false;	
		for (String line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()){
			calculateLineCountData(line, lineCountData, comment_block);
		}
		lineCountData.print();
		lineCount.push_back(lineCountData);
	}
	
	return lineCount;
#else

		cout << "Error wxWidgets not defined!  Code not completed!"

#endif

}

inline LineCountData& calculateLineCountData(String& line, LineCountData& lineCountData , bool& comment_block ){
	leftTrim(line);
	++lineCountData.lineCount;
	if (line.find("/*")==0)
		comment_block = true;

	//while not in a comment block
	if (!comment_block){
		if (line.find("//") == 0){
			++lineCountData.comment;
			//std::cout << line << std::endl;
		}
		else if (line.empty())
			++lineCountData.empty;
		else{
			++lineCountData.code;
			//check if a comment is at the end of the line, count twice!
			if (line.find("//") != std::string::npos){
				//std::cout << "same line comment!" << std::endl; // like this
				++lineCountData.comment; // or this;
			}
		}
	}
	else {
		++lineCountData.comment;
		if (line.find("*/") == std::string::npos)
			comment_block = false;
	}

	return lineCountData;


}
