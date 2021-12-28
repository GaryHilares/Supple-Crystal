#include <optional>
#include <string>
#include <vector>

/**
 * @brief Loads an object from a file.
 *
 * @tparam LoadableObject The type of the object to load. Must have a loadFromFile method.
 * @param filename Name of the file.
 * @param fallbackDirectories Paths to the directories to search the files.
 * @return LoadableObject The loaded object.
 * @throw Error if the object isn't found in any of the directories.
 */
template <class LoadableObject>
std::optional<LoadableObject> loadFromFileWithFallbacks(const std::string& filename, const std::vector<std::string>& fallbackDirectories)
{
    LoadableObject loaded_object;
    for (const std::string& directory : fallbackDirectories)
        if (loaded_object.loadFromFile(directory + filename))
            return loaded_object;
    return std::nullopt;
}