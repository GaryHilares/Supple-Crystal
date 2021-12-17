#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "ResourceLoader.hpp"
#include "Utils.hpp"
#include <experimental/filesystem>
#include <functional>
#include <unordered_map>
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
    ImageViewerStatus status; // controller
    sf::RenderWindow window; // display
    ImageDisplay image_display; // display
    CyclicalDoublyLinkedList<std::experimental::filesystem::path> files; // files

    ResourceLoader<sf::Font,sf::Image> resource_loader; // display
    const std::unordered_map<std::string,std::function<void()>> functionalities; // controller
    void openImageFromPath(const std::experimental::filesystem::path& filename, bool open_folder = false); // files, controller & display
    static std::string formatWindowTitle(const std::experimental::filesystem::path& file_path, std::string mode); // display
    void updateWindowTitle(std::string mode); // files

public:

    /**
     * @brief Construct a new ImageViewer object.
     * 
     * @param new_resource_folder Folder where assets and other resources are stored.
     * @param new_file_path File to open in the image viewer.
     */
    ImageViewer(const std::experimental::filesystem::path resource_folder, const std::experimental::filesystem::path new_file_path);

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