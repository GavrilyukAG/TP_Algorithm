/*
Задача № 3 (4 балла)
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
*/
#include <iostream>
#include <cassert>

class Queue {
public:
    Queue();
    ~Queue();
    Queue(const Queue&) = delete;
    Queue(Queue&& other);
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&);

    void push_back(int value);
    int pop_front();

private:
    int head;
    int tail;
    int cap;
    int size;
    int* arr;
    void expand();
};

Queue::Queue(): cap(10), size(0), head(0), tail(0) {
    arr = new int[cap];
}

Queue::~Queue() {
    delete[] arr;
}

Queue::Queue(Queue&& other) {
    *this = std::move(other);
}

Queue& Queue::operator=(Queue&& other) {
    head = other.head;
    tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;

    return *this;
}

int Queue::pop_front() {
    if(size == 0) {
        return -1;
    }
    const int tmp = arr[head];
    ++head;
    if(head == cap) {
        head = 0;
    }
    --size;
    return tmp;
}

void Queue::push_back(int value) {
    assert(value >= 0);
    if(tail == cap && size < cap) {
        tail = 0;
    }
    if(size == cap) {
        expand();
    }
    arr[tail] = value;
    ++tail;
    ++size;
}

void Queue::expand() {
    if(tail <= head) {
        // int* tmp = new int[cap];
        // for(int iter_arr = head, j = 0; iter_arr < cap; ++iter_arr, ++j) {
        //     tmp[j] = arr[iter_arr];
        // }
        // for(int iter_arr = 0, j = cap - head; iter_arr < tail; ++iter_arr, ++j) {
        //     tmp[j] = arr[iter_arr];
        // }
        // delete[] arr;

        int* tmp = new int[cap * 2];
        for(int i = head, j = 0; i != tail; ++i,++j) {
            if(i == n) {
                i = 0;
            }
            tmp[j] = arr[i];
        }
        delete[] arr;

        // arr = new int[cap * 2];
        // for(int i = 0; i < cap; ++i) {
        //     arr[i] = tmp[i];
        // }
        // delete[] tmp;
        arr = tmp;
        delete[] tmp;

        head = 0;
        tail = cap;
        cap *= 2;
    }
    else {
        int* tmp = new int[cap];
        for(int i = 0; i < cap; ++i) {
            tmp[i] = arr[i];
        }
        delete[] arr;

        arr = new int[cap * 2];
        for(int i = 0; i < cap; ++i) {
            arr[i] = tmp[i];
        }
        delete[] tmp;

        tail = cap;
        cap *= 2;
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    Queue myQ;
    for(int i = 0; i < n; ++i) {
        int id = 0, val = 0;
        std::cin >> id >> val;
        switch(id) {
            case 2:
                if(myQ.pop_front() != val) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                myQ.push_back(val);
                break;
            default:
                assert(false);
        }
    }
    std::cout << "YES";

    return 0;
}
