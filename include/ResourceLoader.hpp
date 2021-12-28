#include "Utils/LoadOps.hpp"
#include <array>
#include <map>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

template <class... LoadableTypes>
class ResourceLoader {
private:
    std::unordered_map<std::string, std::variant<LoadableTypes...>> m_resources;
    std::vector<std::string> m_searchDirectories;

public:
    ResourceLoader(const std::vector<std::string>& newSearchDirectories)
        : m_searchDirectories(newSearchDirectories)
    {
    }
    template <class LoadableType>
    void load(std::string resourceName)
    {
        const std::map<std::string_view, std::string_view> resourcesPaths = {
            std::pair<std::string_view, std::string_view> { "icon", "assets/logo_bg-true_resized.png" },
            std::pair<std::string_view, std::string_view> { "font", "PublicSans-Regular.ttf" }
        };
        std::string_view resourcePath = resourcesPaths.at(resourceName);
        std::optional<LoadableType> loadingObject = loadFromFileWithFallbacks<LoadableType>(std::string(resourcePath.begin(), resourcePath.end()), m_searchDirectories);
        if (loadingObject.has_value())
            m_resources[resourceName] = loadingObject.value();
        else
            throw std::runtime_error("Couldn't load resource \"" + resourceName + "\".");
    }
    template <class T>
    const T& get(std::string resourceName) const
    {
        return std::get<T>(m_resources.at(resourceName));
    }
    void unload(std::string resourceName)
    {
        this->resources.erase(m_resources.find(resourceName));
    }
};