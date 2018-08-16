/*
Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива
строго возрастают, а на интервале [m, n-1] строго убывают.
Найти m за O(log m).
2 ≤ n ≤ 10000.
in:
10
1 2 3 4 5 6 7 6 5 4
out: 6
*/

#include <iostream>
#include <cassert>

int unimod(int n, int* arr) {
    assert(n > 1);

    if (n == 2) {
        int ind = 1;
        arr[ind] > arr[ind - 1] ? ind : --ind;
        return ind;
    }

    int left = 0, right = n;

    for (int i = 1; i < n; i *= 2) {
        if (arr[i] < arr[i - 1]) {
            left = i / 2;
            right = i;
            break;
        }
    }

    while (right > left) {
        int middle = left + (right - left) / 2;
        if ((arr[middle] > arr[middle - 1]) && (arr[middle] > arr[middle + 1])) {
            return middle;
        }
        else if (arr[middle] > arr[middle - 1]) {
            left = middle + 1;
        }
        else if (arr[middle] < arr[middle - 1]) {
            right = middle;
        }
    }

    int ind = n - 1;
    arr[ind] > arr[0] ? ind : ind = 0;
    return ind;
}



int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 1);

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << unimod(n, arr);

    delete[] arr;

    return 0;
}
