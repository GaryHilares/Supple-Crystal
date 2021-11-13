#pragma once

namespace App
{
    class SuppleCrystal
    {
    public:
        enum class Activity{FastMode, PolishedMode};
    private:
        bool do_exit;
        int exit_code;
        Activity current_activity;
        void runFastMode(const int argc, char* argv[]);
        void runPolishedMode(const int argc, char* argv[]);
    public:
        SuppleCrystal();
        int run(const int argc, char* argv[]);
    };
}
