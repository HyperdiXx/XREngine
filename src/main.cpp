#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include "crtdbg.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

/*#include "core\SystemSetup\SetupCom.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdline, int Cmdshow)
{
#ifdef _DEBUG
	_CrtMemState _msBegin, _msEnd, _msDiff;
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtMemCheckpoint(&_msBegin);
#endif
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

	

#ifdef _DEBUG
	_CrtMemCheckpoint(&_msEnd);

	if (_CrtMemDifference(&_msDiff, &_msBegin, &_msEnd) > 0) {
		_CrtDumpMemoryLeaks();
		std::system("pause");
	}
#endif
	
}*/



