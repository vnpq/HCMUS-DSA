#include "func.cpp"
#include <map>
#include <queue>
#include <stack>
#include <functional>
#define fi first
#define se second
//#define nullptr NULL
//cmt block: ctrl shift C, uncmt: ctrl shift x

void printA(vector <char> A)
{
    cout << '{';
    char aa = A.back();
    A.erase(A.begin() + A.size()-1);
    for (char a : A) cout << a << ", ";
    A.push_back(aa);
    cout << aa << "}\n";
}

struct Node {
    vector <char> A;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
};
int vowels (vector <char> A)
{
    int v = 0;
    for (char a : A) {
        if (a == 'a' || a == 'A' || a == 'o' || a == 'O' || a == 'e' || a == 'E')
            v++;
        else
            if (a == 'u' || a == 'U' || a == 'i' || a == 'I')
                v++;
    }

    return v;
}
int maxFrequen(vector <char> A)
{
    map <char, int> f;
    for (char a : A)
        f[a]++;
    int maxF = 0;
    for (char a : A)
        maxF = max(maxF, f[a]);
    return maxF;
}
int compare (vector <char> A, vector <char> B)
{
    int vA = vowels(A), vB = vowels(B);
    int fA = maxFrequen(A), fB = maxFrequen(B);
    if (vA > vB) return 2;
    if (vA < vB) return 0;

    if (fA > fB) return 2;
    if (fA < fB) return 0;

    return 1;
}

int toInt(string st)
{
    int ans = 0;
    for (int i=0; i< st.length(); ++i) {
        ans = ans*10 + (st[i] - '0');
    }
    return ans;
}
void Input(const string filename, vector <vector <char>> &ans)
{
    ifstream ifs(filename);
    string data;
    getline(ifs, data);
    while (getline(ifs, data))
    {
        vector <char> A;
        for (char a : data) {
            if (a == '/') break;
            if (a == ' ') continue;
            A.push_back(a);
        }
        ans.push_back(A);
    }

    ifs.close();
}
int Height(Node* pRoot)
{
    if (pRoot == nullptr) return 0;

    int left = Height(pRoot->left);
    int right = Height(pRoot->right);

    return max(left, right) + 1;
}
int height(Node* node) {
    return node ? node->height : 0;
}

//TREE TREE TREE
Node *createNode(vector <char> data)
{
    Node *cur = new Node;
    cur->A = data;
    cur->left = cur->right = nullptr;
    cur->height = 1;
    return cur;
}
Node* findLeftMost(Node* root){
    while (root->left)
        root = root->left;
    return root;
}
Node* findRightMost(Node* root){
    while (root->right)
        root = root->right;
    return root;
}
int balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}
void UpdateHeightandBalance(Node* pRoot) {
    if (!pRoot) return;
    pRoot->height = 1 + std::max(height(pRoot->left), height(pRoot->right));

    int balance = balanceFactor(pRoot);

    if (balance > 1 && balanceFactor(pRoot->left) >= 0)
        pRoot = rotateRight(pRoot);

    if (balance > 1 && balanceFactor(pRoot->left) < 0) {
        pRoot->left = rotateLeft(pRoot->left);
        pRoot = rotateRight(pRoot);
    }

    if (balance < -1 && balanceFactor(pRoot->right) <= 0)
        pRoot = rotateLeft(pRoot);

    if (balance < -1 && balanceFactor(pRoot->right) > 0) {
        pRoot->right = rotateRight(pRoot->right);
        pRoot = rotateLeft(pRoot);
    }
}
Node* insertAVL(Node* root, vector <char> data) {
    if (root == nullptr)
        return createNode(data);

    int cmp = compare(data, root->A);
    if (cmp == 0)
        root->left = insertAVL(root->left, data);
    else if (cmp == 2)
        root->right = insertAVL(root->right, data);
    else
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = balanceFactor(root);
    // Left Left Case
    if (balance > 1 && compare(data, root->left->A) == 0)
        return rotateRight(root);
    // Right Right Case
    if (balance < -1 && compare(data, root->right->A) == 2)
        return rotateLeft(root);
    // Left Right Case
    if (balance > 1 && compare(data, root->left->A) == 2) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && compare(data, root->right->A) == 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* createAVL(vector <vector <char>> lines)
{
    Node* pRoot = nullptr;
    for (vector <char> line : lines)
        pRoot = insertAVL(pRoot, line);
    return pRoot;
}
void RemoveAVL(Node* &pRoot, vector <char> x) {
    if (!pRoot) return;
    int cmp = compare(x, pRoot->A);
    if (cmp == 0)
        return RemoveAVL(pRoot->left, x);
    if (cmp == 2)
        return RemoveAVL(pRoot->right, x);
    //printA(x);
    if (!pRoot->left) {
        Node* tmp = pRoot->right;
        pRoot->A.clear();
        delete pRoot;
        pRoot = nullptr;
        pRoot = tmp;
        UpdateHeightandBalance(pRoot);
        return;
    }
    if (!pRoot->right) {
        Node* tmp = pRoot->left;
        pRoot->A.clear();
        delete pRoot;
        pRoot = nullptr;
        pRoot = tmp;
        UpdateHeightandBalance(pRoot);
        return;
    }
    Node* successor = findLeftMost(pRoot->right);
    pRoot->A.clear();
    pRoot->A = successor->A;
    RemoveAVL(pRoot->right, successor->A);

    UpdateHeightandBalance(pRoot);
}
//Tree
void printNodesAtLevelK(Node* root, int k) {
    if (root == nullptr)
        return;

    if (k == 0) {
        printA(root->A);
    } else {
        printNodesAtLevelK(root->left, k - 1);
        printNodesAtLevelK(root->right, k - 1);
    }
}

void printNodesAtHeightK(Node* root, int k) {
    if (root == nullptr)
        return;
    if (root->height == k) {
        printA(root->A);
    }
    printNodesAtHeightK(root->left, k);
    printNodesAtHeightK(root->right, k);
}
void print_levellist(Node* root, string level_list) {
    stringstream ss(level_list);
    int k;
    char dot;
    while (ss >> k) {
        printNodesAtLevelK(root, k);
        ss >> dot;
    }

}
void NLR(Node* pRoot)
{
    if (pRoot == nullptr)
        return;
    printA(pRoot->A);
    NLR(pRoot->left);
    NLR(pRoot->right);
}

void LNR(Node* pRoot)
{
    if (pRoot == nullptr)
        return;
    LNR(pRoot->left);
    //cout << vowels(pRoot->A) << " ";
    printA(pRoot->A);
    LNR(pRoot->right);
}

void LRN(Node* pRoot)
{
    if (pRoot == nullptr) return;
    LRN(pRoot->left);
    LRN(pRoot->right);
    printA(pRoot->A);
}

void Vowelis2(Node* root, Node* pRoot)
{
    if (!root) return;
    //cout << vowels(root->A);
    while (root && vowels(root->A) == 2){
        //printA(root->A);
        RemoveAVL(pRoot, root->A);
        if (vowels(root->A) != 2) break;
    }
    if (!root) return;
    Vowelis2(root->left, pRoot);
    Vowelis2(root->right, pRoot);

}
void todo(string flightdata_filename, string data_filename){
    vector <vector <char>> As;
    Input(data_filename, As);
    Node* pRoot = createAVL(As);
    cout << height(pRoot);
    LNR(pRoot);
    cout << "=====\n";
    Vowelis2(pRoot, pRoot);
    LNR(pRoot);

}

void main_debug(){
    // Main for student
    todo("g1.v2.jl", "data.txt");

}

