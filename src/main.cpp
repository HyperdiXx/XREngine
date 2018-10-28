
#include "SetupCom.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdline, int Cmdshow)
{
	bool s;
	SetupCom* system = new SetupCom;

	s = system->Init();
	if(s)
	{
		system->Start();
	}
	

	system->Release();
	delete system;
	system = NULL;

	return (0);
}



