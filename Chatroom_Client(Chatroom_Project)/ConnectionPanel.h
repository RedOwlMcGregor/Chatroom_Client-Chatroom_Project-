#pragma once
#include <wx/wx.h>

class ConnectionPanel : public wxPanel
{
public:
	ConnectionPanel(wxWindow* parent,
		wxWindowID winid = wxID_ANY,
		const wxString& name = wxASCII_STR(wxPanelNameStr),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize
	);
	std::string GetName();
	std::string GetIp();
	
private:
	wxTextCtrl* userNameField;
	wxTextCtrl* ipField;
};

