#include "../include/App.hpp"
#include "../include/ImageViewer.hpp"
#include <iostream>

const std::pair<std::experimental::filesystem::path,std::experimental::filesystem::path> App::parseArguments(const int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Invalid number of arguments!" << std::endl;
        throw;
    }
    const std::experimental::filesystem::path executable_path = std::string(argv[0]);
    const std::experimental::filesystem::path resource_folder = executable_path.parent_path();
    const std::experimental::filesystem::path file_path = std::string(argv[1]);
    return {resource_folder,file_path};
}

int App::run(const int argc, char* argv[])
{
    std::pair<std::experimental::filesystem::path,std::experimental::filesystem::path> arguments = this->parseArguments(argc,argv);
    const std::experimental::filesystem::path resource_folder = arguments.first;
    const std::experimental::filesystem::path file_path = arguments.second;
    ImageViewer viewer(resource_folder,file_path);
    while(!do_exit)
    {
        switch(viewer.getStatus())
        {
        case ImageViewerStatus::RunFastMode:
            viewer.runFastMode();
            break;
        case ImageViewerStatus::RunPolishedMode:
            viewer.runPolishedMode();
            break;
        case ImageViewerStatus::LeftOk:
            this->do_exit = true;
            break;
        case ImageViewerStatus::Error:
            this->exit_code = 1;
            this->do_exit = true;
        case ImageViewerStatus::OngoingTask:
            break;
        }
    }
    return this->exit_code;
}

App::App(): do_exit(false), exit_code(0) {}
