/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/
#include <iostream>
#include <string>
#include <cassert>

const float fillingCoef = 0.75;

int hashForString(const std::string& str, const int& cap) {
    const int a = 37;
    int hash = 0;
    for(int i = 0; i < str.length(); ++i) {
        hash = (hash * a + str[i]) % cap;
    }
    return hash;
}

template <class T, class P>
int Hash(const T& value, const int& cap, const P& hashing) {
    if(cap < 1) {
        assert(false);
    }
    // int hash = hashing(value, cap);
    // return hash;
    return hashing(value, cap);
}

template <class T>
class HashTable {
public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable<T>& other) = delete;
    HashTable(HashTable<T>&& other);
    HashTable<T>& operator=(const HashTable<T>& other) = delete;
    HashTable<T>& operator=(HashTable<T>&& other);

    bool Insert(const T& value);
    bool Remove(const T& value);
    bool Has(const T& value);

private:
    T* table;
    int size;
    int cap;

    void expand();
    int probing(int hash, int iter);
};

template <class T>
HashTable<T>::HashTable(): size(0), cap(8) {
    table = new T[cap];
}

template <class T>
HashTable<T>::~HashTable() {
    delete[] table;
}

template <class T>
HashTable<T>::HashTable(HashTable<T>&& other) {
    *this = std::move(other);
}

template <class T>
HashTable<T>& HashTable<T>::operator=(HashTable<T>&& other) {
    table = other.table;
    size = other.size;
    cap = other.cap;

    other.table = NULL;
    other.size = 0;
    other.cap = 0;

    return *this;
}

template <class T>
bool HashTable<T>::Insert(const T& value) {
    if(Has(value)) {
        return false;
    }

    if((float)size / (float)cap >= fillingCoef) {
        expand();
    }

    int hash = Hash(value, cap, hashForString);
    int key = hash;
    for(int i = 0; i < cap; ++i) {
        if(table[key] == "" || table[key] == "DELETED") {
            table[key] = value;
            ++size;
            return true;
        }
        key = (probing(hash, i) % cap);
    }
    return false;
}

template <class T>
bool HashTable<T>::Remove(const T& value) {
    if(size == 0) {
        return false;
    }

    int hash = Hash(value, cap, hashForString);
    int key = hash;
    for(int i = 0; i < cap; ++i) {
        if(table[key] == value) {
            table[key] = "DELETED";
            --size;
            return true;
        } else if(table[key] == "") {
            return false;
        }
        key = (probing(hash, i) % cap);
    }

    return false;
}

template <class T>
bool HashTable<T>::Has(const T& value) {
    if(size == 0) {
        return false;
    }

    int hash = Hash(value, cap, hashForString);
    int key = hash;
    for(int i = 0; i < cap; ++i) {
        if(table[key] == value) {
            return true;
        } else if(table[key] == "") {
            return false;
        }
        key = (probing(hash, i) % cap);
    }

    return false;
}

template <class T>
void HashTable<T>::expand() {
    int new_cap = cap * 2;
    T* new_table = new T[new_cap];

    for(int i = 0; i < cap; ++i) {
        if(table[i] == "DELETED" || table[i] == "") {
            continue;
        }
        int hash = Hash(table[i], new_cap, hashForString);
        int key = hash;
        if(new_table[key] == "") {
            new_table[key] = table[i];
        } else {
            for(int j = 0; j < new_cap; ++j) {
                key = (probing(hash, j) % new_cap);
                if(new_table[key] == "") {
                    new_table[key] = table[i];
                    break;
                }
            }
        }
    }

    delete[] table;
    cap = new_cap;
    table = new T[cap];
    for(int i = 0; i < cap; ++i) {
        table[i] = new_table[i];
    }
    delete[] new_table;
}

template<class T>
int HashTable<T>::probing(int hash, int iter) {
    if(iter == 0 && hash == 0) {
        return 0;
    }
    return ((hash + iter - 1) + iter * 2);
}


int main() {
    HashTable<std::string> table;
    std::string str = "";
    char symb = 0;

    while(std::cin >> symb >> str) {
        bool res = 0;
        switch(symb) {
            case '+':
                std::cout << (table.Insert(str) ? "OK" : "FAIL") << '\n';
                break;
            case '-':
                std::cout << (table.Remove(str) ? "OK" : "FAIL") << '\n';
                break;
            case '?':
                std::cout << (table.Has(str) ? "OK" : "FAIL") << '\n';
                break;
            default:
                assert(false);
        }
    }

    return 0;
}
