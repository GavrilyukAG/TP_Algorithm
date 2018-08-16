/*
4_3. Тупики.
На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.
Формат входных данных. Вначале вводится n - количество электричек в расписании. Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
Формат выходных данных. Натуральное число - минимальное количеством тупиков.
Максимальное время: 50мс, память: 5Мб.
*/
#include <iostream>
#include <cassert>

struct Train {
    int arrival_time;
    int departure_time;
};

class Heap {
public:
    Heap();

    ~Heap();
    Heap(const Heap&) = delete;
    Heap(Heap&& other);
    Heap& operator=(const Heap&) = delete;
    Heap& operator=(Heap&&);

    Train ExtractFirst();
    void HeapInsert(Train t);
    int HeapSize();

private:
    int cap;
    int size;
    Train* trains;
    void expand();

    void SiftUp(int index);
    void SiftDown(int index);
};

Heap::Heap(): cap(5), size(0) {
    trains = new Train[cap];
}

Heap::~Heap() {
    delete[] trains;
}

Heap::Heap(Heap&& other) {
    *this = std::move(other);
}

Heap& Heap::operator=(Heap&& other) {
    delete[] trains;
    trains = other.trains;
    other.trains = nullptr;
    return *this;
}

int Heap::HeapSize() {
    return size;
}

Train Heap::ExtractFirst() {
    assert(size >= 0);

    Train buf = trains[0];
    trains[0] = trains[size - 1];
    --size;
    if(size > 0) {
        SiftDown(0);
    }

    return buf;
}

void Heap::HeapInsert(Train t) {
    if(size == cap) {
        expand();
    }
    if(size != 0 && trains[0].departure_time < t.arrival_time) {
        ExtractFirst();
    }
    trains[size] = t;
    SiftUp(size);
    ++size;
}

void Heap::SiftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if(trains[index].departure_time >= trains[parent].departure_time) {
            return;
        }
        std::swap(trains[index], trains[parent]);
        index = parent;
    }
}

void Heap::SiftDown(int index) {
    while(true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int parent = index;

        if(left < size && trains[parent].departure_time > trains[left].departure_time) {
            parent = left;
        }
        if(right < size && trains[parent].departure_time > trains[right].departure_time) {
            parent = right;
        }

        if(parent != index) {
            std::swap(trains[index], trains[parent]);
            //SiftDown(parent);
            index = parent;
        } else {
            break;
        }
    }
}

void Heap::expand() {
    Train* buf = new Train[cap * 2];
    for (int i = 0; i < cap; ++i) {
        buf[i] = trains[i];
    }
    delete[] trains;

    trains = new Train[cap * 2];
    for (int i = 0; i < cap; ++i) {
        trains[i] = buf[i];
    }
    delete[] buf;
    cap *= 2;
}


int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    Heap myHeap;
    Train* train = new Train[n];
    for(int i = 0; i < n; ++i) {
        std::cin >> train[i].arrival_time >> train[i].departure_time;
        myHeap.HeapInsert(train[i]);
    }
    std::cout << myHeap.HeapSize();

    delete[] train;
    return 0;
}
