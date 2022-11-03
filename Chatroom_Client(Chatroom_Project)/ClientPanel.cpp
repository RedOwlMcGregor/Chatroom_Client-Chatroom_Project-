#include "ClientPanel.h"
#include "wx/wx.h"
#include "Client.h"

ClientPanel::ClientPanel(wxWindow* parent, wxWindowID winid, const wxString& name, const wxPoint& pos, const wxSize& size) : wxPanel(parent, winid, pos, size, wxNO_BORDER, name)
{
	this->client = client;

	chatPanel = new wxScrolledWindow(this, wxID_ANY, wxPoint(20, 20), wxSize(380, 520));
	chatPanel->SetBackgroundColour(wxColour(33, 33, 35));
	chatPanel->Center();
	chatPanel->SetPosition(wxPoint(chatPanel->GetPosition().x, chatPanel->GetPosition().y - 40));

	sizer = new wxBoxSizer(wxVERTICAL);

	chatPanel->FitInside();
	chatPanel->SetScrollRate(2, 2);
	chatPanel->SetSizer(sizer);

	sendBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 535), wxSize(250, 50), wxTE_PROCESS_ENTER | wxTE_MULTILINE);

}


wxStaticText* ClientPanel::AddText(std::string inText)
{
	wxStaticText* text = NULL;

	if (chatPanel->GetChildren().GetCount() == 0) {
		text = new wxStaticText(chatPanel, wxID_ANY, "   >> " + inText, wxPoint(0, 0));
	}
	else {
		wxWindow* l = chatPanel->GetChildren().back();
		text = new wxStaticText(chatPanel, wxID_ANY, "   >> " + inText, wxPoint(0, l->GetPosition().y + l->GetSize().y));
	}

	text->SetForegroundColour(wxColor(255, 255, 255));

	this->Refresh();
	this->Update();


	chatPanel->FitInside();

	sizer->Add(text, 0, wxLeft);

	return text;
}


