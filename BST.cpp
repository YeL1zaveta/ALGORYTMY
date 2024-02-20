#include <iostream>
#include< string > 
#include <chrono>
#include <ctime>
#include <algorithm> 
using namespace std;

class MojObiekt {
private:
    int INT;
    char CHAR;

public:
    MojObiekt() : INT(rand() % 1000), CHAR('a' + (rand() % 26)) {}
    int GetINT() const {
        return INT;
    }
    char GetCHAR() const {
        return CHAR;
    }
    // Dodanie operatora "<" do porównywania obiektów MojObiekt
    bool operator<(const MojObiekt& other) const {
        if (INT < other.INT) {
            return true;
        }
        else if (INT == other.INT) {
            return CHAR < other.CHAR;
        }
        else {
            return false;
        }
    }
    // Dodanie operatora "<" do porównywania obiektów MojObiekt
    bool operator>(const MojObiekt& other) const {
        if (INT > other.INT) {
            return true;
        }
        else if (INT == other.INT) {
            return CHAR > other.CHAR;
        }
        else {
            return false;
        }
    }
    std::string to_string() const {
        return  std::to_string(INT) + CHAR;
    }

};

template <typename T>
class Node {
public:
    T data;
    Node* parent;
    Node* left;
    Node* right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}

};

template <typename T>
class BST {
private:
    int size;
    Node<T>* root;

public:
    BST() : root(nullptr), size(0) {}

    Node<T>* Getroot() {
        return root;
    }
    int Getsize() {
        return size;
    }

    void Setarr(Node<T>* r) {
        root = r;
    }
    void Setsize(int si) {
        size = si;
    }
    Node<T>* AddNode(Node<T>* node, T data, bool (*comparator)(const T&, const T&)) {
        if (node == nullptr) {
            return new Node<T>(data);
        }

        if (comparator(data, node->data)) {
            node->left = AddNode(node->left, data, comparator);
        }
        else {
            node->right = AddNode(node->right, data, comparator);
        }

        return node;
    }

    void Add(const T& data, bool (*comparator)(const T&, const T&)) {
        root = AddNode(root, data, comparator);
        size++;
    }
    int height_of_tree(Node<T>* node) {
        if (node == nullptr)
            return 0;
        else {
            int height_left = height_of_tree(node->left);
            int height_right = height_of_tree(node->right);
            return std::max(height_left, height_right) + 1;
        }
    }
    string Print(Node<T>* node) {
        if (node == nullptr) {
            return "";
        }
        string result = "(" + to_string(node->data->GetINT()) + ": [p: ";
        result += (node->parent ? to_string(node->parent->data->GetINT()) : "NULL") + ", l: ";
        result += (node->left ? to_string(node->left->data->GetINT()) : "NULL") + ", r: ";
        result += (node->right ? to_string(node->right->data->GetINT()) : "NULL") + "], data: (";
        result += to_string(node->data->GetINT()) + ", " + node->data->GetCHAR() + ")), ";

        string leftString = Print(node->left);
        string rightString = Print(node->right);


        result += leftString;
        if (!leftString.empty() && !rightString.empty()) {
            result += ", ";
        }
        result += rightString;

        return result;
    }

    // Przejście drzewa binarnego w kolejności inorder
    void Inorder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        Inorder(node->left);
        cout << "(" << node->data->GetINT() << ", " << node->data->GetCHAR() << ") ";
        Inorder(node->right);
    }

    // Przejście drzewa binarnego w kolejności preorder
    void Preorder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        cout << "(" << node->data->GetINT() << ", " << node->data->GetCHAR() << ") ";
        Preorder(node->left);
        Preorder(node->right);
    }
};
bool (*customComparator)(MojObiekt* const&, MojObiekt* const&) = [](MojObiekt* const& left, MojObiekt* const& right) {
    return left->GetINT() < right->GetINT();
};

int main() {
    BST<MojObiekt*>* bst = new BST<MojObiekt*>();
    cout << "Size na poczatku:" << bst->Getsize() << endl;
    int Max_element = 10000;
    clock_t start_time = clock();
    // Dodawanie do drzewa
    for (int i = 0; i < Max_element; i++) {
        MojObiekt* obj = new MojObiekt();
        bst->Add(obj, customComparator);

    }
    clock_t end_time = clock();
    cout << bst->Print(bst->Getroot()) << endl;
    cout << "Size po stworzeniu drzewa:" << bst->Getsize() << endl;
    double elapsed_time = static_cast<double>(end_time - start_time);
    cout << "Dodano " << Max_element << " obiektów do BST w czasie " << elapsed_time << " ms." << endl;

    cout << "Inorder traversal: ";
    bst->Inorder(bst->Getroot());
    cout << endl;
    cout << "Preorder traversal: ";
    bst->Preorder(bst->Getroot());
    cout << endl;
    int wysokosc = bst->height_of_tree(bst->Getroot());

    cout << "Wysokosc drzewa :" << wysokosc << endl;
    cout << "Wysokosc drzewa / log2(n):" << wysokosc / log2(bst->Getsize()) << endl;

    delete bst;

    return 0;
}
