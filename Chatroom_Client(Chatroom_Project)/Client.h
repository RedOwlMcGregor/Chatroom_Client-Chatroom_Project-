#pragma once
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <vector>


class ClientPanel;
class ConnectionPanel;
class ClientFrame;
class wxTimer;
class wxCommandEvent;

class Client
{
public:
	Client();
	void Connect();
	void Receive();
	void SentMessage(wxCommandEvent& evt);
	void appendMessage();
	void JoinedMessage();
	void Disconnect();
	bool online = false;
	
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	int wsaerr;
	sockaddr_in service;
	ClientFrame* clientFrame;
	ConnectionPanel* connectionPanel;
	std::thread receiveAndSendThread;
	wxTimer* listenInterval;
	static constexpr int timerID = 6612;
	std::string message;
	std::string previousMessage;
	ClientPanel* clientPanel;
	std::string name;
	std::string ip;
};

