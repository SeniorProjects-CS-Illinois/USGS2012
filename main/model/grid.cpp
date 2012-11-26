//See header file for documentation.

template <typename T>
Grid::Grid(std::size_t xDim, std::size_t yDim) {
    numCol = xDim;
    numRow = yDim;
    array.resize(numCol * numRow);
}

template <typename T>
T & Grid::operator()(std::size_t x, std::size_t y){
    return array[x*numCol + y];
}

template <typename T>
T const & Grid::operator()(std::size_t x, std::size_t y) const {
    return array[x*numCol + y];
}

template <typename T>
T & Grid::operator()(std::size_t index){
    return array[index];
}

template <typename T>
T const & Grid::operator()(std::size_t index) const {
    return array[index];
}

template <typename T>
T * Grid::getArray(void) {
    return array[0];
}

template <typename T>
std::size_t Grid::getArraySize(void){
    return array.size();
}

template <typename T>
std::size_t Grid::getXDim(void) {
    return numCol;
}

template <typename T>
std::size_t Grid::getYDim(void) {
    return numRow;
}
