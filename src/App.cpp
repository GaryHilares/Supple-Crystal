#include "../include/App.hpp"
#include "../include/ImageViewer.hpp"
#include "../include/MessageBox.hpp"
#include <iostream>

const std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> App::parseArguments(const int argc, char* argv[])
{
    if (argc != 2)
        throw std::runtime_error("Invalid number of arguments!");
    const std::experimental::filesystem::path executablePath = std::string(argv[0]);
    const std::experimental::filesystem::path resourceFolder = executablePath.parent_path();
    const std::experimental::filesystem::path filePath = std::string(argv[1]);
    return { resourceFolder, filePath };
}

int App::run(const int argc, char* argv[])
{
    try {
        std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> arguments = this->parseArguments(argc, argv);
        const std::experimental::filesystem::path resourceFolder = arguments.first;
        std::experimental::filesystem::path filePath = arguments.second;
        ImageViewer viewer(resourceFolder);
        while (!m_doExit) {
            switch (viewer.getStatus()) {
            case ImageViewerStatus::RunFastMode:
                filePath = viewer.runFastMode(filePath).second;
                break;
            case ImageViewerStatus::RunPolishedMode:
                filePath = viewer.runPolishedMode(filePath).second;
                break;
            case ImageViewerStatus::LeftOk:
                m_doExit = true;
                break;
            case ImageViewerStatus::Error:
                m_exitCode = 1;
                m_doExit = true;
                break;
            case ImageViewerStatus::OngoingTask:
                throw std::runtime_error("OngoingTask: Something was not expected to happen");
            case ImageViewerStatus::NothingAssigned:
                filePath = viewer.runFastMode(filePath).second;
                break;
            }
        }
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        if (argc >= 1) {
            const std::experimental::filesystem::path executablePath = std::string(argv[0]);
            const std::experimental::filesystem::path resourceFolder = executablePath.parent_path();
            std::optional<sf::Font> loadingObject = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf", { resourceFolder.string() + "/", "", "C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/" });
            if (loadingObject.has_value())
                MessageBox("Error", error.what(), loadingObject.value());
            else
                std::cerr << "Couldn't load error message box font." << std::endl;
        } else {
            std::cerr << "The program received less than 1 argument." << std::endl;
        }
        m_exitCode = 1;
    }
    return m_exitCode;
}

App::App()
    : m_doExit(false)
    , m_exitCode(0)
{
}
