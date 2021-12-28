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
    ImageViewerStatus m_status;
    sf::RenderWindow m_window;
    ImageDisplay m_imageDisplay;
    CyclicalDoublyLinkedList<std::experimental::filesystem::path> m_files;
    std::optional<std::experimental::filesystem::path> m_loadedFolder;
    std::string m_mode;
    ResourceLoader<sf::Font, sf::Image> m_resourceLoader;
    const std::unordered_map<std::string, std::function<void()>> m_functionalities;

    void openImageFromPath(const std::experimental::filesystem::path& filename);
    static std::string formatWindowTitle(const std::experimental::filesystem::path& filePath, const std::string mode);
    static bool isSupportedImageType(std::experimental::filesystem::path file);
    void updateWindowTitle(std::experimental::filesystem::path newFilePath);

public:
    /**
     * @brief Construct a new ImageViewer object.
     *
     * @param new_resource_folder Folder where assets and other resources are stored.
     * @param new_file_path File to open in the image viewer.
     */
    ImageViewer(const std::experimental::filesystem::path resourceFolder);

    /**
     * @brief Runs the ImageViewer on "Fast mode".
     *
     */
    std::pair<ImageViewerStatus, std::experimental::filesystem::path> runFastMode(const std::experimental::filesystem::path newFilePath);

    /**
     * @brief Runs the ImageViewer on "Polished mode".
     *
     */
    std::pair<ImageViewerStatus, std::experimental::filesystem::path> runPolishedMode(const std::experimental::filesystem::path newFilePath);

    /**
     * @brief Gets the most recent status of the ImageViewer object.
     *
     * @return ImageViewerStatus The most recent status of the ImageViewer object.
     */
    ImageViewerStatus getStatus();
};