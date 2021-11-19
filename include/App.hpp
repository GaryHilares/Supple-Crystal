#pragma once

class App
{
private:
    enum class Activity{FastMode, PolishedMode};
    bool do_exit;
    int exit_code;
    Activity current_activity;
    /**
     * @brief Runs the App on "Fast mode".
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
     */
    void runFastMode(const int argc, char* argv[]);
    /**
     * @brief Runs the App on "Polished mode".
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
     * @throws Never throws.
     */
    void runPolishedMode(const int argc, char* argv[]);
public:
    /**
     * @brief Construct a new App object
     * @throw Never throws.
     */
    App();
    /**
     * @brief Runs the App.
     * 
     * @param argc The amount of program arguments.
     * @param argv Program arguments.
     * @return int The app exit code.
     * @throws Never throws
     */
    int run(const int argc, char* argv[]);
};
