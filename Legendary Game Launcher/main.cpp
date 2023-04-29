#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <windows.h>
#include <locale>
#include <codecvt>
#include "launch.h"
#include "gl.h"
#include "input_pause.h"


int main(int argc, char* argv[])
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("game", boost::program_options::value<std::string>(), "Set game id")
        ("sentry", "Enables sentry.io integration")
        ("nogui", "Disables the WIP GUI with OpenGL")
        ;

    boost::program_options::variables_map vm;

    try
    {
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
		boost::program_options::notify(vm);
	}
    catch (boost::program_options::error& e)
    {
		std::cout << e.what() << std::endl;
		return 1;
	}

    if (vm.count("nogui")) {
        std::cout << "Game id was not set. Do you want to set it now? [Y/n]" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "yes" || input == "y") {
            std::cout << "Enter game id: ";
            std::cin >> input;
            std::cout << "Game id was set to " << input << std::endl;
            std::cout << "Launching game..." << std::endl;
            launch(input);
        } 
        return 0;
	}

    if (vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

    if (vm.count("game")) {
        launch(vm["game"].as<std::string>());
    }
    else {
        ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
        gl_window_loader();
        return 0;
	}

    // pause();
    return 0;
}