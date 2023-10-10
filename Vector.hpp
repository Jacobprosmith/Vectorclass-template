#include "Vector.h"
#include <stdexcept>
#include <iterator>
#include <ostream>

using namespace std;

template <typename T>
Vector<T>::Vector() {
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector &rhs) {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = new T[rhs.theCapacity];
}

template <typename T>
Vector<T>::Vector(Vector &&rhs) {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = rhs.array;
    rhs.array = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template <typename T>
Vector<T>::Vector(int num, const T& val) {
    theSize = num;
    theCapacity = num;
    array = new T[num];
    for (int i = 0; i < num; i++) {
        array[i] = val;
    }
}

template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end) {
    int size = distance(start, end);
    theSize = size;
    theCapacity = size;
    array = new T[theCapacity];
    int i = 0;
    for (auto it = start; it != end; it++) {
        array[i] = *it;
        i++;
    }
}

template <typename T>
Vector<T>::~Vector(){
    if (array != nullptr) {
        delete[] array;
    }
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    return array[index];
}

template <typename T>
const  Vector<T>& Vector<T>::operator=(const Vector &rhs) {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    if (array != nullptr) {
        delete[] array;
    }
    array = new T[rhs.theCapacity];
    for (int i = 0; i < rhs.theCapacity; i++) {
        array[i] = rhs.array[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector &&rhs) {
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    if (array != nullptr) { //can nullptr be &rhs or must it be null
        delete[] array;
    }
    array = rhs.array;
    rhs.theCapacity = 0;
    rhs.theSize = 0;
    rhs.array = nullptr;
    return *this;
}

template <typename T>
T& Vector<T>::at(int loc) {
    if(loc >= 0 && loc < theSize) {
        return array[loc];
    } else {
        throw out_of_range("Out of range");
    }
}

template <typename T>
const T& Vector<T>::at(int loc ) const {
    if(loc >= 0 && loc < theSize) {
        return array[loc];
    } else {
        throw out_of_range("Out of range");
    }
}

template <typename T>
T& Vector<T>::front() {
    return array[0];
}

template <typename T>
const T& Vector<T>::front() const {
    return array[0];
}

template <typename T>
T& Vector<T>::back() {
    return array[theSize - 1];
}

template <typename T>
const T& Vector<T>::back() const {
    return array[theSize - 1];
}

template <typename T>
int Vector<T>::size() const {
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const {
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const {
    if (theCapacity == 0 || theSize == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
void Vector<T>::clear() {
    theSize = 0;
}

template <typename T>
void Vector<T>::push_back(const T & val) {
    if (theSize == theCapacity) {
        theCapacity *= 2;
    }
    if (theCapacity == 0) {
        theCapacity = 1;
    }
    T* tempArray = new T[theCapacity];
    for (int i = 0; i < theSize; i++) {
        tempArray[i] = array[i];
    }
    tempArray[theSize] = val;
    delete[] array;
    array = tempArray;
    theSize++;
}

template <typename T>
void Vector<T>::pop_back() {
    theSize -= 1;
}

template <typename T>
void Vector<T>::resize(int num, T val) {
     if (num < theSize) {
         theSize = num;
     } else if (num > theSize) {
         if (num > theCapacity) {
             theCapacity *= 2;
         }
         T* tempArray = new T[theCapacity];
         for (int j = 0; j < theSize; j++) {
             tempArray[j] = array[j];
         }
         int tempSize = theSize;
         theSize = num;
         for (int i = tempSize; i < theSize; i++) {
             tempArray[i] = val;
         }
         delete[] array;
         array = tempArray;
     } else {
         theSize = num;
     }
}

template <typename T>
void Vector<T>::reserve(int newCapacity) {
    if (newCapacity > theCapacity) {
        theCapacity = newCapacity;
        T* tempArray = new T[theCapacity];
        for (int i = 0; i < theSize; i++) {
            tempArray[i] = array[i];
        }
        delete[] array;
        array = tempArray;
    }
}

template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const {
    for (int i = 0; i < theSize; i++) {
        os << array[i];
        if (i != theSize-1) {
            os << ofc;
        }
    }
}

template <typename T>
T* Vector<T>::begin() {
    return &array[0];
}

template <typename T>
const T* Vector<T>::begin() const {
    return &array[0];
}

template <typename T>
T* Vector<T>:: end() {
    return &array[theSize];
}

template <typename T>
const T* Vector<T>::end() const {
    return &array[theSize];
}

template <typename T>
T* Vector<T>::insert(iterator itr, const T& val) {
    if (theSize == theCapacity) {
        theCapacity *= 2;
        T* tempArray = new T[theCapacity];
        int i = 0;
        for (auto it = begin(); it != itr; it++) {
            tempArray[i] = *it;
            i++;
        }
        tempArray[i] = val;
        int valRemem = i;
        i++;
        for (auto it = itr; it != end(); it++) {
            tempArray[i] = *it;
            i++;
        }
        delete[] array;
        array = tempArray;
        theSize++;
        return &array[valRemem];
    } else {
        int i = 0;
        for (auto it = begin(); it != itr; it++) {
            i++;
        }
        int valRemem = i;
        i = theSize;
        for (auto it = end() - 1; it >= itr; it--) {
            array[i] = *it;
            i--;
        }
        array[valRemem] = val;
        theSize++;
        return &array[valRemem];
    }
}

template <typename T>
T* Vector<T>::erase(iterator itr) {
    int i = 0;
    for (auto it = begin(); it != itr; it++) {
        i++;
    }
    int rememI = i;
    for (auto it = itr; it != end() - 1; it++) {
        array[i] = array[i+1];
        i++;
    }
    theSize--;
    return &array[rememI];
}

template <typename T>
T* Vector<T>::erase(iterator start, iterator end) {
    int i = 0;
    int size = distance(start, end);
    for (auto it = begin(); it != start; it++) {
        i++;
    }
    int rememI = i;
    for (auto it = start; it != end - 1; it++) {
        array[i] = array[i+size];
        i++;
    }
    theSize = theSize - size;
    return &array[rememI];
}

template <typename T>
void Vector<T>::doubleCapacity() {
    if (theCapacity == 0) {
        theCapacity = 1;
    }
    theCapacity*=2;
    T *tempArray = new T[theCapacity];
    for (int i = 0; i < theSize; i++) {
        tempArray[i] = array[i];
    }
    delete[] array;
    array = tempArray;
}

template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs) {
    if (lhs.size() == rhs.size()) {
        for (int i = 0; i < lhs.size(); i++) {
            if (lhs.at(i) == rhs.at(i)) {
                continue;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}


template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs) {
    if (lhs.size() == rhs.size()) {
        for (int i = 0; i < lhs.size(); i++) {
            if (lhs.at(i) == rhs.at(i)) {
                continue;
            } else {
                return true;
            }
        }
    } else {
        return true;
    }
    return false;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v) {
    for (int i = 0; i < v.size(); i++) {
        os << v.at(i);
        if (i != v.size() -1) {
            os << ' ';
        }
    }
    return os;
}
