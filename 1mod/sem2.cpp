#include <iostream>

struct Range
{ int Min; int Max; } getKeyRange(int* arr, int size) {
    assert(size > 0);
    Range range = { arr[0], arr[0] };
    for (int i = 0; i < size; ++i) {
        if (range.Min > arr[i]) {
            range.Min = arr[i];
        } else if (arr[i] > range.Max) {
            range.Max = arr[i];
        }
    }
    return range;
}

void CountingSort(int* arr, int size) {
    if (size == 0) {
        return;
    }

    // Находим диапозон ключей
    Range range = getKeyRange(arr, size);

    int* keysCount = new int[range.Max - range.Min + 1];
    for (int i = 0; i < size; ++i) {
        keysCount[arr[i] - range.Min]++;
    }

    int currInd = 0;
    for ( int i = 0; i < range.Max - range.Min + 1; ++i) {
        while (keysCount[i] != 0) {
            arr[currInd++] = i + ramge.Min;
            keysCount[i]--;
        }
    }

    delete[] keysCount;
}


int main() {
    int size = 0;
    std::cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    CountingSort(arr, size);

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }

    delete[] arrl
    return 0;
}
