#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <experimental/filesystem>
#include <string>

/**
 * @brief Replaces all the ocurrences of a character in a string.
 * 
 * @param str The string.
 * @param to_replace The character to replace.
 * @param replacement The replacement of the character.
 * @return std::string A copy of the string of text with the cars replaced.
 */
std::string replaceAllOcurrencesOfCharacter(std::string str, char to_replace, char replacement);

/**
 * @brief Prevents the default resizing SFML does to the contents of a window.
 * 
 * @param window The window which threw the resize event.
 * @param resize_event The resize event triggered by the resize button.
 * @param throw FatalError Terminates the program if sf::Event is not a resize event.
 */
void preventWindowContentResize(sf::RenderWindow& window, sf::Event resize_event);

/**
 * @brief Loads an object from a file.
 * 
 * @tparam LoadableObject The type of the object to load. Must have a loadFromFile method.
 * @param filename Name of the file.
 * @param fallbackDirectories Paths to the directories to search the files.
 * @return LoadableObject The loaded object.
 * @throw Error if the object isn't found in any of the directories.
 */
template <class LoadableObject> LoadableObject loadFromFileWithFallbacks(const std::string& filename, const std::vector<std::string>& fallbackDirectories){
    LoadableObject loaded_object;
    for(const std::string& directory: fallbackDirectories)
        if(loaded_object.loadFromFile(directory + filename))
            return loaded_object;
    throw;
}

/**
 * @brief A ciclical std::vector.
 * 
 * @tparam T The class to create the CiclicalITerator of.
 */
template <class T>
class CiclicalIterator
{
private:
    std::vector<T> data;
    typename std::vector<T>::size_type index;

public:
    CiclicalIterator(): data(), index(0) {}
    void push(T val)
    {
        data.push_back(val);
    }
    T& next()
    {
        if(index == data.size() - 1)
            index = 0;
        else
            index++;
        return data[index];
    }
    T& prev()
    {
        if(index == 0)
            index = data.size() - 1;
        else
            index--;
        return data[index];
    }
    T& cur()
    {
        return data[index];
    }
    void search(T val)
    {
        auto new_index = std::find(data.begin(),data.end(),val);
        if(new_index != data.end())
            this->index = std::distance(data.begin(),new_index);
    }
};

template<class T>
bool in(const T& x, std::initializer_list<T> c)
{
  return std::find(c.begin(), c.end(), x) != c.end();
}

bool isSupportedImageType(std::experimental::filesystem::path file);