
template <typename T>
void Utility::initArray(T * & array, int size, T initialValue) {
    array = new T[size];
    for(int i = 0; i < size; i++) {
        array[i] = initialValue;
    }
}

template <typename T>
T * Utility::copyArray(T * other, int size) {
    T * array = new T[size];
    for(int i = 0; i < size; i++) {
        array[i] = other[i];
    }
    return array;

}
