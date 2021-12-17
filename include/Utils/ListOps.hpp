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