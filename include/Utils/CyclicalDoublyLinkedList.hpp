#pragma once
#include <vector>

/**
 * @brief A circular doubly linked list.
 * 
 * @tparam T The class to create the CyclicalDoublyLinkedList of.
 */
template <class T>
class CyclicalDoublyLinkedList
{
private:
    std::vector<T> data;
    typename std::vector<T>::size_type index;

public:
    /**
     * @brief Construct a new CyclicalDoublyLinkedList object.
     * 
     */
    CyclicalDoublyLinkedList(): data(), index(0) {}
    /**
     * @brief Inserts a new value into the CyclicalDoublyLinkedList.
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