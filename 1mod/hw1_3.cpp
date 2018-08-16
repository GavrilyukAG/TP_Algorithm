/*Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
 Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
n, m ≤ 100000.
1 2 3 4 5 5
1 2 5 6 8 9 10
*/

#include <iostream>
#include <cassert>

int pairSum(int sizeA, int sizeB, int k, int* arrA, int* arrB) {
    assert(sizeA > 0 && sizeB > 0);
    int countPair = 0;
    int tmpJ = sizeB - 1;
    for(int i = 0; i < sizeA; ++i) {
        int j = tmpJ;
        for(; j >= 0; --j) {
            int buf = arrA[i] + arrB[j];
            if(buf > k) {
                continue;
            } else if(buf < k) {
                tmpJ = j;
                break;
            } else {
                tmpJ = --j;
                ++countPair;
                break;
            }
        }
    }
    return countPair;
}

int main() {

    int sizeA = 0;
    std::cin >> sizeA;
    assert(sizeA > 0);
    int* arrA = new int[sizeA];
    for (int i = 0; i < sizeA; ++i) {
        std::cin >> arrA[i];
    }

    int sizeB = 0;
    std::cin >> sizeB;
    assert(sizeB > 0);
    // if(sizeB <= 0) {
    //     delete[] arrA;
    //     return 0;
    // }
    int* arrB = new int[sizeB];
    for(int i = 0; i < sizeB; ++i) {
        std::cin >> arrB[i];
    }

    int k = 0;
    std::cin >> k;

    std::cout << pairSum(sizeA, sizeB, k, arrA, arrB);

    delete[] arrA;
    delete[] arrB;

    return 0;
}
