#include "Client.h"
#include <iostream>
#include <thread>
#include <vector>
#include <inaddr.h>
#include <ws2tcpip.h>
#include "ClientFrame.h"
#include "ClientPanel.h"
#include "ConnectionPanel.h"
#include <string> 
#include <stdio.h>
#include <wx/wx.h>

enum IDS // This is used to give customID's 
{
	LISTEN_TIMER = 1,
};



Client::Client()
{
	clientFrame = new ClientFrame("Client Window", this);
	connectionPanel = new ConnectionPanel(clientFrame, wxID_ANY, "Connection panel", wxPoint(0, 0), wxSize(400, 200));
	clientPanel = new ClientPanel(clientFrame, wxID_ANY, "Hell Yeah it's the ChatPanel", wxPoint(0, 0), wxSize(400, 600));

	clientPanel->Hide();

	clientFrame->SetChatPanel(clientPanel);
	clientFrame->SetConnectionPanel(connectionPanel);

	clientFrame->Show();

	clientPanel->sendBox->Bind(wxEVT_TEXT_ENTER, &Client::SentMessage, this);


}

void Client::Connect()
{
	name = connectionPanel->GetName();

	ip = connectionPanel->GetIp();

	WORD wVersionNeeded = MAKEWORD(2, 2);

	int wsaerr = WSAStartup(wVersionNeeded, &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in service;

	service.sin_family = AF_INET;

	inet_pton(AF_INET, ip.c_str(), &service.sin_addr.s_addr);

	service.sin_port = htons(25565);

	if (connect(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		this->online = false;
	}
	else
	{
		const char* nameSendBuffer = name.c_str();
		
		int nameSendLength = strlen(nameSendBuffer);

		send(clientSocket, nameSendBuffer, nameSendLength, 0);
		clientPanel->AddText("Connected \n");
		online = true;

		JoinedMessage();

		this->listenInterval = new wxTimer(clientFrame, this->timerID);
		clientFrame->Bind(wxEVT_TIMER, [this](wxTimerEvent&)
			{
				appendMessage();
			}, timerID);

		this->listenInterval->Start(1, wxTIMER_CONTINUOUS);

		receiveAndSendThread = std::thread(&Client::Receive, this);

		
	}

}

void Client::Receive()
{
	while (online)
	{
		char receiveBuffer[200] = "";
		int byteAmount = recv(clientSocket, receiveBuffer, 200, 0);
		if (byteAmount > 0)
		{
			message = std::string(receiveBuffer);
		}
	}
}

void Client::SentMessage(wxCommandEvent& evt)
{
	wxString evtString = wxString::Format(evt.GetString());

	std::string message = std::string(evtString.mb_str());

	const char* messageBuffer = message.c_str();

	int sendL = strlen(messageBuffer);

	int r = send(clientSocket, messageBuffer, sendL, 0);

	clientPanel->sendBox->Clear();
}

void Client::appendMessage()
{

	if (previousMessage != message)
	{
		int wrapAmount = 50;
		const int spaceSearchLength = 16;

		if (message.size() > wrapAmount)
		{
			for (int i = wrapAmount - 1; i < message.size(); i += wrapAmount)
			{
				bool spaceFound = false;

				for (int j = i; j > (i - spaceSearchLength); j--)
				{

					if (isspace(message[j]))
					{

						spaceFound = true;
						i = j;
						message = message.substr(0, j) + '\n' + message.substr(j, message.size());

						break;
					}
				}

				if (!spaceFound)
				{
					message = message.substr(0, i) + '\n' + message.substr(i, message.size());
				}
			}


		}


		clientPanel->AddText(message);
		previousMessage = message;
	}
}

void Client::JoinedMessage()
{
	if(message.find("joined") && previousMessage.find("joined"))
	{ 
		char receiveBuffer[200] = "";
		int byteAmount = recv(clientSocket, receiveBuffer, 200, 0);
		clientPanel->AddText(receiveBuffer);
	}
	
}

void Client::Disconnect()
{
	
	receiveAndSendThread.detach();
	online = false;
	clientPanel->chatPanel->DestroyChildren();
	closesocket(this->clientSocket);
	WSACleanup();
}


