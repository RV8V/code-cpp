#include "app_ns.h"

INT CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, INT)
{
	c_app app{};
	return app.run();
}