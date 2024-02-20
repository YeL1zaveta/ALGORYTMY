#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <ctime> 
#include< string > 
using namespace std;
template <typename T>
class Dyn_Arr {
private:
    T* arr;         // Wskaźnik do tablicy dynamicznej
    int capacity;   // Pojemność tablicy
    int size;

public:
    Dyn_Arr() {
        capacity = 1;  // Początkowa pojemność
        size = 0;      // Początkowy rozmiar
        arr = new T[capacity];
    }

    ~Dyn_Arr() {
        delete[] arr;
    }

    T* Getarr() const {
        return arr;
    }
    int  Getcapacity() const {
        return capacity;
    }

    int Getsize() const {
        return size;
    }

    void Setarr(T* a) {
        arr = a;
    }
    void Setcapacity(int ca)const {
        capacity = ca;
    }
    void Setsize(int si)const {
        size = si;
    }
    void pushBack(const T& data) {
        if (size >= capacity) {
            // Jeśli tablica jest pełna, zwiększ jej rozmiar
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }

        arr[size] = data;
        size++;
    }
    void clear() {
        delete[] arr;
        capacity = 1;
        size = 0;
        arr = new T[capacity];
    }
    T get(int index) {
        return arr[index];
    }
    void sortowanie_babelkowe(bool (*comparator)(const T, const T)) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (comparator(arr[j], arr[j + 1])) {
                    // Zamiana miejscami, jeśli komparator zwraca true
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

}; 

class MojObiekt {
private:
    int INT;
    char CHAR;

public:
    MojObiekt() : INT(rand() % 50), CHAR('a' + (rand() % 26)) {}

    int GetINT() const {
        return INT;
    }

    char GetCHAR() const {
        return CHAR;
    }
    std::string to_string() const {
        return  std::to_string(INT) + CHAR;
    }
};

int main() {
    cout << "START" << endl;
    Dyn_Arr<MojObiekt*>* tab = new Dyn_Arr<MojObiekt*>();

    int numElements = 10000000;
    double max_time = 0; 
    clock_t start_time = clock();
    for (int i = 0; i < numElements; i++) {
        MojObiekt* obj = new MojObiekt(); // Tworzenie obiektu 
        clock_t cz = clock();
        tab->pushBack(obj);//Dodawanie wskaźnika do obiektu do tablicy dynamicznej
        clock_t cz2 = clock();
        double cz_time = static_cast<double>(cz2 - cz) / (double) CLOCKS_PER_SEC;
        if (cz_time > max_time) {
             max_time= cz_time;
            cout << "Najgorszy czas: " << cz_time << "  przy elemencie pod numerem :"<< i <<endl;
        }

    }

    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / (double) CLOCKS_PER_SEC;
    cout << "Dodano " << numElements << " obiektów do tablicy dynamicznej w czasie " << elapsed_time  << endl;    
    
    cout << "Tablica:";
   /*for (int i = 0; i < numElements; i++) {
        cout << (tab->Getarr()[i])->to_string() << " ";
    }*/
    // Wyczyść tablicę dynamiczną
    tab->clear();

    return 0;
}