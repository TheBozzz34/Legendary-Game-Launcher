#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <windows.h>
#include <locale>
#include <codecvt>

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
        std::cout << "Launching game..." << std::endl;

        std::string command = "C:\\Users\\sansm\\bin\\legendary.exe launch " + vm["gameid"].as<int>();

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wstr = converter.from_bytes(command);


        STARTUPINFOW si = { 0 };
        si.cb = sizeof(STARTUPINFOW);
        PROCESS_INFORMATION pi = { 0 };

        BOOL success = CreateProcessW(NULL, const_cast<wchar_t*>(wstr.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        if (!success) {
            std::cerr << "Failed to start process. Error code: " << GetLastError() << std::endl;
            system("pause");
            return 1;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode = 0;
        if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
            std::cerr << "Failed to get process exit code. Error code: " << GetLastError() << std::endl;
            system("pause");
        }
        else {
            std::cout << "Process exited with code " << exitCode << std::endl;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        
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

            std::string command = "C:\\Users\\sansm\\bin\\legendary.exe launch " + input;

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wstr = converter.from_bytes(command);


            STARTUPINFOW si = { 0 };
            si.cb = sizeof(STARTUPINFOW);
            PROCESS_INFORMATION pi = { 0 };

            BOOL success = CreateProcessW(NULL, const_cast<wchar_t*>(wstr.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
            if (!success) {
                std::cerr << "Failed to start process. Error code: " << GetLastError() << std::endl;
                system("pause");
                return 1;
            }

            WaitForSingleObject(pi.hProcess, INFINITE);

            DWORD exitCode = 0;
            if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
                std::cerr << "Failed to get process exit code. Error code: " << GetLastError() << std::endl;
                system("pause");
            }
            else {
                std::cout << "Process exited with code " << exitCode << std::endl;
            }

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
     
            
		}
        else {
			std::cout << "Game id was not set. Exiting..." << std::endl;
            system("pause");
			return 1;   
        }

	}

    std::cout << "Finished all tasks. Exiting..." << std::endl;
    system("pause");
    return 0;
}