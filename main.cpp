#include "mysplay.h"

int main()
{
    node *root = nullptr;
    root = insert(root, 3, 3);
    root = insert(root, 1, 2);
    root = insert(root, 1, 1);
    root = insert(root, 4, 4);
    root = insert(root, 5, 5);
    root = insert(root, 7, 7);
    root = insert(root, 6, 6);
    root = insert(root, 8, 8);
    root = insert(root, 10, 10);
    root = insert(root, 9, 9);
    preOrder(root);
    cout << endl;
    root = del(root, 3); // deletes 3
    root = del(root, 4); // deletes 5
    root = del(root, 8); // deletes 10
    preOrder(root);
    return 0;
}
