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
 * @brief A circular doubly linked list.
 * 
 * @tparam T The class to create the CiclicalDoublyLinkedList of.
 */
template <class T>
class CiclicalDoublyLinkedList
{
private:
    std::vector<T> data;
    typename std::vector<T>::size_type index;

public:
    /**
     * @brief Construct a new CiclicalDoublyLinkedList object.
     * 
     */
    CiclicalDoublyLinkedList(): data(), index(0) {}
    /**
     * @brief Inserts a new value into the CiclicalDoublyLinkedList.
     * 
     * @param val The value to insert.
     */
    void push(T val)
    {
        data.push_back(val);
    }
    /**
     * @brief Moves the index to the next value in the list and returns it.
     * 
     * @return T& The next value in the list.
     */
    T& next()
    {
        if(index == data.size() - 1)
            index = 0;
        else
            index++;
        return data[index];
    }
    /**
     * @brief Moves the index to the previous value in the list and returns it.
     * 
     * @return T& The previous element in the list.
     */
    T& prev()
    {
        if(index == 0)
            index = data.size() - 1;
        else
            index--;
        return data[index];
    }
    /**
     * @brief Returns the current value in the list.
     * 
     * @return T& The current element in the list.
     */
    T& cur()
    {
        return data[index];
    }
    /**
     * @brief Search a value in the list and sets the index on its position.
     * 
     * @param val The value to search.
     */
    void search(T val)
    {
        auto new_index = std::find(data.begin(),data.end(),val);
        if(new_index != data.end())
            this->index = std::distance(data.begin(),new_index);
    }
};

/**
 * @brief Searchs a value in a list.
 * 
 * @tparam T The type of the value to search.
 * @param x The value to search.
 * @param c The std::initiliazer_list to look at.
 * @return bool True if the value is found, false otherwise.
 */
template<class T>
bool in(const T& x, std::initializer_list<T> c)
{
  return std::find(c.begin(), c.end(), x) != c.end();
}

/**
 * @brief Checks if a file is of an image type supported by Supple Crystal.
 * 
 * @param file The file to check.
 * @return bool True if the file is of an image type supported by Supple Crystal.
 */
bool isSupportedImageType(std::experimental::filesystem::path file);