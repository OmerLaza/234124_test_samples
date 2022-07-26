#ifndef QUEUE_H
#define QUEUE_H

#include <new>
#include <cassert>

template<class T>
class Queue
{
public:
    Queue() : m_head(nullptr), m_size(EMPTY_QUEUE_SIZE)
    {
    }

    ~Queue();

    Queue(const Queue& queue);

    Queue& operator=(const Queue& queue);

    int size() const;

    void pushBack(const T& item);

    const T& front() const;

    T& front();

    void popFront();

    class Iterator;

    Iterator begin();

    Iterator end();

    class ConstIterator;

    ConstIterator begin() const;

    ConstIterator end() const;

    class EmptyQueue;

private:
    const static int EMPTY_QUEUE_SIZE = 0;

    class Node;

    Node* m_head;
    int m_size;

    Node* operator[](int index) const;

    T& getHeadNodeData() const;

    void deleteQueueNodes(Node* firstNodeToDelete);

    Node* copyQueueNodes(const Queue<T>& other);
};

template<class T>
int Queue<T>::size() const
{
    return m_size;
}

template<class T>
Queue<T>::~Queue()
{
    deleteQueueNodes(m_head);
}

/**
 * deletes all the nodes in the queue after the firstNodeToDelete
 * @tparam T queue datatype
 * @param firstNodeToDelete the first node to delete (the function deletes all the nodes after it)
 */
template<class T>
void Queue<T>::deleteQueueNodes(Queue::Node* firstNodeToDelete)
{
    Node* current = firstNodeToDelete;
    while (current != nullptr) {
        Node* next = current->getNext();
        delete current;
        current = next;
    }
}

/**
 * Copy logic of queue.
 * @tparam T : datatype of queue
 * @param other : queue to copy nodes from
 * @return pointer to the first node of the copied nodes
 */
template<class T>
typename Queue<T>::Node* Queue<T>::copyQueueNodes(const Queue<T>& other)
{
    Node* head = new Node(other.m_head->getData());
    Node* current = head;
    Node* otherNode = other.m_head->getNext();
    while (otherNode != nullptr) {
        try {
            current->setNext(new Node(otherNode->getData()));
            current = current->getNext();
            otherNode = otherNode->getNext();
        } catch (std::bad_alloc& badAlloc) {
            // if an allocation fails in the middle of the copying process, we should release the memory that was
            // allocated before it to avoid memory leaks, and then re-throw the exception.
            deleteQueueNodes(head);
            throw badAlloc;
        }
    }
    return head;
}

template<class T>
Queue<T>::Queue(const Queue& queue) : m_head(nullptr), m_size(EMPTY_QUEUE_SIZE)
{
    if (queue.m_size == EMPTY_QUEUE_SIZE)
        return;
    m_head = copyQueueNodes(queue);
    m_size = queue.m_size;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
    if (this == &queue) {
        return *this;
    }
    if (queue.size() == EMPTY_QUEUE_SIZE) {
        m_head = nullptr;
        m_size = EMPTY_QUEUE_SIZE;
        return *this;
    }
    Node* head = copyQueueNodes(queue);
    deleteQueueNodes(m_head);
    m_head = head;
    m_size = queue.m_size;
    return *this;
}

template<class T>
typename Queue<T>::Node* Queue<T>::operator[](int index) const
{
    assert(index < m_size && index >= 0);
    Node* current = m_head;
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }
    return current;
}

template<class T>
void Queue<T>::pushBack(const T& item)
{
    assert(m_size >= EMPTY_QUEUE_SIZE);
    Node* newNode = new Node(item);
    if (m_size == EMPTY_QUEUE_SIZE) {
        assert(m_head == nullptr);
        m_head = newNode;
    } else {
        Node* lastNode = (*this)[m_size - 1];
        lastNode->setNext(newNode);
    }
    m_size++;
}

template<class T>
const T& Queue<T>::front() const
{
    return this->getHeadNodeData();
}

