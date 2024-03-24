#include <windows.h>
#include "Application.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CApplication app("tetris");

	app.Run();

	return 0;
}