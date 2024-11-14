#include "func.cpp"
#include <vector>
#include <queue>
#include <map>




Node *createNode(Flight data)
{
    Node *cur = new Node;
    cur->base = data;
    cur->left = cur->right = nullptr;
    return cur;
}

int compare (Flight a, Flight b)
{
    if (a.src < b.src) return 0;
    if (a.src > b.src) return 2;

    if (a.des < b.des) return 0;
    if (a.des > b.des) return 2;

    if (a.airliner < b.airliner) return 0;
    if (a.airliner > b.airliner) return 2;

    if (a.eco < b.eco) return 0;
    if (a.eco > b.eco) return 2;

    if (a.bus < b.bus) return 0;
    if (a.bus > b.bus) return 2;

    if (a.hours < b.hours) return 0;
    if (a.hours > b.hours) return 2;

    if (a.mins < b.mins) return 0;
    if (a.mins > b.mins) return 2;

    return 1;
}

void Insert(Node* &pRoot, Flight x)
{
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    int cmp = compare(x, pRoot->base);
    if (cmp == 0)
        Insert(pRoot->left, x);
    if (cmp == 2)
        Insert(pRoot->right, x);
}

Node* createTree(Flight a[], int n)
{
    Node* pRoot = nullptr;
    for (int i = 0; i < n; ++i)
        Insert(pRoot, a[i]);

    return pRoot;
}

void input(const string flightdata_filename, map <string, vector<Flight>> &adj)
{
    ifstream ifs;
    ifs.open(flightdata_filename);

    vector<Flight> v;
    string data;
    while (getline(ifs, data)){
        stringstream ss(data);
        Flight f = {"", "", "", 0, 0, 0, 0};
        string dumpData;
        getline(ss, dumpData, '\"');
        getline(ss, f.src, ',');
        getline(ss, f.des, '\"');

        getline(ss, dumpData, '\"');

        getline(ss, f.airliner, '\"');
        getline(ss, dumpData, '\"');

        ss >> f.bus;
        getline(ss, dumpData, ',');
        ss >> f.eco;
        getline(ss, dumpData, '\"');
        getline(ss, dumpData, '\"');


        ss >> f.hours;
        getline(ss, dumpData, ',');

        // truong hop khong co hours
        if (dumpData[1] != 'h'){
            f.mins = f.hours;
            f.hours = 0;
        }
        // truong hop co minute
        if (dumpData.back() != '}'){
            ss >> f.mins;
        }

        adj[f.src].push_back(f);

    }

    ifs.close();
}


int** generateMatrix(int m, int n)
{
    int **a;
    a = new int*[m];
    for (int i=0; i<m; ++i)  {
        a[i] = new int[n];
        for (int j = 0; j<n; ++j) {
            a[i][j] = i+j;
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\n";
    return a;
}

void matrix()
{
    int p = 5;
    int m=2;
    int n=3;

    int ***b = new int**[10];
    for (int k=0; k<p; ++k) {
        //b[k] = new int*[m];
        b[k] = generateMatrix(m, n);
    }
    cout << "=====\n";

    for (int k=0; k<p; ++k) {
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++)
                cout << b[k][i][j] << " ";
            cout << "\n";
        }
        cout << "---\n";
    }

}

void LRN(Node* root)
{
    if (root == nullptr)
        return;

    LRN(root->left);
    LRN(root->right);
    cout << root->base.src << "," << root->base.des  << "," << root->base.airliner << "," << root->base.eco << "," << root->base.bus << "," << root->base.hours << "," << root->base.mins << "\n";
}

Node* findMax(Node* pRoot)
{
    if (!pRoot->right) return pRoot;
    return findMax(pRoot->right);
}

void Remove(Node* &pRoot, Flight x)
{
    if (!pRoot) return;

    int cmp = compare(x, pRoot->base);
    if (cmp == 0)
        return Remove(pRoot->left, x);
    if (cmp == 2)
        return Remove(pRoot->right, x);

    if (!pRoot->left) {
        Node* tmp = pRoot;
        pRoot = pRoot->right;
        delete tmp;
        return;
    }
    if (!pRoot->right) {
        Node* tmp = pRoot;
        pRoot = pRoot->left;
        delete tmp;
        tmp = nullptr;
        return;
    }
    Node* preSuccesor = findMax(pRoot->left);
    pRoot->base = preSuccesor->base;
    Remove(pRoot->left, preSuccesor->base);
}

int Height(Node* pRoot)
{
    if (pRoot == nullptr) return 0;

    int left = Height(pRoot->left);
    int right = Height(pRoot->right);

    return max(left, right) + 1;
}

void printNodesAtLevelK(Node* root, int k) {
    if (root == nullptr)
        return;

    if (k == 0) {
    cout << root->base.src << "," << root->base.des  << "," << root->base.airliner << "," << root->base.eco << "," << root->base.bus << "," << root->base.hours << "," << root->base.mins << "\n";
    } else {
        printNodesAtLevelK(root->left, k - 1);
        printNodesAtLevelK(root->right, k - 1);
    }
}
void print_levellist(Node* root, string level_list) {
    stringstream ss(level_list);
    int k;
    char dot;
    while (ss >> k) {
        printNodesAtLevelK(root, k);
        ss >> dot; // Đọc dấu chấm ngăn cách giữa các giá trị k
    }
}

int flightTime(Node* node) {
    return node->base.hours * 60 + node->base.mins;
}

void findMaxFlightTime(Node* root, int currentLevel, int& maxTime) {
    if (root == nullptr)
        return;

    int time = flightTime(root);
    if (time > maxTime) {
        maxTime = time;
    }

    findMaxFlightTime(root->left, currentLevel + 1, maxTime);
    findMaxFlightTime(root->right, currentLevel + 1, maxTime);
}

void todo(const string flightdata_filename, string data_filename){
    Node* pRoot = nullptr;
    map <string, vector<Flight>> adjList;
    input("g1.v2.jl", adjList);
    //Remove(pRoot, f);
    //print_preorder(pRoot);
    cout << Height(pRoot);
}

void main_debug(){
    // Main for student
    todo("g1.v2.jl", "");
}
