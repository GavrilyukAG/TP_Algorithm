/*
7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/
#include <iostream>

template <class T>
bool bit(const T number, int digit) {
    return (number >> digit) & 1;
}

template <class T>
void binaryQuickSort(T* arr, int begin, int end, int digit) {
    if(digit < 0 || begin >= end) {
        return;
    }

    int i = begin;
    int j = end;

    while(i < j) {
        while(bit(arr[i], digit) == 0 && i < j) {
            ++i;
        }
        while(bit(arr[j], digit) == 1 && i < j) {
            --j;
        }
        if(i < j) {
            std::swap(arr[i], arr[j]);
        }
    }

    if(bit(arr[j], digit) == 0) {
        ++j;
    }

    binaryQuickSort(arr, begin, j - 1, digit - 1);
    binaryQuickSort(arr, j, end, digit - 1);
}

int main() {
    int n = 0;
    std::cin >> n;
    if(n < 1) {
        return 0;
    }

    unsigned long long* arr = new unsigned long long[n];
    for(int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    binaryQuickSort(arr, 0, n - 1, 63);

    for(int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }

    delete[] arr;
    return 0;
}
