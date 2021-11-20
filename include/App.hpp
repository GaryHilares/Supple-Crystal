#pragma once
#include <string>
#include <utility>

class App
{
private:
    enum class Activity{FastMode, PolishedMode};
    bool do_exit;
    int exit_code;
    Activity current_activity;
    /**
     * @brief Parses the arguments and extracts the important data.
     * 
     * @param argc Amount of arguments.
     * @param argv Program arguments.
     * @return std::pair<std::string,std::string> The path to the executable and the path of the image to open.
     */
    const std::pair<std::string,std::string> parseArguments(const int argc, char* argv[]);
    
    /**
     * @brief Runs the App on "Fast mode".
     * 
     * @param folder_path The path to the executable.
     * @param argv The path of the image to open.
     */
    void runFastMode(const std::string folder_path, const std::string filename);

    /**
     * @brief Runs the App on "Polished mode".
     * 
     * @param folder_path The path to the executable.
     * @param argv The path of the image to open.
     */
    void runPolishedMode(const std::string folder_path, const std::string filename);

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
