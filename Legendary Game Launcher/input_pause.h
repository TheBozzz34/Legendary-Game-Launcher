#include <iostream>
#include <limits>

class Pause {
public:
    void operator()() const {
        std::cin.clear();
        std::cout << "Press enter to continue...";
        std::cin.get();
        std::cout << "Continuing..." << std::endl;
    }
};