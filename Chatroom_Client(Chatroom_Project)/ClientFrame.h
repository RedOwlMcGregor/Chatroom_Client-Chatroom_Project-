#pragma once
#include <wx/wx.h>
#include "Client.h"

class ConnectionPanel;

class ClientFrame : public wxFrame
{

public:
	ClientFrame(const wxString& title, Client* client);
	void SetConnectionPanel(wxPanel* panel);
	void SetChatPanel(wxPanel* panel);
	void ConnectPressed(wxCommandEvent& evt);
	void DisconnectPressed(wxCommandEvent& evt);
	//void ScaleWindow(wxSize tSize, float timeTaken);
	wxDECLARE_EVENT_TABLE();

private:

	wxPanel* connectionPanel;
	wxPanel* chatPanel;
	wxStaticText* userName;
	std::thread scaleThread;
	wxButton* button;
	bool toggle = false;
	Client* client;
	wxStaticText* connectionError;
};

