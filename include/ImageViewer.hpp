#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "Utils.hpp"
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>

/**
 * @brief Statuses that the ImageViewer may have.
 * 
 */
enum class ImageViewerStatus{
    NothingAssigned,
    LeftOk,
    Error,
    RunPolishedMode,
    RunFastMode,
    OngoingTask
};

/**
 * @brief Class which manages the image viewer.
 * 
 */
class ImageViewer
{
private:
    const std::experimental::filesystem::path resource_folder;
    ImageViewerStatus status;
    ImageDisplay image_display;
    CyclicalDoublyLinkedList<std::experimental::filesystem::path> files;
    void openImageFromPath(const std::experimental::filesystem::path& filename, bool open_folder = false);

public:
    ImageViewer(const std::experimental::filesystem::path new_resource_folder, const std::experimental::filesystem::path new_file_path);

    /**
     * @brief Runs the ImageViewer on "Fast mode".
     * 
     */
    void runFastMode();

    /**
     * @brief Runs the ImageViewer on "Polished mode".
     * 
     */
    void runPolishedMode();

    /**
     * @brief Gets the most recent status of the ImageViewer object.
     * 
     * @return ImageViewerStatus The most recent status of the ImageViewer object.
     */
    ImageViewerStatus getStatus();
};