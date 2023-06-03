#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
using namespace std;






struct Node
{
    int value;
    Node* left;
    Node* right;
};




//**********************CREATE A BST**********************
Node* createBT(int value) {
    Node* root = new Node;
    root->left = NULL;
    root->right = NULL;
    root->value = value;
    return root;
}

//**********************GET MIN ELEMENT**********************
Node* getMinBT(Node* root) {
    while (root->left)
        root = root->left;
    return root;
}

//**********************GET MAX ELEMENT**********************
Node* getMaxBT(Node* root) {
    while (root->right)
        root = root->right;
    return root;
}



// Вывод бинарного дерева в указанный ostream
void printBT(Node* root, std::ostream& os, const std::string& rpf = "", const std::string& mpf = "", const std::string& lpf = "") {
    if (root != NULL) {
        if (root->right)
            printBT(root->right, os, rpf + "   ", rpf + ".-->", rpf + "|  ");
        os << mpf << root->value << std::endl;
        if (root->left)
            printBT(root->left, os, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

//**********************FIND NODE**********************
Node* searchBT(int value, Node* root) {
    if (root != nullptr)
    {
        if (value == root->value)
            return root;
        if (value < root->value)
            return searchBT(value, root->left);
        else
            return searchBT(value, root->right);
    }
    else return NULL;
}

//**********************DELETE NODE**********************
Node* deleteBT(int value, Node* root) {
    if (root == NULL)
        return NULL;

    if (value < root->value)
        root->left = deleteBT(value, root->left);
    else if (value > root->value)
        root->right = deleteBT(value, root->right);
    else {
        if (root->left == NULL && root->right == NULL)
            root = NULL;
        else if (root->left == NULL || root->right == NULL)
            root = root->left ? root->left : root->right;
        else {
            Node* minnode = getMinBT(root->right);
            root->value = minnode->value;
            root->right = deleteBT(minnode->value, root->right);
        }
    }

    return root;
}



// Добавить значение в бинарное дерево (root != null)
void insertBT(int value, Node* root) {
    if (!root) return;
    if (value < root->value)
    {
        if (root->left != NULL)
            insertBT(value, root->left);
        else {
            root->left = new Node;
            root->left->value = value;
            root->left->left = NULL;
            root->left->right = NULL;
        }
    }
    else if (value >= root->value) {
        if (root->right != NULL)
            insertBT(value, root->right);
        else {
            root->right = new Node;
            root->right->value = value;
            root->right->left = NULL;
            root->right->right = NULL;
        }
    }
}

// Добавить значение в бинарное дерево
void addBT(int value, Node*& root) {
    if (root == NULL)
        root = createBT(value);
    else
        insertBT(value, root);
}

//**********************DESTROY BST**********************
void destroyBT(Node* root) {
    if (root != NULL) {
        destroyBT(root->left);
        destroyBT(root->right);
        delete root;
    }
}

//**********************STRAIGHT TRAVERSAL - (прямой обход)**********************
void preOrderTravers(Node* root) {
    if (root) {
        std::cout << root->value << ' ';
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

//**********************REVERSE TRAVERSAL - (обратный обход)**********************
void postOrderTravers(Node* root) {
    if (root) {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        std::cout << root->value << ' ';
    }
}

//**********************SYMMETRICAL TRAVERSAL - (симметричный обход)**********************
void inOrderTravers(Node* root) {
    if (root) {
        inOrderTravers(root->left);
        std::cout << root->value << ' ';
        inOrderTravers(root->right);
    }
}


void Tasks() {
    int n;
    cout << "ВВедите количество заданий : ";
    cin >> n;
    ofstream ofs_task("input_tasks.txt");
    ofstream ofs_ans("output_ans.txt");
    ofstream ofs_key("output_key.txt");
    ofs_task << "\t\t\t\t\tCreated tasks.\n";
    for (int i = 1; i <= n; i++) {
        ofs_task << "#" << i << ".\n";
        ofs_ans << "Answers to " << "#" << i << ".\n";
        ofs_key << "#" << i << ".\n";
        ofs_task << i << ".1" << " Creating a BST with values:";
        Node* bt = NULL;
        int numToDelete = rand() % 200 - 99;
        for (int i = 0; i < 10; i++) {
            int x = rand() % 200 - 99;
            addBT(x, bt);
            if (rand() % 10 > 6)
                numToDelete = x;
            ofs_task << ' ' << x;
        }
        ofs_task << '\n';
        ofs_ans << i << ".1" << " Created binary tree: \n";
        printBT(bt, ofs_ans);
        printBT(bt, ofs_key);

        int y = rand() % 200 - 99;
        ofs_task << i <<".2" << " Insert " << y << " into BST\n";
        addBT(y, bt);
        ofs_ans << "\n" << i <<".2" << " Binary tree after " << y << " insertion\n";
        printBT(bt, ofs_ans);
        ofs_key << "\n";
        printBT(bt, ofs_key);

        ofs_task << i << ".3" << " Delete " << numToDelete << " from BST\n";
        deleteBT(numToDelete, bt);
        ofs_ans << "\n" << i << ".3" << " Binary tree after " << numToDelete << " deletion\n";
        printBT(bt, ofs_ans);
        ofs_key << "\n";
        printBT(bt, ofs_key);


        ofs_ans << "\n------------------------------------------------------------------------------------\n\n";
        ofs_task << "\n\n";
        ofs_key << "\n------------------------------------------------------------------------------------\n";
        destroyBT(bt);
    }
}



int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    Node* bt = NULL;
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "(0) - Exit \n"
            "(1) - Create Binary search Tree\n"
            "(2) - Print Binary search Tree\n"
            "(3) - Insert element\n"
            "(4) - Delete element\n"
            "(5) - Find element\n"
            "(6) - BST traversal\n"
            "(7) - Task\n\n";
        int choice;
        cout << "Action >> ";
        cin >> choice;
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            system("cls");
            cout <<
                "\t\t\t\tCREATING A BINARY SEARCH TREE.\n"
                "Choose how to create:\n"
                "1. With random values\n"
                "2. With manual values\n"
                "3. From the file\n\n";
            int choice;
            cout << "Action >> ";
            cin >> choice;
            cout << endl;
            switch (choice) {
            case 1: {
                destroyBT(bt);
                bt = NULL;
                int n;
                cout << "Enter the number of elements: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    int r = rand() % 200 - 99;
                    addBT(r, bt);
                }
                break;
            }
            case 2: {
                destroyBT(bt);
                bt = NULL;
                cout << "Enter value (To stop enter symbol \"x\").\n";
                int val;
                while (true) {
                    cin >> val;
                    if (cin.fail())
                        break;
                    addBT(val, bt);
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case 3: {
                destroyBT(bt);
                bt = NULL;

                ifstream ifs("bt.txt");
                if (ifs) {
                    int N;
                    ifs >> N;
                    cout << "There are " << N << " elements in the file.\n\n";
                    int n;
                    cout << "Choose how many elements to read from the file: ";
                    cin >> n;
                    cout << endl;
                    for (int i = 0; i < n && !ifs.eof(); i++) {
                        int inp;
                        ifs >> inp;
                        addBT(inp, bt);
                    }
                    ifs.close();
                }
                break;
            }
            }
            break;
        case 2:
            system("cls");
            cout <<"\t\t\t\tBINARY TREE: \n\n";
            printBT(bt, cout);
            cout << endl;
            break;
        case 3: {            
            system("cls");
            cout << "\t\t\t\tINSERT AN ELEMENT.\n\n";
            int n;
            cout << "Input a number to insert: ";
            cin >> n;
            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            addBT(n, bt);
            auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto result = end - start;
            cout << endl;
            cout << setw(32) << setfill('-') << "Insertion Time" << setw(32) << setfill('-') << "\n";
            cout << "Reslut\t" << result << " nanoseconds." << endl;
            cout << endl << setw(64) << setfill('-') << "\n\n";
            break;
        }
        case 4: {
            system("cls");
            cout << "\t\t\t\tREMOVING AN ELEMENT.\n\n";
            int n;
            cout << "Input a number to delete: ";
            cin >> n;
            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            deleteBT(n, bt);
            auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto result = end - start;
            cout << endl;
            cout << setw(32) << setfill('-') << "Deletion Time" << setw(32) << setfill('-') << "\n";
            cout << "Result\t" << result << " nanoseconds." << endl;
            cout << endl << setw(64) << setfill('-') << "\n\n";
            break;
        }
        case 5: {
            system("cls");
            cout << "\t\t\t\tELEMENT SEARCH.\n\n";
            int n;
            cout << "Input a number to search: ";
            cin >> n;
            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            Node* node = searchBT(n, bt);
            auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto result = end - start;
            if (node != NULL) {
                cout << endl;
                cout << setw(32) << setfill('-') << "Search Time" << setw(32) << setfill('-') << "\n";
                cout << "Element found\n" << "Result\t" << result << " nanoseconds." << endl;
                cout << endl << setw(64) << setfill('-') << "\n\n";
            }
            else {
                cout << endl;
                cout << setw(32) << setfill('-') << "Search Time" << setw(32) << setfill('-') << "\n";
                cout << "Element not found\n" << "Result\t" << result << " nanoseconds." << endl;
                cout << endl << setw(64) << setfill('-') << "\n\n";
            }
            break;
        }
        case 6: {
            system("cls");
            cout <<
                "Choose how to traversal:\n"
                "1. Straight\n"
                "2. Reverse\n"
                "3. Symmetrical\n\n";

            int choice;
            cout << "Action >> ";
            cin >> choice;
            cout << endl;
            switch (choice) {
            case 1:
                preOrderTravers(bt);
                cout << endl;
                break;
            case 2:
                postOrderTravers(bt);
                cout << endl;
                break;
            case 3:
                inOrderTravers(bt);
                cout << endl;
                break;
            }
            break;
        }
        case 7:
            Tasks();
            break;
        default:
            cout << "\nERROR" << endl;
            break;
        }
        system("pause");
    }
}