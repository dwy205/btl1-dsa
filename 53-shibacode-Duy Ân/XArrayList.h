
#ifndef XARRAYLIST_H
#define XARRAYLIST_H
#include <memory.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>

#include "list/IList.h"
using namespace std; 
template <class T>
class XArrayList : public IList<T> {
public:
    class Iterator;  // forward declaration

protected:
    T* data;
    int capacity;
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(XArrayList<T>*);

public:
    XArrayList(void (*deleteUserData)(XArrayList<T>*) = 0,
        bool (*itemEqual)(T&, T&) = 0, int capacity = 10);
    XArrayList(const XArrayList<T>& list);
    XArrayList<T>& operator=(const XArrayList<T>& list);
    ~XArrayList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T& get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string(*item2str)(T&) = 0);
    // Inherit from IList: BEGIN

    void println(string(*item2str)(T&) = 0) {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T>*) = 0) {
        this->deleteUserData = deleteUserData;
    }

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, count); }

protected:
    void checkIndex(int index);      // check validity of index for accessing
    void ensureCapacity(int index);  // auto-allocate if needed
    void copyFrom(const XArrayList<T>& list);
    void removeInternalData();

    //! FUNTION STATIC
protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T&)) {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

public:
    static void free(XArrayList<T>* list) {
        typename XArrayList<T>::Iterator it = list->begin();
        while (it != list->end()) {
            delete* it;
            it++;
        }
    }

public:
    class Iterator {
    private:
        int cursor;
        XArrayList<T>* pList;

    public:
        Iterator(XArrayList<T>* pList = 0, int index = 0) {
            this->pList = pList;
            this->cursor = index;
        }
        Iterator& operator=(const Iterator& iterator) {
            cursor = iterator.cursor;
            pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0) {
            T item = pList->removeAt(cursor);
            if (removeItemData != 0) removeItemData(item);
            cursor -= 1;  // MUST keep index of previous, for ++ later
        }

        T& operator*() { return pList->data[cursor]; }
        bool operator!=(const Iterator& iterator) {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator& operator++() {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
};

//! ////////////////////////////////////////////////////////////////////
//! //////////////////////     METHOD DEFNITION      ///////////////////
//! ////////////////////////////////////////////////////////////////////

template <class T>
XArrayList<T>::XArrayList(void (*deleteUserData)(XArrayList<T>*),
    bool (*itemEqual)(T&, T&), int capacity) : capacity(capacity), itemEqual(itemEqual), deleteUserData(deleteUserData) {
    // TODO implement
    this->count = 0;
    this->data = new T[capacity];

}

template <class T>
XArrayList<T>::XArrayList(const XArrayList<T>& list) :capacity(list.capacity), count(list.count) {
    // TODO implement
    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = list.data[i];
    }
}
template <class T>
XArrayList<T>& XArrayList<T>::operator=(const XArrayList<T>& list) {
    // TODO implement
    if (this != &list) {
        delete[] data;
        capacity = list.capacity;
        this->count = list.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = list.data[i];
        }
        return *this;
    }
}

template <class T>
XArrayList<T>::~XArrayList() {
    // TODO implement
    removeInternalData();
}

template <class T>
void XArrayList<T>::add(T e) {
    // TODO implement
    ensureCapacity(count + 1);
    data[count++] = e;
}

template <class T>
void XArrayList<T>::add(int index, T e) {
    // TODO implement
    if (index < 0 || index > count) {
        throw out_of_range("Index is out of range!");
    }
    ensureCapacity(count+1);

    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;
    count++;
}

template <class T>
T XArrayList<T>::removeAt(int index) {
    // TODO implement
    if (index < 0 || index >= count)
        throw std::out_of_range("Index is out of range!");

    T removedItem = data[index]; // Store the item to be removed

    for (int i = index; i < count - 1; ++i) {
        data[i] = data[i + 1]; // Shift elements left
    }

    count--; // Reduce count by 1
    return removedItem;
}

template <class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T)) {
    // TODO implement
    for (int i = 0; i < count; i++) {
        if (equals(data[i], item, itemEqual) == 1) {
            if (removeItemData != 0) removeItemData(data[i]);


            for (int j = i; j < count - 1; j++) {
                data[j] = data[j + 1];
            }

            count--;
            return true;
        }
    }
    return false;
}

template <class T>
bool XArrayList<T>::empty() {
    // TODO implement
    return count == 0;
}

template <class T>
int XArrayList<T>::size() {
    // TODO implement
    return count;
}

template <class T>
void XArrayList<T>::clear() {
    // TODO implement
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    count = 0;
    capacity = 0;
}

template <class T>
T& XArrayList<T>::get(int index) {
    // TODO implement
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range!");
    }
    return data[index];
}

template <class T>
int XArrayList<T>::indexOf(T item) {
    // TODO implement
    for (int i = 0; i < count; i++) {
        if (equals(data[i], item, itemEqual) == 1) {
            return i;
        }
    }
    return -1;
}

template <class T>
bool XArrayList<T>::contains(T item) {
    // TODO implement
    return indexOf(item) != -1;
}

template <class T>
string XArrayList<T>::toString(string(*item2str)(T&)) {
    // TODO implement
    string result = "[";
    for (int i = 0; i < count; i++) {
        if (item2str != nullptr) {
            result += item2str(data[i]);
        }
        else {

            if constexpr (is_arithmetic<T>::value) {
                result += to_string(data[i]);
            }
        }
        if (i < count - 1) {
            result += ", ";
        }
    }
    result += ']';
    return result;
}

//! ////////////////////////////////////////////////////////////////////
//! ////////////////////// (private) METHOD DEFNITION //////////////////
//! ////////////////////////////////////////////////////////////////////
template <class T>
void XArrayList<T>::checkIndex(int index) {
    /**
     * Validates whether the given index is within the valid range of the list.
     * Throws an std::out_of_range exception if the index is negative or exceeds
     * the number of elements. Ensures safe access to the list's elements by
     * preventing invalid index operations.
     */
     // TODO implement
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range!");
    }
}
template <class T>
void XArrayList<T>::ensureCapacity(int index) {
    /**
     * Ensures that the list has enough capacity to accommodate the given index.
     * If the index is out of range, it throws an std::out_of_range exception. If
     * the index exceeds the current capacity, reallocates the internal array with
     * increased capacity, copying the existing elements to the new array. In case
     * of memory allocation failure, catches std::bad_alloc.
     */
     // TODO implement
    if (index > capacity) {
        T* newdata = new T[2 * capacity + 1];
        for (int i = 0; i < count; i++) {
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
        capacity = 2 * capacity + 1;
    }
}

template <class T>
void XArrayList<T>::copyFrom(const XArrayList<T>& list) {
    /*
     * Copies the contents of another XArrayList into this list.
     * Initializes the list with the same capacity as the source list and copies
     * all elements. Also duplicates user-defined comparison and deletion
     * functions, if applicable.
     */
     // TODO implement
    if (this == &list) {
        return;
    }


    delete[] data;
    count = list.count;
    capacity = list.capacity;


    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = list.data[i];
    }
}



template <class T>
void XArrayList<T>::removeInternalData() {
    /*
     * Clears the internal data of the list by deleting the dynamic array and any
     * user-defined data. If a custom deletion function is provided, it is used to
     * free the stored elements. Finally, the dynamic array itself is deallocated
     * from memory.
     */
     // TODO implement
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    count = 0;
    capacity = 0;
}
#endif /* XARRAYLIST_H */
