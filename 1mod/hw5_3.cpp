/*
5_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
*/
#include <iostream>
#include <cassert>

struct Point {
    int position;
    bool state; // 1 - начало отрезка, 0 - конец

    Point(): position(0), state(false) {}
};

class MyFunctor {
public:
    MyFunctor() {}

    bool operator()(const Point& left, const Point& right) {
        return (left.position < right.position);
    }
};

bool func(const Point& l, const Point& r) {
    return (l.position < r.position);
}

template<class P, class T>
void mergeSort(int pointsCount, P* point, const T& func) {
    if(pointsCount > 1) {
        int firstLength = pointsCount / 2;
        int secondLength = pointsCount - firstLength;
        mergeSort(firstLength, point, func);
        mergeSort(secondLength, point + firstLength, func);

        const int bufSize = firstLength + secondLength;
        P* tmp = new P[bufSize];
        merge(point, firstLength, point + firstLength, secondLength, tmp, func);
        for(int i = 0; i < pointsCount; ++i) {
            point[i] = tmp[i];
        }

        delete[] tmp;
    }
}

template<class P, class T>
void merge(const P* firstArr, int firstArrSize, const P* secondArr, int secondArrSize, P* tmp, const T& func) {
    int firstIter = 0, secondIter = 0;
    int bufIter = 0;
    while(firstIter < firstArrSize && secondIter < secondArrSize) {
        if(func(firstArr[firstIter], secondArr[secondIter])) {
            tmp[bufIter++] = firstArr[firstIter++];
        } else {
            tmp[bufIter++] = secondArr[secondIter++];
        }
    }

    // если остались остатки
    while(firstIter < firstArrSize) {
        tmp[bufIter++] = firstArr[firstIter++];
    }
    while(secondIter < secondArrSize) {
        tmp[bufIter++] = secondArr[secondIter++];
    }
}

int paintedLength(int pointsCount, Point* point) {
    mergeSort(pointsCount, point, func);

    int length = 0; // длина закрашенной части
    int layer = 0; // слой закраски
    int begin = point[0].position;

    for(int i = 0; i < pointsCount; ++i) {
        if(point[i].state) { // если начало отрезка, то слой закрашен
            ++layer;
        } else {
            --layer;
        }
        if(layer == 0) {
            length += point[i].position - begin;
            if(pointsCount - i > 1) {
                begin = point[i + 1].position;
            }
        }
    }

    return length;
}

int main() {
    int n = 0; // кол-во отрезков
    std::cin >> n;
    assert(n > 0);
    const int pointsCount = n * 2; // кол-во точек

    Point* point = new Point[pointsCount];
    for(int i = 0; i < pointsCount; ++i) {
        std::cin >> point[i].position;
        point[i].state = true;
        std::cin >> point[++i].position;
    }
    std::cout << paintedLength(pointsCount, point);

    delete[] point;
    return 0;
}
