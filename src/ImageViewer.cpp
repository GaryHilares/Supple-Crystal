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
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{this->resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    const std::string& starting_window_title_utf8 = file_path.u8string().substr(file_path.u8string().find_last_of("/\\")+1,file_path.u8string().size()) + " - Supple Crystal: Fast mode";
    sf::String starting_window_title = sf::String::fromUtf8(starting_window_title_utf8.begin(),starting_window_title_utf8.end());
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),starting_window_title);
    window.setFramerateLimit(60);
    window.setIcon(32,32,icon.getPixelsPtr());
    OS::maximizeWindow(window);
    auto run_polished_mode = [&](){this->status = ImageViewerStatus::RunPolishedMode;};
    auto rotate_image_to_the_right = [&](){
        this->image_display.rotate(90);
    };
    auto rotate_image_to_the_left = [&](){
        this->image_display.rotate(-90);
    };
    auto zoom_image = [&](){this->image_display.scale({1.1,1.1});};
    auto unzoom_image = [&](){this->image_display.scale({0.8,0.8});};
    auto set_next_image = [&](){
        this->openImageFromPath(this->files.next());
        const std::string& window_title_utf8 = this->files.cur().u8string().substr(this->files.cur().u8string().find_last_of("/\\")+1,this->files.cur().u8string().size()) + " - Supple Crystal: Fast mode";
        sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
        window.setTitle(window_title);
        std::cout << this->files.cur().string() << std::endl;
    };
    const auto set_previous_image = [&](){
        this->openImageFromPath(this->files.prev());
        const std::string& window_title_utf8 = this->files.cur().u8string().substr(this->files.cur().u8string().find_last_of("/\\")+1,this->files.cur().u8string().size()) + " - Supple Crystal: Fast mode";
        sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
        window.setTitle(window_title);
        std::cout << this->files.cur().string() << std::endl;
    };
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Polished Mode",font,run_polished_mode)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,rotate_image_to_the_left)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,rotate_image_to_the_right)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,zoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,unzoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,set_next_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,set_previous_image))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,zoom_image},
                                            {sf::Keyboard::Subtract,unzoom_image},
                                            {sf::Keyboard::Left,rotate_image_to_the_left},
                                            {sf::Keyboard::Right,rotate_image_to_the_right},
                                            {sf::Keyboard::Up,set_next_image},
                                            {sf::Keyboard::Down,set_previous_image}
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

void ImageViewer::runPolishedMode()
{
    this->status = ImageViewerStatus::OngoingTask;
    const std::experimental::filesystem::path file_path = this->files.cur();
    sf::Font font = loadFromFileWithFallbacks<sf::Font>("PublicSans-Regular.ttf",{this->resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    sf::Image icon = loadFromFileWithFallbacks<sf::Image>("assets/logo_bg-true_resized.png",{this->resource_folder.string() + "/","","C:/Users/Administrator/Desktop/Supple-Crystal 0.1.0.2-alfa/"});
    const std::string& starting_window_title_utf8 = file_path.u8string().substr(file_path.u8string().find_last_of("/\\")+1,file_path.u8string().size()) + " - Supple Crystal: Polished mode";
    sf::String starting_window_title = sf::String::fromUtf8(starting_window_title_utf8.begin(),starting_window_title_utf8.end());
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),starting_window_title);
    window.setFramerateLimit(60);
    window.setIcon(32,32,icon.getPixelsPtr());
    OS::maximizeWindow(window);
    const auto run_polished_mode = [&](){this->status = ImageViewerStatus::RunFastMode;};
    auto rotate_image_to_the_right = [&](){
        this->image_display.rotate(90);
    };
    const auto rotate_image_to_the_left = [&](){
        this->image_display.rotate(-90);
    };
    const auto zoom_image = [&](){this->image_display.scale({1.1,1.1});};
    const auto unzoom_image = [&](){this->image_display.scale({0.8,0.8});};
    const auto set_next_image = [&](){
        this->openImageFromPath(this->files.next());
        const std::string& window_title_utf8 = this->files.cur().u8string().substr(this->files.cur().u8string().find_last_of("/\\")+1,this->files.cur().u8string().size()) + " - Supple Crystal: Polished mode";
        sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
        window.setTitle(window_title);
        std::cout << this->files.cur().string() << std::endl;
    };
    const auto set_previous_image = [&](){
        this->openImageFromPath(this->files.prev());
        const std::string& window_title_utf8 = this->files.cur().u8string().substr(this->files.cur().u8string().find_last_of("/\\")+1,this->files.cur().u8string().size()) + " - Supple Crystal: Polished mode";
        sf::String window_title = sf::String::fromUtf8(window_title_utf8.begin(),window_title_utf8.end());
        window.setTitle(window_title);
        std::cout << this->files.cur().string() << std::endl;
    };
    ToolbarMenu toolbar_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",font,run_polished_mode)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,rotate_image_to_the_left)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,rotate_image_to_the_right)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,zoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,unzoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,set_next_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,set_previous_image))
                            });
    ContextMenu context_menu({
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Fast Mode",font,run_polished_mode)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate left",font,rotate_image_to_the_left)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Rotate right",font,rotate_image_to_the_right)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Increase zoom",font,zoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Decrease zoom",font,unzoom_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Next image",font,set_next_image)),
                                std::make_shared<PopupMenuButton>(PopupMenuButton("Previous image",font,set_previous_image))
                           });
    HotkeysController hotkeys_controller({
                                            {sf::Keyboard::Add,zoom_image},
                                            {sf::Keyboard::Subtract,unzoom_image},
                                            {sf::Keyboard::Left,rotate_image_to_the_left},
                                            {sf::Keyboard::Right,rotate_image_to_the_right},
                                            {sf::Keyboard::Up,set_next_image},
                                            {sf::Keyboard::Down,set_previous_image}
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