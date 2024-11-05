#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {
	private:
		Node<T>* first;
		int n;

	public:
		ListLinked() : first(nullptr), n(0) {}

		~ListLinked() {
			Node<T>* nodePtr = first;
			while (nodePtr != nullptr) {
				Node<T>* aux = nodePtr->next;
				delete nodePtr;
				nodePtr = aux;
			}
		}

		
		void insert(int pos, T elem) override {
			if (pos < 0 || pos > n) {
				throw out_of_range("Posición inválida");
			}

			Node<T>* newNode = new Node<T>(elem);
			if (pos == 0) {
				newNode->next = first;
				first = newNode;
			} else {
				Node<T>* prev = first;
				for (int i = 1; i < pos; ++i) {
					prev = prev->next;
				}
				newNode->next = prev->next;
				prev->next = newNode;
			}
			n++;
		}

		
		void append(T elem) override {
			insert(n, elem);
		}
		
		
		void prepend(T elem) override {
			insert(0, elem);
		}

		
		T remove(int pos) override {
			if (pos < 0 || pos >= n) {
				throw out_of_range("Posición inválida");
			}

			Node<T>* toDelete;
			T removedValue;
			if (pos == 0) {
				toDelete = first;
				first = first->next;
			} else {
				Node<T>* prev = first;
				for (int i = 1; i < pos; ++i) {
					prev = prev->next;
				}
				toDelete = prev->next;
				prev->next = toDelete->next;
			}

			removedValue = toDelete->data;
			delete toDelete;
			n--;
			return removedValue;
		}

		T get(int pos) override {
			if (pos < 0 || pos >= n) {
				throw out_of_range("Posición inválida");
			}

			Node<T>* nodePtr = first;
			for (int i = 0; i < pos; ++i) {
				nodePtr = nodePtr->next;
			}
			return nodePtr->data;
		}

		
		int search(T elem) override {
			Node<T>* nodePtr = first;
			for (int i = 0; i < n; ++i) {
				if (nodePtr->data == elem) {
					return i;
				}
				nodePtr = nodePtr->next;
			}
			return -1;
		}

		bool empty() override {
			return n == 0;
		}


		int size() override {
			return n;
		}



		T operator[](int pos) {
    			if (pos < 0 || pos >= n) {
        			throw out_of_range("Posición inválida");
    			}

    			Node<T>* nodePtr = first;
    			for (int i = 0; i < pos; ++i) {
       				 nodePtr = nodePtr->next;  
			}
    			return nodePtr->data;
		}
	

		friend ostream& operator<<(ostream &out, const ListLinked<T> &list) {
			out << "[";
			Node<T>* nodePtr = list.first;
			while (nodePtr != nullptr) {
				out << nodePtr->data;
				if (nodePtr->next != nullptr) {
					out << ", ";
				}
				nodePtr = nodePtr->next;
			}
			out << "]";
			return out;
		}
};

