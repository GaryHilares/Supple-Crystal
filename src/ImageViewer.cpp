#include "../include/ImageViewer.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Elements/Menus/ToolbarMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/OSUtils.hpp"
#include "../include/Utils.hpp"
#include <iostream>

ImageViewer::ImageViewer(const std::experimental::filesystem::path resource_folder, const std::experimental::filesystem::path new_file_path):
    window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),""),
    status(ImageViewerStatus::NothingAssigned),
    search_directories({resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"}),
    font(loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",search_directories)),
    icon(loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",search_directories)),
    functionalities({
        {"run_fast_mode",[this](){this->status = ImageViewerStatus::RunFastMode;}},
        {"run_polished_mode",[this](){this->status = ImageViewerStatus::RunPolishedMode;}},
        {"rotate_image_to_the_right",[this](){this->image_display.rotate(90);}},
        {"rotate_image_to_the_left",[this](){this->image_display.rotate(-90);}},
        {"zoom_image",[this](){this->image_display.scale({1.1,1.1});}},
        {"unzoom_image",[this](){this->image_display.scale({0.8,0.8});}},
        {"set_next_image",[this](){
            this->openImageFromPath(this->files.next());
            this->updateWindowTitle("Fast");
            std::cout << this->files.cur().string() << std::endl;
        }},
        {"set_previous_image",[this](){
            this->openImageFromPath(this->files.prev());
            this->updateWindowTitle("Fast");
            std::cout << this->files.cur().string() << std::endl;
        }}
    })
{
    this->openImageFromPath(new_file_path,true);
    this->window.setFramerateLimit(60);
    OS::maximizeWindow(this->window);
    this->window.setIcon(32,32,icon.getPixelsPtr());
}

void ImageViewer::openImageFromPath(const std::experimental::filesystem::path& new_file_path, bool open_folder)
{
    this->image_display = ImageDisplay(new_file_path.u8string());
    this->image_display.setOrigin(image_display.getDimensions().x/2,image_display.getDimensions().y/2);
    this->image_display.setPosition(sf::VideoMode::getDesktopMode().width/2,sf::VideoMode::getDesktopMode().height/2);
    if(open_folder)
    {
        for(const auto& file: std::experimental::filesystem::directory_iterator(new_file_path.parent_path()))
            if(isSupportedImageType(file))
                this->files.push(file);
        this->files.search(new_file_path);
    }
}

std::string ImageViewer::formatWindowTitle(const std::experimental::filesystem::path& file_path, std::string mode)
{
    return file_path.filename().u8string() + " - Supple Crystal: " + mode + " mode";
}

void ImageViewer::runFastMode()
{
    this->status = ImageViewerStatus::OngoingTask;
    this->updateWindowTitle("Fast");    
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Polished Mode",font,this->functionalities["run_polished_mode"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,this->functionalities["rotate_image_to_the_left"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,this->functionalities["rotate_image_to_the_right"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,this->functionalities["zoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,this->functionalities["unzoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,this->functionalities["set_next_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,this->functionalities["set_previous_image"]))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,this->functionalities["zoom_image"]},
                                            {sf::Keyboard::Subtract,this->functionalities["unzoom_image"]},
                                            {sf::Keyboard::Left,this->functionalities["rotate_image_to_the_left"]},
                                            {sf::Keyboard::Right,this->functionalities["rotate_image_to_the_right"]},
                                            {sf::Keyboard::Up,this->functionalities["set_next_image"]},
                                            {sf::Keyboard::Down,this->functionalities["set_previous_image"]}
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
}

void ImageViewer::updateWindowTitle(std::string mode){
    const std::string window_title_utf8 = ImageViewer::formatWindowTitle(this->files.cur(),mode);
    const sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
    this->window.setTitle(window_title);
}

void ImageViewer::runPolishedMode()
{
    this->status = ImageViewerStatus::OngoingTask;
    this->updateWindowTitle("Polished");
    ToolbarMenu toolbar_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",font,this->functionalities["run_fast_mode"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,this->functionalities["rotate_image_to_the_left"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,this->functionalities["rotate_image_to_the_right"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,this->functionalities["zoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,this->functionalities["unzoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,this->functionalities["set_next_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,this->functionalities["set_previous_image"]))
                            });
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",font,this->functionalities["run_fast_mode"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,this->functionalities["rotate_image_to_the_left"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,this->functionalities["rotate_image_to_the_right"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,this->functionalities["zoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,this->functionalities["unzoom_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,this->functionalities["set_next_image"])),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,this->functionalities["set_previous_image"]))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,this->functionalities["zoom_image"]},
                                            {sf::Keyboard::Subtract,this->functionalities["unzoom_image"]},
                                            {sf::Keyboard::Left,this->functionalities["rotate_image_to_the_left"]},
                                            {sf::Keyboard::Right,this->functionalities["rotate_image_to_the_right"]},
                                            {sf::Keyboard::Up,this->functionalities["set_next_image"]},
                                            {sf::Keyboard::Down,this->functionalities["set_previous_image"]}
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
}

ImageViewerStatus ImageViewer::getStatus()
{
    return this->status;
}