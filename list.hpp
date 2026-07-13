#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {

/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
private:
    // Node structure for the doubly linked list
    struct Node {
        T data;
        Node* prev;
        Node* next;
        
        Node() : prev(nullptr), next(nullptr) {}
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    // Sentinel node to simplify edge cases
    Node* head;  // points to the sentinel node
    size_t list_size;

protected:
    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    Node* insert(Node* pos, Node* cur) {
        cur->next = pos;
        cur->prev = pos->prev;
        if (cur->prev) cur->prev->next = cur;
        pos->prev = cur;
        return cur;
    }
    
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    Node* erase(Node* pos) {
        if (pos == head) throw container_is_empty();
        
        Node* prev_node = pos->prev;
        Node* next_node = pos->next;
        
        if (prev_node) prev_node->next = next_node;
        if (next_node) next_node->prev = prev_node;
        
        if (pos == head) head = next_node;
        return pos;
    }

public:
    class const_iterator;
    class iterator {
    private:
        Node* node_ptr;
        
    public:
        iterator() : node_ptr(nullptr) {}
        explicit iterator(Node* ptr) : node_ptr(ptr) {}
        
        // iter++
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        
        // ++iter
        iterator& operator++() {
            if (!node_ptr || node_ptr == head) throw invalid_iterator();
            node_ptr = node_ptr->next;
            return *this;
        }
        
        // iter--
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
        
        // --iter
        iterator& operator--() {
            if (!node_ptr || node_ptr == head) throw invalid_iterator();
            node_ptr = node_ptr->prev;
            return *this;
        }
        
        // *it
        T& operator*() const {
            if (!node_ptr || node_ptr == head) throw container_is_empty();
            return node_ptr->data;
        }
        
        // it->field
        T* operator->() const {
            if (!node_ptr || node_ptr == head) throw container_is_empty();
            return &(node_ptr->data);
        }
        
        // == operator
        bool operator==(const iterator& rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        
        bool operator==(const const_iterator& rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        
        // != operator
        bool operator!=(const iterator& rhs) const {
            return node_ptr != rhs.node_ptr;
        }
        
        bool operator!=(const const_iterator& rhs) const {
            return node_ptr != rhs.node_ptr;
        }
    };
    
    /**
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
    private:
        const Node* node_ptr;
        
    public:
        const_iterator() : node_ptr(nullptr) {}
        explicit const_iterator(const Node* ptr) : node_ptr(ptr) {}
        const_iterator(const iterator& other) : node_ptr(other.node_ptr) {}
        
        // iter++
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        
        // ++iter
        const_iterator& operator++() {
            if (!node_ptr || node_ptr == head) throw invalid_iterator();
            node_ptr = node_ptr->next;
            return *this;
        }
        
        // iter--
        const_iterator operator--(int) {
            const_iterator old = *this;
            --(*this);
            return old;
        }
        
        // --iter
        const_iterator& operator--() {
            if (!node_ptr || node_ptr == head) throw invalid_iterator();
            node_ptr = node_ptr->prev;
            return *this;
        }
        
        // *it
        const T& operator*() const {
            if (!node_ptr || node_ptr == head) throw container_is_empty();
            return node_ptr->data;
        }
        
        // it->field
        const T* operator->() const {
            if (!node_ptr || node_ptr == head) throw container_is_empty();
            return &(node_ptr->data);
        }
        
        // == operator
        bool operator==(const const_iterator& rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        
        bool operator==(const iterator& rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        
        // != operator
        bool operator!=(const const_iterator& rhs) const {
            return node_ptr != rhs.node_ptr;
        }
        
        bool operator!=(const iterator& rhs) const {
            return node_ptr != rhs.node_ptr;
        }
    };

public:
    /**
     * Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() {
        head = new Node();
        head->prev = head;
        head->next = head;
        list_size = 0;
    }
    
    list(const list& other) {
        head = new Node();
        head->prev = head;
        head->next = head;
        list_size = 0;
        
        for (const T& item : other) {
            push_back(item);
        }
    }
    
    /**
     * Destructor
     */
    ~list() {
        clear();
        delete head;
    }
    
    /**
     * Assignment operator
     */
    list& operator=(const list& other) {
        if (this == &other) return *this;
        
        clear();
        
        for (const T& item : other) {
            push_back(item);
        }
        
        return *this;
    }
    
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T& front() const {
        if (empty()) throw container_is_empty();
        return head->next->data;
    }
    
    const T& back() const {
        if (empty()) throw container_is_empty();
        return head->prev->data;
    }
    
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(head->next);
    }
    
    const_iterator cbegin() const {
        return const_iterator(head->next);
    }
    
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(head);
    }
    
    const_iterator cend() const {
        return const_iterator(head);
    }
    
    /**
     * checks whether the container is empty.
     */
    bool empty() const {
        return list_size == 0;
    }
    
    /**
     * returns the number of elements
     */
    size_t size() const {
        return list_size;
    }
    
    /**
     * clears the contents
     */
    void clear() {
        Node* current = head->next;
        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        
        head->prev = head;
        head->next = head;
        list_size = 0;
    }
    
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    iterator insert(iterator pos, const T& value) {
        if (pos.node_ptr == nullptr || pos.node_ptr == head) throw invalid_iterator();
        
        Node* new_node = new Node(value);
        insert(pos.node_ptr, new_node);
        list_size++;
        return iterator(new_node);
    }
    
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    iterator erase(iterator pos) {
        if (pos.node_ptr == nullptr || pos.node_ptr == head) throw invalid_iterator();
        
        Node* next_node = pos.node_ptr->next;
        erase(pos.node_ptr);
        delete pos.node_ptr;
        list_size--;
        return iterator(next_node);
    }
    
    /**
     * adds an element to the end
     */
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        insert(head, new_node);
        list_size++;
    }
    
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() {
        if (empty()) throw container_is_empty();
        erase(iterator(head->prev));
    }
    
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        insert(head->next, new_node);
        list_size++;
    }
    
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() {
        if (empty()) throw container_is_empty();
        erase(iterator(head->next));
    }
    
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort() {
        if (list_size <= 1) return;
        
        // Convert to array for sorting
        std::vector<T> array;
        for (const T& item : *this) {
            array.push_back(item);
        }
        
        // Use the provided sort function
        sjtu::sort(array.data(), array.data() + array.size(), 
                  [](const T& a, const T& b) { return a < b; });
        
        // Rebuild the list
        clear();
        for (const T& item : array) {
            push_back(item);
        }
    }
    
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list& other) {
        if (other.empty()) return;
        
        if (empty()) {
            *this = other;
            return;
        }
        
        // Find the first node in each list
        Node* this_node = head->next;
        Node* other_node = other.head->next;
        
        // Connect the lists
        head->prev->next = other.head->next;
        other.head->next->prev = head->prev;
        other.head->prev->next = head;
        head->prev = other.head->prev;
        
        // Update size
        list_size += other.list_size;
        other.list_size = 0;
        
        // Reset other list
        other.head->prev = other.head;
        other.head->next = other.head;
    }
    
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() {
        if (list_size <= 1) return;
        
        Node* current = head->next;
        while (current != head) {
            std::swap(current->prev, current->next);
            current = current->next; // Now points to the previous node
        }
        
        // Swap the head's prev and next pointers
        std::swap(head->prev, head->next);
    }
    
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() {
        if (list_size <= 1) return;
        
        Node* current = head->next;
        while (current != head) {
            if (current->next != head && current->data == current->next->data) {
                Node* to_delete = current->next;
                current->next = to_delete->next;
                to_delete->next->prev = current;
                delete to_delete;
                list_size--;
            } else {
                current = current->next;
            }
        }
    }
};

} // namespace sjtu

#endif // SJTU_LIST_HPP
