#include "ConnectionPanel.h"
#include <wx/wx.h>



ConnectionPanel::ConnectionPanel(wxWindow* parent, wxWindowID winid, const wxString& name, const wxPoint& pos, const wxSize& size) : wxPanel(parent, winid, pos, size, wxNO_BORDER, name)
{
	wxStaticText* userNameText = new wxStaticText(this, wxID_ANY, "Username:", wxPoint(50, 51), wxSize(60, 30));
	userNameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(115, 50), wxSize(100, 20));
	wxStaticText* ipText = new wxStaticText(this, wxID_ANY, "IP:", wxPoint(93, 82), wxSize(60, 15));
	ipField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(115, 80), wxSize(100, 20));
}

std::string ConnectionPanel::GetName()
{
	std::string name = userNameField->GetValue().ToStdString();
	return name;
}

std::string ConnectionPanel::GetIp()
{
	std::string ip = ipField->GetValue().ToStdString();
	return ip;
}

