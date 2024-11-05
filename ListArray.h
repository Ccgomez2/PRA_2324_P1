#include <stdexcept>
#include <ostream>
#include "List.h"

using namespace std;

template <typename T>
class ListArray : public List<T> {
        
	private:
                T* arr;
                int max;
                int n;
                static const int MINSIZE = 2;

                void resize(int new_size) {
                        T* newArr = new T[new_size];
                        for (int i = 0; i < n; ++i) {
                                newArr[i] = arr[i];
                        }
                        delete[] arr;
                        arr = newArr;
                        max = new_size;
                }

        public:
                 // Constructor
                ListArray() : max(MINSIZE), n(0) {
                        arr = new T[max];
                 }

                 // Destructor
                ~ListArray() {
                        delete[] arr;
                }

                void insert(int pos, T elem) override {
                        if (pos < 0 || pos > n) {  
                                 throw out_of_range("Posición inválida");
                        }

                        if (n >= max) {
                                resize(max * 2);
                        }

                        for (int i = n; i > pos; --i) {
                                arr[i] = arr[i - 1];
                        }

                        arr[pos] = elem;
                        n++;
                }

                // Añadir al final
                void append(T elem) override {
                        insert(n, elem);
                }
                
                // Añadir al principio
                void prepend(T elem) override {
                        insert(0, elem);
                }

                // Eliminar un elemento
                T remove(int pos) override {
                        if (pos < 0 || pos >= n) {
                                throw out_of_range("Posición inválida");
                        }

                        T removedValue = arr[pos];
                        for (int i = pos; i < n - 1; ++i) {
                                arr[i] = arr[i + 1];
                        }
                        --n;

                        if (n < max / 4 && max > MINSIZE) {
                                resize(max / 2);
                        }

                        return removedValue;
                }

                // Obtener un elemento
                T get(int pos) override {
                        if (pos < 0 || pos >= n) {
                                throw out_of_range("Posición inválida");
                        }
                        return arr[pos];
                }

                // Buscar un elemento
                int search(T elem) override {
                        for (int i = 0; i < n; ++i) {
                                if (arr[i] == elem) {
                                        return i; 
                                }
                        }
                        return -1;
                }

                 // Verificar si la lista está vacía
                bool empty() override {
                        return n == 0;
                }

                // Retornar el tamaño de la lista
                int size() override {
                        return n;
                }

                // Sobrecarga del operador []
                T operator[](int pos) {
                        if (pos < 0 || pos >= n) {
                                throw out_of_range("Posición inválida");
                        }
                        return arr[pos];
                }

                // Sobrecarga del operador <<
                friend ostream& operator<<(ostream &out, const ListArray<T> &list) {
                        out << "[";
                        for (int i = 0; i < list.n; ++i) {
                                 out << list.arr[i];
                                if (i < list.n - 1) {
                                        out << ", ";
                                }
                        }
                        out << "]";
                        return out;
                }
};

