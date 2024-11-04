/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>
#include <sstream>
#include <type_traits>

#include "list/IList.h"
using namespace std;

template <class T>
class DLinkedList : public IList<T> {
public:
    class Node;         // Forward declaration
    class Iterator;     // Forward declaration
    class BWDIterator;  // Forward declaration

protected:
    Node* head;
    Node* tail;
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(DLinkedList<T>*);

public:
    DLinkedList(void (*deleteUserData)(DLinkedList<T>*) = 0,
        bool (*itemEqual)(T&, T&) = 0);
    DLinkedList(const DLinkedList<T>& list);
    DLinkedList<T>& operator=(const DLinkedList<T>& list);
    ~DLinkedList();

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
    // Inherit from IList: END

    void println(string(*item2str)(T&) = 0) {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T>*) = 0) {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size) {
        int idx = 0;
        for (DLinkedList<T>::Iterator it = begin(); it != end(); it++) {
            if (!equals(*it, array[idx++], this->itemEqual)) return false;
        }
        return true;
    }

    Iterator begin() { return Iterator(this, true); }
    Iterator end() { return Iterator(this, false); }

    BWDIterator bbegin() { return BWDIterator(this, true); }
    BWDIterator bend() { return BWDIterator(this, false); }

protected:
    void copyFrom(const DLinkedList<T>& list);
    void removeInternalData();
    Node* getPreviousNodeOf(int index);

    //! FUNTION STATIC
public:
    static void free(DLinkedList<T>* list) {
        typename DLinkedList<T>::Iterator it = list->begin();
        while (it != list->end()) {
            delete* it;
            it++;
        }
    }

protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T&)) {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

public:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;
        friend class DLinkedList<T>;

    public:
        Node(Node* next = 0, Node* prev = 0) {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node* next = 0, Node* prev = 0) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

public:
    class Iterator {
    private:
        DLinkedList<T>* pList;
        Node* pNode;

    public:
        Iterator(DLinkedList<T>* pList = 0, bool begin = true) {
            if (begin) {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            }
            else {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator& operator=(const Iterator& iterator) {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0) {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node* pNext = pNode->prev;  // MUST prev, so iterator++ will go to end
            if (removeItemData != 0) removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T& operator*() { return pNode->data; }
        bool operator!=(const Iterator& iterator) {
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload
        Iterator& operator++() {
            pNode = pNode->next;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

    class BWDIterator {
        // TODO implement
    private:
        DLinkedList<T>* pList;
        Node* currentNode;
    public:
        BWDIterator(DLinkedList<T>* pList = 0, bool begin = true) : pList(pList) {
            if (begin) {
                if (pList != 0)
                    this->currentNode = pList->tail->prev;
                else
                    currentNode = 0;
            }
            else {
                if (pList != 0)
                    this->currentNode = pList->head;
                else
                    currentNode = 0;
            }
            this->pList = pList;
        }
        BWDIterator& operator=(const BWDIterator& iterator) {
            if (this != &iterator) {
                this->currentNode = iterator.currentNode;
                this->pList = iterator.pList;
            }
            return *this;
        }
        T& operator*() {
            return currentNode->data;
        }
        bool operator!=(const BWDIterator& iterator) const {
            return currentNode != iterator.currentNode;
        }
        BWDIterator& operator--() {
            if (currentNode != pList->head) { // Avoid going beyond head
                currentNode = currentNode->prev;
            }
            return *this;
        }

        BWDIterator operator--(int) {
            BWDIterator iterator = *this;
            --*this;
            return iterator;
        }
        void remove(void (*removeItemData)(T) = 0) {
            if (currentNode != pList->head && currentNode != pList->tail) {
                currentNode->prev->next = currentNode->next;
                currentNode->next->prev = currentNode->prev;
                Node* currentNext = currentNode->next;
                if (removeItemData != 0) removeItemData(currentNode->data);
                delete currentNode;
                currentNode = currentNext;
                pList->count -= 1;
            }
        }

    };
};
template <class T>
using List = DLinkedList<T>;

//! ////////////////////////////////////////////////////////////////////
//! //////////////////////     METHOD DEFNITION      ///////////////////
//! ////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(void (*deleteUserData)(DLinkedList<T>*),
    bool (*itemEqual)(T&, T&)) {
    // TODO implement
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
    this->count = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& list) : count(0) {
    // TODO implement
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
    Node* temp = list.head->next;
    for (int i = 0; i < list.count; i++) {
        this->add(temp->data);
        temp = temp->next;

    }
}

template <class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& list) {
    // TODO implement
    if (this != &list) {

        clear();
        this->deleteUserData = list.deleteUserData;
        this->itemEqual = list.itemEqual;

        Node* temp = list.head->next;
        while (temp != list.tail) {
            add(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}


template <class T>
DLinkedList<T>::~DLinkedList() {
    // TODO implement
    Node* temp = head->next;
    while (count != 0) {
        Node* current = temp->next;
        delete temp;
        temp = current;
        --count;
    }
    head->next = tail;
    tail->prev = head;
    count = 0;
}

template <class T>
void DLinkedList<T>::add(T e) {
    // TODO implement
    Node* newnode = new Node(e);
    if (count == 0) {
        head->next = newnode;
        newnode->prev = head;
        newnode->next = tail;
        tail->prev = newnode;
    }
    else {

        Node* temp = tail->prev;
        temp->next = newnode;
        newnode->prev = temp;
        newnode->next = tail;
        tail->prev = newnode;

    }
    count++;

}
template <class T>
void DLinkedList<T>::add(int index, T e) {
    // TODO implement

    if (index < 0 || index > count) {
        throw out_of_range("Index is out of range!");
    }

    Node* newnode = new Node(e);

    if (index == 0) {
        // Thêm vào đầu danh sách
        newnode->next = head->next;
        head->next->prev = newnode;
        head->next = newnode;
        newnode->prev = head;
    }
    else if (index == count) {
        // Thêm vào cuối danh sách
        tail->prev->next = newnode;
        newnode->prev = tail->prev;
        tail->prev = newnode;
        newnode->next = tail;
    }
    else {
        // Thêm vào giữa danh sách
        Node* temp = head->next;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        newnode->next = temp;
        newnode->prev = temp->prev;
        temp->prev->next = newnode;
        temp->prev = newnode;
    }
    ++count;
}

template <class T>
T DLinkedList<T>::removeAt(int index) {
    // TODO implement
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range!");
    }
    Node* temp = head->next;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    T removedData = temp->data;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    count--;
    return removedData;
}

template <class T>
bool DLinkedList<T>::empty() {
    // TODO implement
    return count == 0;
}

template <class T>
int DLinkedList<T>::size() {
    // TODO implement
    return count;
}

template <class T>
void DLinkedList<T>::clear() {
    // TODO implement
    Node* temp = head->next;
    while (count != 0) {
        Node* current = temp->next;
        delete temp;
        temp = current;
        --count;
    }
    head->next = tail;
    tail->prev = head;
    count = 0;
}

template <class T>
T& DLinkedList<T>::get(int index) {
    // TODO implement
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range!");
    }
    Node* temp = head->next;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item) {
    // TODO implement
    Node* temp = head->next;
    for (int i = 0; i < count; i++) {
        if (equals(temp->data, item, itemEqual)) {
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T)) {
    // TODO implement
    Node* temp = head->next;
    while (temp != tail) {
        if (equals(temp->data, item, itemEqual)) {

            if (removeItemData != nullptr) {
                removeItemData(temp->data);
            }


            temp->prev->next = temp->next;
            if (temp->next) {
                temp->next->prev = temp->prev;
            }

            delete temp;
            count--;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <class T>
bool DLinkedList<T>::contains(T item) {
    // TODO implement
    return indexOf(item) != -1;
}

template <class T>
string DLinkedList<T>::toString(string(*item2str)(T&)) {
    // TODO implement
    string result = "[";
    Node* temp=head->next;
    for (int i = 0; i < count; i++) {
        if (item2str != nullptr) {
            result += item2str(temp->data);
        }
        else {

            if constexpr (is_arithmetic<T>::value) {
                result += to_string(temp->data);
            }
        }
        if (i < count - 1) {
            result += ", ";
        }
        temp=temp->next;
    }
    result += ']';
    return result;
}

//! ////////////////////////////////////////////////////////////////////
//! ////////////////////// (private) METHOD DEFNITION //////////////////
//! ////////////////////////////////////////////////////////////////////
template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T>& list) {
    /**
     * Copies the contents of another doubly linked list into this list.
     * Initializes the current list to an empty state and then duplicates all data
     * and pointers from the source list. Iterates through the source list and
     * adds each element, preserving the order of the nodes.
     */
     // TODO implement
    if (this == &list) {
        return;
    }
    clear();
    Node* temp = list.head->next;
    this->count = list.count;
    while (temp != list.tail) {
        add(temp->data);
        temp = temp->next;
    }

}

template <class T>
void DLinkedList<T>::removeInternalData() {
    /**
     * Clears the internal data of the list by deleting all nodes and user-defined
     * data. If a custom deletion function is provided, it is used to free the
     * user's data stored in the nodes. Traverses and deletes each node between
     * the head and tail to release memory.
     */
     // TODO implement
    Node* temp = head->next;
    while (count != 0) {
        Node* current = temp->next;
        delete temp;
        temp = current;
        --count;
    }
    head->next = tail;
    tail->prev = head;
}

template <class T>
typename DLinkedList<T>::Node* DLinkedList<T>::getPreviousNodeOf(int index) {
    /**
     * Returns the node preceding the specified index in the doubly linked list.
     * If the index is in the first half of the list, it traverses from the head;
     * otherwise, it traverses from the tail. Efficiently navigates to the node by
     * choosing the shorter path based on the index's position.
     */
     // TODO implement
    if (index < 0 || index >= count) {
        throw out_of_range("Index is out of range");
    }
    int chiso = count / 2;
    if (index < chiso) {
        Node* temp = head->next;
        for (int i = 1; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }
    else {
        Node* temp = tail->prev;
        for (int i = count - 2; i >= index - 1; i--) {
            temp = temp->prev;
        }
        return temp;
    }
}

#endif /* DLINKEDLIST_H */
