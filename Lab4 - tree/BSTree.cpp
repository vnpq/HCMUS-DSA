#include <iostream>
#include <vector>

using namespace std;

struct NODE{
    int key;
    NODE* left;
    NODE* right;
};

NODE* createNode(int data)
{
    return new NODE {data, nullptr, nullptr};
    //return tmp;
}

void Insert(NODE* &pRoot, int x)
{
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    if (pRoot->key > x)
        Insert(pRoot->left, x);
    if (pRoot->key < x)
        Insert(pRoot->right, x);
}

void NLR(NODE* pRoot)
{
    if (pRoot == nullptr)
        return;
    cout << pRoot->key << " ";
    NLR(pRoot->left);
    NLR(pRoot->right);
}

void LNR(NODE* pRoot)
{
    if (pRoot == nullptr)
        return;
    LNR(pRoot->left);
    cout << pRoot->key << " ";
    LNR(pRoot->right);
}

void LRN(NODE* pRoot)
{
    if (pRoot == nullptr) return;
    }
    LRN(pRoot->left);
    LRN(pRoot->right);
    cout << pRoot->key << " ";
}

int Height(NODE* pRoot)
{
    if (pRoot == nullptr) return 0;

    int left = Height(pRoot->left);
    int right = Height(pRoot->right);

    return max(left, right) + 1;
}

int countNode(NODE* pRoot)
{
    if (pRoot == nullptr) return 0;

    int left = countNode(pRoot->left);
    int right = countNode(pRoot->right);

    return left + right + 1;
}

int sumNode(NODE* pRoot)
{
    if (pRoot == nullptr) return 0;

    int left = sumNode(pRoot->left);
    int right = sumNode(pRoot->right);

    return left + right + pRoot->key;
}

NODE* Search(NODE* pRoot, int x)
{
    if (pRoot == nullptr) return pRoot;

    if (pRoot->key > x)
        return Search(pRoot->left, x);
    if (pRoot->key < x)
        return Search(pRoot->right, x);

    return pRoot;
}



NODE* createTree(int a[], int n)
{
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; ++i)
        Insert(pRoot, a[i]);

    return pRoot;
}

int heightNode(NODE* pRoot, int value)
{
    if (pRoot == nullptr) return -1;
    if (pRoot->key == value)
        return Height(pRoot);
    if (pRoot->key > value)
        return heightNode(pRoot->left, value);
    else return heightNode(pRoot->right, value);

}

NODE* findMax(NODE* pRoot)
{
    if (!pRoot->right) return pRoot;
    return findMax(pRoot->right);
}

void Remove(NODE* &pRoot, int x)
{
    if (!pRoot) return;
    if (pRoot->key > x)
        return Remove(pRoot->left, x);
    if (pRoot->key < x)
        return Remove(pRoot->right, x);

    if (!pRoot->left) {
        NODE* tmp = pRoot;
        pRoot = pRoot->right;
        delete tmp;
        return;
    }
    if (!pRoot->right) {
        NODE* tmp = pRoot;
        pRoot = pRoot->left;
        delete tmp;
        tmp = nullptr;
        return;
    }
    NODE* preSuccesor = findMax(pRoot->left);
    pRoot->key = preSuccesor->key;
    Remove(pRoot->left, preSuccesor->key);
}

int Level(NODE* pRoot, NODE* p)
{
    if (pRoot == p) return 1;
    if (pRoot->key > p->key)
        return 1 + Level(pRoot->left, p);
    return 1 + Level(pRoot->right, p);
}

int countLeaf(NODE* pRoot)
{
    if (!pRoot) return 0;
    if (!pRoot->left && !pRoot->right) return 1;

    int left = countLeaf(pRoot->left);
    int right = countLeaf(pRoot->right);
    return left + right;
}

int countLess(NODE* pRoot, int x)
{
    if (!pRoot || pRoot->key > x) return 0;
    return countLess(pRoot->left, x) + countLess(pRoot->right, x) + (pRoot->key < x);
}

int countGreater(NODE* pRoot, int x)
{
    if (!pRoot || pRoot->key < x) return 0;
    return countLess(pRoot->left, x) + countLess(pRoot->right, x) + (pRoot->key > x);
}

int main()
{
    int a[6] = {6,4,9,3,11};
    NODE* pRoot = createTree(a, 5);
    NLR(pRoot); cout << "\n";
    Remove(pRoot, 6);
    NLR(pRoot);
}


