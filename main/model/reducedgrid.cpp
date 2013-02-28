#include "reducedgrid.h"

template <typename T>
ReducedGrid<T>::ReducedGrid(int width, int height) {
    this.width = width;
    this.height = height;
}

template <typename T>
bool ReducedGrid<T>::locationExists(int x, int y) {
    int hashKey = getHashKey(x,y);
    return dataset.contains(hashKey);
}

template <typename T>
void ReducedGrid<T>::addItem(T data, int x, int y) {
    if(compressed) {
        abort();
    }
    DataStruct_t entry;
    entry.data = data;
    entry.x = x;
    entry.y = y;

    tempData.append(entry);
}

template <typename T>
T ReducedGrid<T>::get(int i) {
    return dataset[i];
}

template <typename T>
T ReducedGrid<T>::get(int x, int y) {
    if(!locationExists(x,y)){
        std::cerr << "Cannot return a location that doesn't exist, use locationExists() before calling get()!";
        std::cerr << std::endl;
        abort();
    }

    int hashKey = getHashKey(x,y);
    int index = indiciesHash[hashKey];
    return dataset[index];
}

template <typename T>
void ReducedGrid<T>::compress() {
    Grid<T> grid(width, height);
    Grid<bool> isData(width, height);

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            isData(i,j) = false;
        }
    }

    for(int i = 0; i < tempData.size(); i++) {
        DataStruct_t entry = tempData[i];
        grid(entry.x, entry.y) = entry.data;
        isData(entry.x, entry.y) = true;
    }

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width; j++) {
            if(isData(i,j)) {
                dataset.append(grid(i,j));
                int index = getHashKey(i,j);
                indiciesHash.insert(index, dataset.size()-1);
            }
        }
    }
}

template <typename T>
int ReducedGrid<T>::getWidth() {
    return width;
}

template <typename T>
int ReducedGrid<T>::getHeight() {
    return height;
}

template <typename T>
int ReducedGrid<T>::getHashKey(int x, int y) {
    return (y * width + x);
}
