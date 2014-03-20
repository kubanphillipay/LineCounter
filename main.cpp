
#include <wx/wx.h>
#include "mainpanel.h"
 
class MyApp : public wxApp
{
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	MainPanel* myPanel;
};

enum
{
	ID_Quit = 1,
	ID_About
};


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame(_("Program Line Counter"), wxPoint(50, 50),
		wxSize(600, 350));

	frame->Connect(ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction)&MyFrame::OnQuit);
	frame->Connect(ID_About, wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction)&MyFrame::OnAbout);

	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, -1, title, pos, size)
{
	wxMenuBar *menuBar = new wxMenuBar;

	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_About, _("&About..."));
	menuFile->AppendSeparator();
	menuFile->Append(ID_Quit, _("E&xit"));

	menuBar->Append(menuFile, _("&File"));

	myPanel = new MainPanel(this);


	SetMenuBar(menuBar);

	CreateStatusBar();

	SetStatusText(_("Don't be a doofus!"));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(_("Simple Program Line Counter.\n"
		"Notes:\n"
		" -Calulates lines of code, empty lines and comments in c++ programs.\n"
		" -//Style comments at the end of lines will be counted twice"
			" as both code and comments.\n"
		" -/* Style comments are only counted if they start the line.\n"
		" -Every line between the /* and */ is counted as comments\n"
		" -*/ Ending comments that do not start are not recognized! This is a \"bug\".\n"
		"    -This may cause the program to think everything is a comment.\n"
		"    -It would take a significant amount of time to fix so I leaving as is.\n"
		),
		_("About Simple Line Counter"),
		wxOK | wxICON_INFORMATION, this);
}
