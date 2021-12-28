#include "../include/App.hpp"
#include "../include/ImageViewer.hpp"
#include "../include/MessageBox.hpp"
#include <iostream>

const std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> App::parseArguments(const int argc, char* argv[])
{
    if (argc != 2)
        throw std::runtime_error("Invalid number of arguments!");
    const std::experimental::filesystem::path executable_path = std::string(argv[0]);
    const std::experimental::filesystem::path resource_folder = executable_path.parent_path();
    const std::experimental::filesystem::path file_path = std::string(argv[1]);
    return { resource_folder, file_path };
}

int App::run(const int argc, char* argv[])
{
    try {
        std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> arguments = this->parseArguments(argc, argv);
        const std::experimental::filesystem::path resource_folder = arguments.first;
        std::experimental::filesystem::path file_path = arguments.second;
        ImageViewer viewer(resource_folder);
        while (!do_exit) {
            switch (viewer.getStatus()) {
            case ImageViewerStatus::RunFastMode:
                file_path = viewer.runFastMode(file_path).second;
                break;
            case ImageViewerStatus::RunPolishedMode:
                file_path = viewer.runPolishedMode(file_path).second;
                break;
            case ImageViewerStatus::LeftOk:
                this->do_exit = true;
                break;
            case ImageViewerStatus::Error:
                this->exit_code = 1;
                this->do_exit = true;
                break;
            case ImageViewerStatus::OngoingTask:
                throw std::runtime_error("OngoingTask: Something was not expected to happen");
            case ImageViewerStatus::NothingAssigned:
                file_path = viewer.runFastMode(file_path).second;
                break;
            }
        }
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        if (argc >= 1) {
            const std::experimental::filesystem::path executable_path = std::string(argv[0]);
            const std::experimental::filesystem::path resource_folder = executable_path.parent_path();
            std::optional<sf::Font> loading_object = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf", { resource_folder.string() + "/", "", "C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/" });
            if (loading_object.has_value())
                MessageBox("Error", error.what(), loading_object.value());
            else
                std::cerr << "Couldn't load error message box font." << std::endl;
        } else {
            std::cerr << "The program received less than 1 argument." << std::endl;
        }
        this->exit_code = 1;
    }
    return this->exit_code;
}

App::App()
    : do_exit(false)
    , exit_code(0)
{
}
