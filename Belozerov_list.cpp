// вставка в начало и конец односв€зного списка, перестановка максимального с последним элементом

#include <iostream>
#include <stdexcept>


using namespace std;

template <typename T>
struct Node {
	T key;
	Node<T>* pNext;

	Node(const T& value): key(value), pNext(nullptr){}
};



template  <typename T> 
class LinkedList {
private:
	Node<T>* head;

public:
	LinkedList(): head(nullptr)
	{}

	~LinkedList() {
		//clear();
	}

	LinkedList(const LinkedList&) = delete;
	LinkedList operator =(const LinkedList&) = delete;

	void push_front(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->pNext = head;
		head = newNode;
	}

	void pushback(const T& value) {
		Node<T>* newNode = new Node<T>(value);

		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<T>* current = head;

			while (current->pNext != nullptr) {
				current = current->pNext;
			}
			current->pNext = newNode;
		}
	}

	void print() const {
		if (head == nullptr) {
			cout << "—писок пуст\n";
			return;
		}

		Node<T>* current = head;
		while (current != nullptr) {
			cout << current->key;

			if (current->pNext != nullptr) {
				cout << " -> ";
			}
			current = current->pNext;
		}
		cout << std::endl;
	}

	void swapMaxWithLast() {
		if (head == nullptr || head->pNext == nullptr) return;

		Node<T>* maxNode = head;
		Node<T>* prevMax = nullptr;
		Node<T>* current = head->pNext;
		Node<T>* prev = head;

		while (current != nullptr) {
			if (current->key > maxNode->key) {
				maxNode = current;
				prevMax = prev;
			}
			prev = current;
			current = current->pNext;
		}

		Node<T>* lastNode = prev;
		Node<T>* prevlast = nullptr;

		current = head;
		while (current != nullptr && current->pNext != lastNode) {
			current = current->pNext;
		}
		prevlast = current;
		if (maxNode == lastNode) return;

		if (maxNode == head) {
			head = maxNode->pNext;
			maxNode->pNext = lastNode->pNext;
			if (prevlast != nullptr) {
				prevlast->pNext = maxNode;
				prevlast->pNext = head;
				head = lastNode;
			}
			else if (maxNode->pNext = lastNode) {
				prevMax->pNext = lastNode;
				maxNode->pNext = lastNode->pNext;
				lastNode->pNext = maxNode;
			}
			else {
				if (prevMax != nullptr)
					prevMax->pNext = lastNode;
				if (prevlast != nullptr)
					prevlast->pNext = maxNode;

				Node<T>* temp = maxNode->pNext;
				maxNode->pNext = lastNode->pNext;
					lastNode->pNext = temp;
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "Ru");
	LinkedList<int> hh;
	
	cout << "¬ведите числа" << endl;

	int x;
	while (true) {
		cin >> x;
		if (x == 0) break;
		hh.pushback(x);
	}

	hh.print();

	hh.swapMaxWithLast();

	hh.print();
}