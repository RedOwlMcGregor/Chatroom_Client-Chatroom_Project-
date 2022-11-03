#include "App.h"
#include "ClientFrame.h"
#include "ConnectionPanel.h"
#include "ClientPanel.h"
#include <wx/wx.h>
#include "Client.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	Client* client = new Client();

	return true;
}

