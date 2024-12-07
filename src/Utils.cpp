#include "Utils.h"
#include <Engine/Config.h>
#include <loguru.hpp>
#ifdef __SWITCH__
#include <switch.h>
#endif

#include <fstream>

void Utils::initLog(int argc, char** argv)
{
	Engine::Config::initLog(argc, argv);

#ifdef _DEBUG
	loguru::g_stderr_verbosity = loguru::Verbosity_MAX;
#else
	loguru::g_stderr_verbosity = loguru::Verbosity_ERROR;
#endif

	//Force to max because switch hard to debug
#ifdef __SWITCH__
	loguru::g_stderr_verbosity = loguru::Verbosity_MAX;
#endif

	if (Engine::Config::lograw)
	{
		loguru::g_preamble = false;
	}
	else
	{
		loguru::g_preamble_uptime = false;
		loguru::g_preamble_date = false;
		loguru::g_preamble_thread = true;
		loguru::g_preamble_verbose = false;
	}

	//init important for crash logging
	loguru::init(argc, argv);
	//Init sets to main thread by default
	loguru::set_thread_name("App Thread");

	if (Engine::Config::logfile)
		loguru::add_file("game.log", loguru::Truncate, loguru::Verbosity_INFO);

	//Logging tests/examples
	//LOG_F(INFO, "I'm hungry for some %.3f!", 3.14159);
	//LOG_S(INFO) << "Some float: " << 3.14;
	//LOG_S(ERROR) << "My vec3: " << 3.14;
	//LOG_S(ERROR) << loguru::stacktrace(1).c_str();
	//tracetest();

	//LOG_SCOPE_FUNCTION(INFO);
	//VLOG_SCOPE_F(1, "Iteration %d", 5);
}

#ifdef __SWITCH__
void Utils::switchInit()
{
	//Log to Ryujinx
	consoleDebugInit(debugDevice_SVC);

	//Log to nxlink on actual hardware
	socketInitializeDefault();
	nxlinkStdio();
	//use cerr for both to work

	//Running off sd card now so no romfs
	/*Result rc = romfsInit();
	if (R_FAILED(rc))
		printf("romfsInit: %08X\n", rc);
	chdir("romfs:/");*/

	chdir("/switch/PhantomDogs/");
}
#endif

//Hack to get vita paths correct.
//TODO: find way to wrap SDL IMG_Load
std::ifstream Utils::loadFile(std::string path)
{
	return loadFile(path, std::ios::in | std::ios::binary | std::ios::ate);
}
std::ifstream Utils::loadFile(std::string path, std::ios_base::openmode mode = std::ios::in | std::ios::binary | std::ios::ate)
{
#ifdef __VITA__
	return std::ifstream("ux0:/data/Phantom Dogs/" + path, mode);
#endif
#ifndef __VITA__
	return std::ifstream(path, mode);
#endif
}