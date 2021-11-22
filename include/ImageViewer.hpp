#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "Utils.hpp"
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>

enum class ImageViewerStatus{
    NothingAssigned,
    LeftOk,
    Error,
    RunPolishedMode,
    RunFastMode,
    OngoingTask
};

class ImageViewer
{
private:
    const std::experimental::filesystem::path resource_folder;
    ImageViewerStatus status;
    ImageDisplay image_display;
    CiclicalIterator<std::experimental::filesystem::path> files;
    void openImageFromPath(const std::experimental::filesystem::path& filename, bool open_folder = false);

public:
    ImageViewer(const std::experimental::filesystem::path new_resource_folder, const std::experimental::filesystem::path new_file_path);

    /**
     * @brief Runs the App on "Fast mode".
     * 
     * @param folder_path The path to the executable.
     * @param argv The path of the image to open.
     */
    void runFastMode();

    /**
     * @brief Runs the App on "Polished mode".
     * 
     * @param folder_path The path to the executable.
     * @param argv The path of the image to open.
     */
    void runPolishedMode();

    ImageViewerStatus getStatus();
};