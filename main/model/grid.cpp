//See header file for documentation.

template <typename T>
Grid<T>::Grid(std::size_t xDim, std::size_t yDim) {
    width = xDim;
    height = yDim;
    size = width * height;
    array = new T[size];
}

template <typename T>
Grid<T>::Grid(const Grid<T> & other) {
    copy(other);
}


template <typename T>
Grid<T> & Grid<T>::operator=(const Grid<T> & rhs) {
    if(this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

template <typename T>
Grid<T>::~Grid() {
    clear();
}



template <typename T>
T & Grid<T>::operator()(std::size_t x, std::size_t y){
    return array[x*height + y];
}

template <typename T>
const T & Grid<T>::operator()(std::size_t x, std::size_t y) const {
    return array[x*height + y];
}

template <typename T>
T & Grid<T>::operator()(std::size_t index){
    return array[index];
}

template <typename T>
const T & Grid<T>::operator()(std::size_t index) const {
    return array[index];
}

template <typename T>
T * Grid<T>::getArray(void) {
    return array[0];
}

template <typename T>
std::size_t Grid<T>::getArraySize(void){
    return size;
}

template <typename T>
T Grid<T>::get(std::size_t x, std::size_t y) const {
    return array[x*height + y];
}

template <typename T>
T Grid<T>::get(std::size_t index) const {
    return array[index];
}

template <typename T>
void Grid<T>::set(std::size_t x, std::size_t y, const T & val) {
    array[x*height + y] = val;
}

template <typename T>
void Grid<T>::set(std::size_t index, const T & val) {
    array[index] = val;
}

template <typename T>
std::size_t Grid<T>::getWidth(void) const {
    return width;
}

template <typename T>
std::size_t Grid<T>::getHeight(void) const {
    return height;
}

template <typename T>
void Grid<T>::clear(void) {
    delete [] array;
}

template <typename T>
void Grid<T>::copy(const Grid<T> & other) {
    width = other.width;
    height = other.height;
    size = other.size;
    array = new T[size];
    for(unsigned int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
}
