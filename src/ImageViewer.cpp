#include "../include/ImageViewer.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/OSUtils.hpp"
#include "../include/Utils.hpp"

ImageViewer::ImageViewer(const std::experimental::filesystem::path resource_folder):
    status(ImageViewerStatus::NothingAssigned),
    window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),""),
    resource_loader({resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"}),
    functionalities({
        {"run_fast_mode",[this](){this->status = ImageViewerStatus::RunFastMode;}},
        {"run_polished_mode",[this](){this->status = ImageViewerStatus::RunPolishedMode;}},
        {"rotate_image_to_the_right",[this](){this->image_display.rotate(90);}},
        {"rotate_image_to_the_left",[this](){this->image_display.rotate(-90);}},
        {"zoom_image",[this](){this->image_display.scale({1.1,1.1});}},
        {"unzoom_image",[this](){this->image_display.scale({0.8,0.8});}},
        {"set_next_image",[this](){
            this->openImageFromPath(this->files.next());
        }},
        {"set_previous_image",[this](){
            this->openImageFromPath(this->files.prev());
        }}
    })
{
    this->window.setFramerateLimit(60);
    OS::maximizeWindow(this->window);
    resource_loader.load<sf::Image>("icon");
    this->window.setIcon(32,32,resource_loader.get<sf::Image>("icon").getPixelsPtr());
    resource_loader.load<sf::Font>("font");
}

void ImageViewer::openImageFromPath(const std::experimental::filesystem::path& new_file_path)
{
    this->image_display = ImageDisplay(new_file_path.u8string());
    this->image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    this->image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    this->updateWindowTitle(new_file_path);
    if(!this->loadedFolder.has_value() || this->loadedFolder != new_file_path.parent_path())
    {
        for(const auto& file: std::experimental::filesystem::directory_iterator(new_file_path.parent_path()))
            if(isSupportedImageType(file))
                this->files.push(file);
        this->loadedFolder = new_file_path.parent_path();
        this->files.search(new_file_path);
    }
}

std::string ImageViewer::formatWindowTitle(const std::experimental::filesystem::path& file_path, const std::string mode)
{
    return file_path.filename().u8string() + " - Supple Crystal: " + mode + " mode";
}

std::pair<ImageViewerStatus,std::experimental::filesystem::path> ImageViewer::runFastMode(const std::experimental::filesystem::path new_file_path)
{
    this->status = ImageViewerStatus::OngoingTask;
    this->mode = "Fast";
    this->openImageFromPath(new_file_path);
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Polished Mode",resource_loader.get<sf::Font>("font"),this->functionalities.at("run_polished_mode"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_left"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_right"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("zoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("unzoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_next_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_previous_image")))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,this->functionalities.at("zoom_image")},
                                            {sf::Keyboard::Subtract,this->functionalities.at("unzoom_image")},
                                            {sf::Keyboard::Left,this->functionalities.at("rotate_image_to_the_left")},
                                            {sf::Keyboard::Right,this->functionalities.at("rotate_image_to_the_right")},
                                            {sf::Keyboard::Up,this->functionalities.at("set_next_image")},
                                            {sf::Keyboard::Down,this->functionalities.at("set_previous_image")}
                                         });
    SlideController slide_controller(this->image_display);
    while(this->status == ImageViewerStatus::OngoingTask && window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::LostFocus:
                slide_controller.setEnabled(false);
                break;
            case sf::Event::GainedFocus:
                slide_controller.setEnabled(true);
                break;
            case sf::Event::Closed:
                window.close();
                this->status = ImageViewerStatus::LeftOk;
                break;
            case sf::Event::MouseMoved:
                slide_controller.checkForUpdates(event);
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
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
        /* Display */
        window.clear(sf::Color(Constants::background_color));
        window.draw(this->image_display);
        window.draw(context_menu);
        window.display();
    }
    return {this->getStatus(),this->files.cur()};
}

void ImageViewer::updateWindowTitle(std::experimental::filesystem::path new_file_path){
    const std::string window_title_utf8 = ImageViewer::formatWindowTitle(new_file_path,this->mode);
    const sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
    this->window.setTitle(window_title);
}

std::pair<ImageViewerStatus,std::experimental::filesystem::path> ImageViewer::runPolishedMode(const std::experimental::filesystem::path new_file_path)
{
    this->status = ImageViewerStatus::OngoingTask;
    this->mode = "Polished";
    this->openImageFromPath(new_file_path);
    ToolbarMenu toolbar_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",resource_loader.get<sf::Font>("font"),this->functionalities.at("run_fast_mode"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_left"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_right"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("zoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("unzoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_next_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_previous_image")))
                            });
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",resource_loader.get<sf::Font>("font"),this->functionalities.at("run_fast_mode"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_left"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",resource_loader.get<sf::Font>("font"),this->functionalities.at("rotate_image_to_the_right"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("zoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",resource_loader.get<sf::Font>("font"),this->functionalities.at("unzoom_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_next_image"))),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",resource_loader.get<sf::Font>("font"),this->functionalities.at("set_previous_image")))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,this->functionalities.at("zoom_image")},
                                            {sf::Keyboard::Subtract,this->functionalities.at("unzoom_image")},
                                            {sf::Keyboard::Left,this->functionalities.at("rotate_image_to_the_left")},
                                            {sf::Keyboard::Right,this->functionalities.at("rotate_image_to_the_right")},
                                            {sf::Keyboard::Up,this->functionalities.at("set_next_image")},
                                            {sf::Keyboard::Down,this->functionalities.at("set_previous_image")}
                                         });
    SlideController slide_controller(this->image_display);
    while(this->status == ImageViewerStatus::OngoingTask && window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::LostFocus:
                slide_controller.setEnabled(false);
                break;
            case sf::Event::GainedFocus:
                slide_controller.setEnabled(true);
                break;
            case sf::Event::Closed:
                window.close();
                this->status = ImageViewerStatus::LeftOk;
                break;
            case sf::Event::MouseMoved:
                slide_controller.checkForUpdates(event);
                break;
            case sf::Event::Resized:
                preventWindowContentResize(window,event);
                break;
            case sf::Event::MouseButtonReleased:
                context_menu.processEvent(event);
                toolbar_menu.processEvent(event);
                break;
            case sf::Event::KeyReleased:
                hotkeys_controller.checkForUpdates(event);
                break;
            default:
                break;
            }
        }
        /* Display */
        window.clear(sf::Color(Constants::background_color));
        window.draw(this->image_display);
        window.draw(context_menu);
        window.draw(toolbar_menu);
        window.display();
    }
    return {this->getStatus(),this->files.cur()};
}

ImageViewerStatus ImageViewer::getStatus()
{
    return this->status;
}