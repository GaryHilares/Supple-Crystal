

namespace App
{
    class SuppleCrystal
    {
    public:
        enum class Activity{FastMode, PolishedMode};
    private:
        Activity current_activity;
        int exit_code;
        bool do_exit;
        void runFastMode(const int argc, char* argv[]);
        void runPolishedMode(const int argc, char* argv[]);
    public:
        int run(const int argc, char* argv[]);
    };
}
