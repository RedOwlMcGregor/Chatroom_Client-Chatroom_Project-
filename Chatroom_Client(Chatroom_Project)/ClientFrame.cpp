#include "ClientFrame.h"



enum IDS // This is used to give customID's 
{
	ConnectB_ID = 1, //ID for the switch button
	DisconnectB_ID = 2
};

wxBEGIN_EVENT_TABLE(ClientFrame, wxFrame) //initiates a event table to add event handling
EVT_BUTTON(ConnectB_ID, ClientFrame::ConnectPressed) //binds the ButtonID to the StartPressed Function
EVT_BUTTON(DisconnectB_ID, ClientFrame::DisconnectPressed)
wxEND_EVENT_TABLE();



ClientFrame::ClientFrame(const wxString& title, Client* client) : wxFrame(nullptr, wxID_ANY, title)
{
	this->client = client;
	connectionError = new wxStaticText(this, wxID_ANY, "Error couldn't connect please check if the ip is correct!", wxPoint(50, 175), wxSize(300, 15));
	connectionError->Hide();
}

void ClientFrame::SetConnectionPanel(wxPanel* panel)
{
	connectionPanel = panel;
	wxButton* connectButton = new wxButton(connectionPanel, ConnectB_ID, "Connect", wxPoint(160, 150), wxSize(60, 20));
	connectionPanel->AddChild(connectionError);
}

void ClientFrame::SetChatPanel(wxPanel* panel)
{
	chatPanel = panel;
	wxButton* Disconnectbutton = new wxButton(chatPanel, DisconnectB_ID, "Disconnect", wxPoint(290, 550), wxSize(70, 20));
}

void ClientFrame::ConnectPressed(wxCommandEvent& evt)
{
	if (client->online == true) return;

	client->Connect();
	if (client->online == false) { connectionError->Show(); return; }
	else { connectionError->Hide(); };

	connectionPanel->Hide();
	chatPanel->Show();

	wxSize pSize = chatPanel->GetSize();
	SetMaxClientSize(pSize);
	SetMinClientSize(pSize);
	SetSize(pSize);
	

}


void ClientFrame::DisconnectPressed(wxCommandEvent& evt)
{
	client->Disconnect();

	chatPanel->Hide();
	connectionPanel->Show();

	wxSize pSize = connectionPanel->GetSize();
	SetMinClientSize(pSize);
	SetMaxClientSize(pSize);
	SetSize(pSize);
}







//else {
//connectionPanel->Show();
//chatPanel->Hide();
//
//wxSize pSize = connectionPanel->GetSize();
//SetMinClientSize(pSize);
//SetMaxClientSize(pSize);
//SetSize(pSize);
//	}



























