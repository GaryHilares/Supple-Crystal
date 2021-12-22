#include "../include/UI/Elements/Displays/ImageDisplay.hpp"
#include "ResourceLoader.hpp"
#include "Utils/CyclicalDoublyLinkedList.hpp"
#include <SFML/Graphics.hpp>
#include <experimental/filesystem>
#include <functional>
#include <optional>
#include <unordered_map>

/**
 * @brief Statuses that the ImageViewer may have.
 *
 */
enum class ImageViewerStatus {
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
class ImageViewer {
private:
    ImageViewerStatus status;
    sf::RenderWindow window;
    ImageDisplay image_display;
    CyclicalDoublyLinkedList<std::experimental::filesystem::path> files;
    std::optional<std::experimental::filesystem::path> loadedFolder;
    std::string mode;

    ResourceLoader<sf::Font, sf::Image> resource_loader;
    const std::unordered_map<std::string, std::function<void()>> functionalities;
    void openImageFromPath(const std::experimental::filesystem::path& filename);
    static std::string formatWindowTitle(const std::experimental::filesystem::path& file_path, const std::string mode);
    static bool isSupportedImageType(std::experimental::filesystem::path file);
    void updateWindowTitle(std::experimental::filesystem::path new_file_path);

public:
    /**
     * @brief Construct a new ImageViewer object.
     *
     * @param new_resource_folder Folder where assets and other resources are stored.
     * @param new_file_path File to open in the image viewer.
     */
    ImageViewer(const std::experimental::filesystem::path resource_folder);

    /**
     * @brief Runs the ImageViewer on "Fast mode".
     *
     */
    std::pair<ImageViewerStatus, std::experimental::filesystem::path> runFastMode(const std::experimental::filesystem::path new_file_path);

    /**
     * @brief Runs the ImageViewer on "Polished mode".
     *
     */
    std::pair<ImageViewerStatus, std::experimental::filesystem::path> runPolishedMode(const std::experimental::filesystem::path new_file_path);

    /**
     * @brief Gets the most recent status of the ImageViewer object.
     *
     * @return ImageViewerStatus The most recent status of the ImageViewer object.
     */
    ImageViewerStatus getStatus();
};