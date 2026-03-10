// вставка в начало и в конец односвязного списка, поиск максимального и последнего(реализация swap) 
#include <iostream>
#include <cmath>  

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    LinkedList(const LinkedList&) = delete;
    LinkedList operator =(const LinkedList&) = delete;

    void pushFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* current = head;

            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void print() const {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void swapMaxWithLast() {
        if (head == nullptr || head->next == nullptr) return;

        Node<T>* maxNode = head;
        Node<T>* prevMax = nullptr;
        Node<T>* current = head->next;
        Node<T>* prev = head;

        while (current != nullptr) {
            if (current->data > maxNode->data) {
                maxNode = current;
                prevMax = prev;
            }
            prev = current;
            current = current->next;
        }

        Node<T>* lastNode = prev;

        Node<T>* prevLast = nullptr;
        current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->next == lastNode) {
                prevLast = current;
                break;
            }
            current = current->next;
        }

        if (maxNode == lastNode) return;

        if (maxNode == head) {
            if (maxNode->next == lastNode) {
                head = lastNode;
                maxNode->next = lastNode->next;
                lastNode->next = maxNode;
            }
            else {
                head = maxNode->next;
                if (prevLast != nullptr) {
                    prevLast->next = maxNode;
                }
                maxNode->next = lastNode->next;
                lastNode->next = head;
                head = lastNode;
            }
        }
        else if (maxNode->next == lastNode) {
            if (prevMax != nullptr) {
                prevMax->next = lastNode;
            }
            maxNode->next = lastNode->next;
            lastNode->next = maxNode;
        }
        else {
            if (prevMax != nullptr)
                prevMax->next = lastNode;
            if (prevLast != nullptr)
                prevLast->next = maxNode;

            Node<T>* temp = maxNode->next;
            maxNode->next = lastNode->next;
            lastNode->next = temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getSize() const {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};

int main() {
    LinkedList<double> list;

    cout << "Enter real numbers. Enter 0 to finish" << endl;
    cout << "Use dot (.) as decimal separator" << endl;
    cout << "Example: 3.14 2.5 7.8 1.6 0" << endl;

    double value;
    while (true) {
        cout << "> ";
        cin >> value;

        if (cin.fail()) {
            cout << "Error! Please enter a number (e.g., 3.14): ";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (fabs(value) < 1e-10) {
            cout << "Input finished." << endl;
            break;
        }

        list.pushBack(value);
    }

    cout << "\nOriginal list (" << list.getSize() << " elements): ";
    list.print();

    list.swapMaxWithLast();

    cout << "After swap: ";
    list.print();

    return 0;
}
