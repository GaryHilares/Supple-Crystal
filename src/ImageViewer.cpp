#include "../include/ImageViewer.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/Utils/ListOps.hpp"
#include "../include/Utils/WindowOps.hpp"

ImageViewer::ImageViewer(const std::experimental::filesystem::path resourceFolder)
    : m_status(ImageViewerStatus::NothingAssigned)
    , m_window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "")
    , m_resourceLoader({ resourceFolder.string() + "/", "", "C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/" })
    , m_functionalities({ { "run_fast_mode", [this]() { m_status = ImageViewerStatus::RunFastMode; } },
          { "run_polished_mode", [this]() { this->m_status = ImageViewerStatus::RunPolishedMode; } },
          { "rotate_image_to_the_right", [this]() { this->m_imageDisplay.rotate(90); } },
          { "rotate_image_to_the_left", [this]() { this->m_imageDisplay.rotate(-90); } },
          { "zoom_image", [this]() { this->m_imageDisplay.scale({ 1.1, 1.1 }); } },
          { "unzoom_image", [this]() { this->m_imageDisplay.scale({ 0.8, 0.8 }); } },
          { "set_next_image", [this]() {
               this->openImageFromPath(m_files.next());
           } },
          { "set_previous_image", [this]() {
               this->openImageFromPath(m_files.prev());
           } } })
{
    m_window.setFramerateLimit(60);
    OS::maximizeWindow(m_window);
    m_resourceLoader.load<sf::Image>("icon");
    m_window.setIcon(32, 32, m_resourceLoader.get<sf::Image>("icon").getPixelsPtr());
    m_resourceLoader.load<sf::Font>("font");
}

void ImageViewer::openImageFromPath(const std::experimental::filesystem::path& newFilePath)
{
    if (!isSupportedImageType(newFilePath)) {
        throw std::runtime_error("This image file type is not supported by Supple-Crystal.");
    }
    m_imageDisplay = ImageDisplay(newFilePath.u8string());
    m_imageDisplay.setOrigin(m_imageDisplay.getSize().x / 2, m_imageDisplay.getSize().y / 2);
    m_imageDisplay.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    this->updateWindowTitle(newFilePath);
    if (!m_loadedFolder.has_value() || m_loadedFolder != newFilePath.parent_path()) {
        for (const auto& file : std::experimental::filesystem::directory_iterator(newFilePath.parent_path()))
            if (isSupportedImageType(file))
                m_files.push(file);
        m_loadedFolder = newFilePath.parent_path();
        m_files.search(newFilePath);
    }
}

std::string ImageViewer::formatWindowTitle(const std::experimental::filesystem::path& filePath, const std::string mode)
{
    return filePath.filename().u8string() + " - Supple Crystal: " + mode + " mode";
}

