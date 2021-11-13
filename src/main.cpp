#include "../include/App.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Invalid number of arguments!" << std::endl;
        return 1;
    }
    App::SuppleCrystal app;
    return app.run(argc,argv);
}
