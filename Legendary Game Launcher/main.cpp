#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <windows.h>
#include <locale>
#include <codecvt>
#include "launch.h"
#include <sentry.h>
#include "gl.h"

#define SENTRY_BACKEND "crashpad"

int main(int argc, char* argv[])
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("game", boost::program_options::value<std::string>(), "Set game id")
        ("sentry", "Enables sentry.io integration")
        ("glad", "Launches a window with OpenGL")
        ("wireframe", boost::program_options::value<bool>()->default_value(false), "Render OpenGL in wireframe mode, default FALSE");
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

    if (vm.count("sentry")) {
        sentry_options_t* options = sentry_options_new();
        sentry_options_set_dsn(options, "https://b42995416ca4449e8740efd79c672f12@o561860.ingest.sentry.io/4505041508696064");
        // This is also the default-path. For further information and recommendations:
        // https://docs.sentry.io/platforms/native/configuration/options/#database-path
        sentry_options_set_database_path(options, ".sentry-native");
        sentry_options_set_release(options, "legendary-game-launcher@1.1");
        sentry_options_set_debug(options, true);
        sentry_init(options);

	} 

    if (vm.count("glad")) {
		gl_window_loader(vm["wireframe"].as<bool>());
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
        else {
			std::cout << "Game id was not set. ";
            system("pause");
			return 1;   
        }
	}

    std::cout << "Finished all tasks. Press any key to exit..." << std::endl;
    std::string blah;
    std::cin >> blah;
    glfwTerminate();
    return 0;
}