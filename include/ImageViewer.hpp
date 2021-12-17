#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "Utils.hpp"
#include <unordered_map>
#include <functional>
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
    sf::RenderWindow window; // display
    ImageViewerStatus status; // controller
    ImageDisplay image_display; // display
    CyclicalDoublyLinkedList<std::experimental::filesystem::path> files; // files
    const std::vector<std::string> search_directories; // display
    const sf::Font font; // display
    const sf::Image icon; // display
    /* const */ std::unordered_map<std::string,std::function<void()>> functionalities; // controller
    
    void openImageFromPath(const std::experimental::filesystem::path& filename, bool open_folder = false); // controller
    static std::string formatWindowTitle(const std::experimental::filesystem::path& file_ath, std::string mode); // controller

public:
    void updateWindowTitle(std::string mode);

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