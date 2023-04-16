#include <iostream>
#include <string>
#include <windows.h>
#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("gameid", boost::program_options::value<int>(), "Set game id")
        ;

    boost::program_options::variables_map vm;

    try
    {
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);
	}
    catch (boost::program_options::error& e)
    {
		std::cout << e.what() << std::endl;
		return 1;
	}

    if (vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

    if (vm.count("game")) {
        std::cout << "Game id was set to " << vm["gameid"].as<int>() << std::endl;
    }
    else {
		std::cout << "Game id was not set. Do you want to set it now?" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "yes" || input == "y") {
			std::cout << "Enter game id: ";
			std::cin >> input;
			std::cout << "Game id was set to " << input << std::endl;
		}
        else {
			std::cout << "Game id was not set. Exiting..." << std::endl;
			return 1;
        }

	}

    std::cout << "Hello World!\n";
}

