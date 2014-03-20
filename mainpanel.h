#pragma once

#include <wx/wx.h>
#include <vector>
#include "filedir.h"
#include "userstring.h"
#include "calclines.h"

class MainPanel : public wxPanel {

public:
	MainPanel(wxFrame* parent);

	void onRun(wxEvent& event);
	void onBrowse(wxEvent& event);
	//void onUnBind(wxEvent& event);
	//void unBind();

private:
	void addInterface();
	
	//wxButton* Button2;
	
	wxTextCtrl* txt2;
	wxTextCtrl* outputTextCtrl;

	wxButton* runButton;
	wxCheckBox* cppCheckBox;
	wxCheckBox* hCheckBox;
	wxTextCtrl* directoryTextCtrl;
	wxButton* browseButton;

	enum BUTTONS { BUTTON1, BUTTON2 };


};