#pragma once
#include <string>
#include <utility>
#include <experimental/filesystem>

/**
 * @brief Class that manages the application.
 * 
 */
class App
{
private:
    bool do_exit;
    int exit_code;
    /**
     * @brief Parses the arguments and extracts the important data.
     * 
     * @param argc Amount of arguments.
     * @param argv Program arguments.
     * @return std::pair<std::string,std::string> The path to the executable and the path of the image to open.
     */
    const std::pair<std::experimental::filesystem::path,std::experimental::filesystem::path> parseArguments(const int argc, char* argv[]);
    
public:
    /**
     * @brief Construct a new App object
     */
    App();

    /**
     * @brief Runs the App.
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
     * @return int The app exit code.
     */
    int run(const int argc, char* argv[]);
};
