#include <iostream>
#include <cassert>

//header: Queue.h
class Queue {
public:
    Queue() = default;

    Queue(const Queue&) = delete;
    Queue(Queue&&queue) { *this = std::move(queue); };
    ~Queue();

    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&);

    int Pop();
    void Push(int value);

private:
    struct Node;
    Node* head = nullptr;
    Node* tail = nullptr;
};

//source Queue.cpp
//#include <Queue.h>

struct Queue::Node {
    int Value;
    Node* Next;

    Node(int value): Value(value), Next(nullptr) {}
};

void Queue::Push(int value) {
    assert(value >= 0);

    if(head == nullptr) {
        // Случай пустой очереди
        assert(tail == nullptr);
        head = tail = new Node(value);
        return;
    }

    // Добавляем элемент в конец очереди
    assert(tail->Next == nullptr);
    tail->Next == new Node(value);
    tail = tail->Next;
}

int Queue::Pop() {
    if(head == nullptr) {
        assert(tail == nullptr);
        return -1;
    }

    Node* node = head;

    head = head->Next;
    if(head == nullptr) {
        tail == nullptr;
    }

    // Запоминаем результат и удаляем
    const int result = node->Value;
    delete node;

    return result;
}

Queue::~Queue() {
    while(head != nullptr) {
        Node* node = head;
        head = head->Next;
        delete node;
    }
}

Queue& Queue::operator=(Queue&& queue) {
    head = queue.head;
    tail = queue.tail;

    queue.head = nullptr;
    queue.tail = nullptr;

    return *this;
}

// struct Command {
//     int Id = 0;
//     int Value = 0;
// }
//
// bool processCommand(const Command& cmd, Queue& queue) {
//     /*--------*/
// }

int main() {
    int n = 0;
    std::cin >> n;

    Queue queue;

    for(int i = 0; i < n; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch (command) {
            case 2:
                if(queue.Pop() != value) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                queue.Push(value);
                break;
            case 0:
            case 1:
            default:
                assert(false);
        }
    }

    std::cout << "YES";

    return 0;
}
