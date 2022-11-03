#pragma once
#include <wx/wx.h>
#include <vector>
#include <thread>
#include "Client.h"
class ClientPanel : public wxPanel
{
public:
	ClientPanel(wxWindow* parent, wxWindowID winid, const wxString& name, const wxPoint& pos, const wxSize& size);

	wxStaticText* AddText(std::string inText);

	wxTextCtrl* sendBox;

	wxScrolledWindow* chatPanel;

private:
	wxBoxSizer* sizer;
	
	Client* client;
	
	wxButton* sendButton;
};

