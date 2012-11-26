//See header file for documentation.

template <typename T>
Grid<T>::Grid(std::size_t xDim, std::size_t yDim) {
    numCol = xDim;
    numRow = yDim;
    array.resize(numCol * numRow);
}

template <typename T>
T & Grid<T>::operator()(std::size_t x, std::size_t y){
    return array[y*numCol + x];
}

template <typename T>
T const & Grid<T>::operator()(std::size_t x, std::size_t y) const {
    return array[y*numCol + x];
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
std::size_t Grid<T>::getXDim(void) {
    return numCol;
}

template <typename T>
std::size_t Grid<T>::getYDim(void) {
    return numRow;
}
