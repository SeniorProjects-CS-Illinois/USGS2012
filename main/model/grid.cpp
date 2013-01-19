//See header file for documentation.

template <typename T>
Grid<T>::Grid(std::size_t xDim, std::size_t yDim) {
    width = xDim;
    height = yDim;
    array.resize(width * height);
}

template <typename T>
T & Grid<T>::operator()(std::size_t x, std::size_t y){
    return array[x*height + y];
}

template <typename T>
T const & Grid<T>::operator()(std::size_t x, std::size_t y) const {
    return array[x*height + y];
}

template <typename T>
T & Grid<T>::operator()(std::size_t index){
    return array[index];
}

template <typename T>
T const & Grid<T>::operator()(std::size_t index) const {
    return array[index];
}

template <typename T>
T * Grid<T>::getArray(void) {
    return array[0];
}

template <typename T>
std::size_t Grid<T>::getArraySize(void){
    return array.size();
}

template <typename T>
std::size_t Grid<T>::getWidth(void) {
    return width;
}

template <typename T>
std::size_t Grid<T>::getHeight(void) {
    return height;
}
