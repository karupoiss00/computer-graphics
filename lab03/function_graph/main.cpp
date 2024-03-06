#include <windows.h>
#include "Application.h"

CMyApplication app("test");

int _tmain(int argc, _TCHAR* argv[])
{
	app.MainLoop();

	return 0;
}