std::pair<ImageViewerStatus, std::experimental::filesystem::path> ImageViewer::runFastMode(const std::experimental::filesystem::path newFilePath)
{
    m_status = ImageViewerStatus::OngoingTask;
    m_mode = "Fast";
    this->openImageFromPath(newFilePath);
    ContextMenu context_menu({ std::make_shared<PopupMenuButton>(PopupMenuButton("Polished Mode", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("run_polished_mode"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_left"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_right"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("zoom_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("unzoom_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Next image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_next_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_previous_image"))) });
    HotkeysController hotkeys_controller({ { sf::Keyboard::Add, m_functionalities.at("zoom_image") },
        { sf::Keyboard::Subtract, m_functionalities.at("unzoom_image") },
        { sf::Keyboard::Left, m_functionalities.at("rotate_image_to_the_left") },
        { sf::Keyboard::Right, m_functionalities.at("rotate_image_to_the_right") },
        { sf::Keyboard::Up, m_functionalities.at("set_next_image") },
        { sf::Keyboard::Down, m_functionalities.at("set_previous_image") } });
    SlideController slide_controller(m_imageDisplay);
    while (m_status == ImageViewerStatus::OngoingTask && m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::LostFocus:
                slide_controller.setEnabled(false);
                break;
            case sf::Event::GainedFocus:
                slide_controller.setEnabled(true);
                break;
            case sf::Event::Closed:
                m_window.close();
                m_status = ImageViewerStatus::LeftOk;
                break;
            case sf::Event::MouseMoved:
                slide_controller.checkForUpdates(event);
                break;
            case sf::Event::Resized:
                preventWindowContentResize(m_window, event);
                break;
            case sf::Event::MouseButtonReleased:
                context_menu.processEvent(event);
                break;
            case sf::Event::KeyReleased:
                hotkeys_controller.checkForUpdates(event);
                break;
            default:
                break;
            }
        }
        m_window.clear(sf::Color(Constants::background_color));
        m_window.draw(m_imageDisplay);
        m_window.draw(context_menu);
        m_window.display();
    }
    return { this->getStatus(), m_files.cur() };
}

void ImageViewer::updateWindowTitle(std::experimental::filesystem::path newFilePath)
{
    const std::string windowTitleUtf8 = ImageViewer::formatWindowTitle(newFilePath, m_mode);
    const sf::String windowTitle = sf::String::fromUtf8(windowTitleUtf8.begin(), windowTitleUtf8.end());
    m_window.setTitle(windowTitle);
}

std::pair<ImageViewerStatus, std::experimental::filesystem::path> ImageViewer::runPolishedMode(const std::experimental::filesystem::path newFilePath)
{
    m_status = ImageViewerStatus::OngoingTask;
    m_mode = "Polished";
    this->openImageFromPath(newFilePath);
    ToolbarMenu toolbarMenu({ std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("run_fast_mode"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_left"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_right"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("zoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("unzoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_next_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_previous_image"))) },
        m_window.getSize().x);
    ContextMenu contextMenu({ std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("run_fast_mode"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_left"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("rotate_image_to_the_right"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("zoom_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("unzoom_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Next image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_next_image"))),
        std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image", m_resourceLoader.get<sf::Font>("font"), m_functionalities.at("set_previous_image"))) });
    HotkeysController hotkeysController({ { sf::Keyboard::Add, m_functionalities.at("zoom_image") },
        { sf::Keyboard::Subtract, m_functionalities.at("unzoom_image") },
        { sf::Keyboard::Left, m_functionalities.at("rotate_image_to_the_left") },
        { sf::Keyboard::Right, m_functionalities.at("rotate_image_to_the_right") },
        { sf::Keyboard::Up, m_functionalities.at("set_next_image") },
        { sf::Keyboard::Down, m_functionalities.at("set_previous_image") } });
    SlideController slideController(m_imageDisplay);
    sf::Texture texture;
    while (m_status == ImageViewerStatus::OngoingTask && m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::LostFocus:
                slideController.setEnabled(false);
                break;
            case sf::Event::GainedFocus:
                slideController.setEnabled(true);
                break;
            case sf::Event::Closed:
                m_window.close();
                m_status = ImageViewerStatus::LeftOk;
                break;
            case sf::Event::MouseMoved:
                slideController.checkForUpdates(event);
                break;
            case sf::Event::Resized:
                preventWindowContentResize(m_window, event);
                toolbarMenu.setWidth(event.size.width);
                break;
            case sf::Event::MouseButtonReleased:
                contextMenu.processEvent(event);
                toolbarMenu.processEvent(event);
                break;
            case sf::Event::KeyReleased:
                hotkeysController.checkForUpdates(event);
                break;
            default:
                break;
            }
        }
        m_window.clear(sf::Color(Constants::background_color));
        m_window.draw(m_imageDisplay);
        m_window.draw(contextMenu);
        m_window.draw(toolbarMenu);
        m_window.display();
    }
    return { this->getStatus(), m_files.cur() };
}

ImageViewerStatus ImageViewer::getStatus()
{
    return m_status;
}

bool ImageViewer::isSupportedImageType(std::experimental::filesystem::path file)
{
    std::string extension = file.string().substr(file.string().find_last_of(".") + 1, file.string().size());
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });
    return in<std::string>(extension, { "bmp", "png", "tga", "jpg", "jpeg", "jfif", "gif", "psd", "hdr", "pic" });
}