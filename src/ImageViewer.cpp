#include "../include/ImageViewer.hpp"
#include "../include/UI/Controllers/HotkeyController.hpp"
#include "../include/UI/Controllers/SlideController.hpp"
#include "../include/UI/Elements/Buttons/PopupMenuButton.hpp"
#include "../include/UI/Elements/Menus/ContextMenu.hpp"
#include "../include/UI/Settings/style-constants.hpp"
#include "../include/OSUtils.hpp"
#include "../include/Utils.hpp"
#include <iostream>

ImageViewer::ImageViewer(const std::experimental::filesystem::path new_resource_folder, const std::experimental::filesystem::path new_file_path):
    resource_folder(new_resource_folder), status(ImageViewerStatus::NothingAssigned)
{
    this->openImageFromPath(new_file_path,true);
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

void ImageViewer::runFastMode()
{
    this->status = ImageViewerStatus::OngoingTask;
    const std::experimental::filesystem::path file_path = this->files.cur();
    sf::Font font = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",{this->resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::String window_title = sf::String(file_path.wstring().substr(file_path.string().find_last_of("/\\")+1,file_path.string().size())) + " - Supple Crystal: Fast mode";
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),window_title);
    window.setFramerateLimit(60);
    window.setIcon(32,32,icon.getPixelsPtr());
    OS::maximizeWindow(window);
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Polished Mode",font,[&](){this->status = ImageViewerStatus::RunPolishedMode;})),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,[&](){this->image_display.rotate(-90);})),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,[&](){this->image_display.rotate(90);})),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,[&](){this->image_display.scale({1.15,1.15});})),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,[&](){this->image_display.scale({0.85,0.85});})),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,[&](){
                                    this->openImageFromPath(this->files.next());
                                    sf::String window_title = sf::String(this->files.cur().wstring().substr(this->files.cur().string().find_last_of("/\\")+1,this->files.cur().string().size())) + " - Supple Crystal: Fast mode";
                                    window.setTitle(window_title);
                                    std::cout << this->files.cur().string() << std::endl;
                                })),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,[&](){
                                    this->openImageFromPath(this->files.prev());
                                    sf::String window_title = sf::String(file_path.wstring().substr(this->files.cur().string().find_last_of("/\\")+1,this->files.cur().string().size())) + " - Supple Crystal: Fast mode";
                                    window.setTitle(window_title);
                                    std::cout << this->files.cur().string() << std::endl;
                                }))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,[&](){this->image_display.scale(1.1,1.1);}},
                                            {sf::Keyboard::Subtract,[&](){this->image_display.scale(0.8,0.8);}},
                                            {sf::Keyboard::Left,[&](){this->image_display.rotate(90);}},
                                            {sf::Keyboard::Right,[&](){this->image_display.rotate(-90);}},
                                            {sf::Keyboard::Up,[&](){
                                                this->openImageFromPath(this->files.next());
                                                sf::String window_title = sf::String(this->files.cur().wstring().substr(this->files.cur().string().find_last_of("/\\")+1,this->files.cur().string().size())) + " - Supple Crystal: Fast mode";
                                                window.setTitle(window_title);
                                                std::cout << this->files.cur().string() << std::endl;
                                            }},
                                            {sf::Keyboard::Down,[&](){
                                                this->openImageFromPath(this->files.prev());
                                                sf::String window_title = sf::String(this->files.cur().wstring().substr(this->files.cur().string().find_last_of("/\\")+1,this->files.cur().string().size())) + " - Supple Crystal: Fast mode";
                                                window.setTitle(window_title);
                                                std::cout << this->files.cur().string() << std::endl;
                                            }}
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
        window.draw(image_display);
        window.draw(context_menu);
        window.display();
    }
}

void ImageViewer::runPolishedMode()
{
    this->status = ImageViewerStatus::OngoingTask;
    this->status = ImageViewerStatus::Error;
}

ImageViewerStatus ImageViewer::getStatus()
{
    return this->status;
}