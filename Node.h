#include <iostream>

using namespace std;

template <typename T>
class Node {
	public:
        	T data;
       	 	Node<T>* next;

        	// Constructor
        	Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}

        	// Sobrecarga del operador <<
        	friend ostream& operator<<(ostream &out, const Node<T> &node) {
            		out << node.data;
            		return out;
        	}
};

