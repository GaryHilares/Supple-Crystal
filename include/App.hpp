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
    std::pair<std::string,std::string> parseArguments(const int argc, char* argv[]);
    /**
     * @brief Runs the App on "Fast mode".
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
     */
    void runFastMode(const std::string folder_path, const std::string filename);
    /**
     * @brief Runs the App on "Polished mode".
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
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