template<class T>
T& Queue<T>::front()
{
    return this->getHeadNodeData();
}

template<class T>
T& Queue<T>::getHeadNodeData() const
{
    if (m_size == EMPTY_QUEUE_SIZE) {
        throw EmptyQueue();
    }
    assert(m_size > EMPTY_QUEUE_SIZE);
    return m_head->getData();
}

template<class T>
void Queue<T>::popFront()
{
    if (m_size == EMPTY_QUEUE_SIZE) {
        assert(m_head == nullptr);
        throw EmptyQueue(); // https://piazza.com/class/l0tbx31evh31vr?cid=705
    }
    assert(m_size > EMPTY_QUEUE_SIZE);
    Node* first = m_head;
    Node* second = m_head->getNext();
    m_head = second;
    delete first;
    m_size--;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(m_head);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(nullptr);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(m_head);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(nullptr);
}

template<class T>
class Queue<T>::Node
{
public:
    explicit Node(const T& data) : m_data(data), m_next(nullptr)
    {
    }

    ~Node() = default;

    Node(const Node& node) = default;

    Node& operator=(const Node& node) = default;

    T& getData()
    {
        return m_data;
    }

    Node* getNext()
    {
        return m_next;
    }

    void setNext(Node* newNode)
    {
        m_next = newNode;
    }

private:
    T m_data;
    Node* m_next;
};

template<class T>
class Queue<T>::Iterator
{
public:
    explicit Iterator(Node* node) : m_current(node)
    {
    }

    ~Iterator() = default;

    Iterator(const Iterator& iterator) = default;

    Iterator& operator=(const Iterator&) = default;

    T& operator*()
    {
        if (m_current == nullptr) {
            throw InvalidOperation();
        }
        return m_current->getData();
    }

    Iterator operator++()
    {
        if (m_current == nullptr) {
            throw InvalidOperation();
        }
        m_current = m_current->getNext();
        return *this;
    }

    bool operator!=(const Iterator& iterator)
    {
        return m_current != iterator.m_current;
    }

    class InvalidOperation;

private:
    Node* m_current;
};


template<class T>
class Queue<T>::ConstIterator
{
public:
    explicit ConstIterator(Node* node) : m_current(node)
    {
    };

    ~ConstIterator() = default;

    ConstIterator(const ConstIterator& iterator) = default;

    const T& operator*()
    {
        if (m_current == nullptr) {
            throw InvalidOperation();
        }
        return m_current->getData();
    }

    ConstIterator operator++()
    {
        if (m_current == nullptr) {
            throw InvalidOperation();
        }
        m_current = m_current->getNext();
        return *this;
    }

    bool operator!=(const ConstIterator& iterator)
    {
        return m_current != iterator.m_current;
    }

    class InvalidOperation;

private:
    Node* m_current;
};

template<class T>
class Queue<T>::EmptyQueue
{
public:
    EmptyQueue() = default;

    ~EmptyQueue() = default;

    EmptyQueue(const EmptyQueue&) = default;
};

template<class T>
class Queue<T>::Iterator::InvalidOperation
{
public:
    InvalidOperation() = default;

    ~InvalidOperation() = default;

    InvalidOperation(const InvalidOperation&) = default;
};

template<class T>
class Queue<T>::ConstIterator::InvalidOperation
{
public:
    InvalidOperation() = default;

    ~InvalidOperation() = default;

    InvalidOperation(const InvalidOperation&) = default;
};

template<class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition function)
{
    // should be returned by value, not by reference https://piazza.com/class/l0tbx31evh31vr?cid=859
    Queue<T> newQueue;
    // can assume condition takes consts https://piazza.com/class/l0tbx31evh31vr?cid=851_f1
    for (const T& item: queue) {
        if (function(item)) {
            newQueue.pushBack(item);
        }
    }
    return newQueue;
}

template<class T, class Condition>
void transform(Queue<T>& queue, Condition function)
{
    for (T& item: queue) {
        function(item);
    }
}

#endif //QUEUE_H