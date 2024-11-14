#include "func.cpp"
#include <map>
#include <queue>
#include <stack>
#include <functional>
#define fi first
#define se second
//#define nullptr NULL
//cmt block: ctrl shift C, uncmt: ctrl shift x

void printFlight(Flight base)
{
    cout << base.src << "," << base.des  << "," << base.airliner << ","
    << base.eco << "," << base.bus << "," << base.hours << "," << base.mins << "\n";
}

struct Graph {
   map <string, int> name2id;
   vector<string> id2name;
   vector<vector<int>> adjMatrix;
   map <string, vector<int>> adjList;
   vector<Flight> base;
};
struct Node {
    Flight base;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
};
int compare (Flight a, Flight b) //For TREE
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

    return 1; //1: = // 2: a>b // 0: a<b
}

int flightTime(Flight base) {
    return base.hours * 60 + base.mins;
}
int toInt(string st)
{
    int ans = 0;
    for (int i=0; i< st.length(); ++i) {
        ans = ans*10 + (st[i] - '0');
    }
    return ans;
}


void input(const string flightdata_filename, vector <Flight> &flights)
{
    ifstream ifs;
    ifs.open(flightdata_filename);

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

        if (f.hours < 10) //dk cua f
            flights.push_back(f);
        //g.adjList[f.src].push_back(g.id2name.size() - 1);
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
int heightNode(Node* pRoot, Flight value) {
    if (pRoot == nullptr) return -1;
    if (compare(pRoot->base, value) == 1)
        return Height(pRoot);
    if (compare(pRoot->base, value) == 2)
        return heightNode(pRoot->left, value);
    else return heightNode(pRoot->right, value);

}
int height(Node* node) {
    return node ? node->height : 0;
}

//TREE TREE TREE
Node *createNode(Flight data)
{
    Node *cur = new Node;
    cur->base = data;
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
Node* insertAVL(Node* root, Flight data) {
    if (root == nullptr)
        return createNode(data);

    int cmp = compare(data, root->base);
    if (cmp == 0)
        root->left = insertAVL(root->left, data);
    else if (cmp == 2)
        root->right = insertAVL(root->right, data);
    else
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = balanceFactor(root);
    // Left Left Case
    if (balance > 1 && compare(data, root->left->base) == 0)
        return rotateRight(root);
    // Right Right Case
    if (balance < -1 && compare(data, root->right->base) == 2)
        return rotateLeft(root);
    // Left Right Case
    if (balance > 1 && compare(data, root->left->base) == 2) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && compare(data, root->right->base) == 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* createAVL(vector <Flight> flights)
{
    Node* pRoot = nullptr;
    for (Flight f : flights)
        pRoot = insertAVL(pRoot, f);
    return pRoot;
}
void RemoveAVL(Node* &pRoot, Flight x) {
    if (!pRoot) return;

    int cmp = compare(x, pRoot->base);
    if (cmp == 0)
        return RemoveAVL(pRoot->left, x);
    if (cmp == 2)
        return RemoveAVL(pRoot->right, x);
    if (!pRoot->left) {
        Node* tmp = pRoot;
        pRoot = pRoot->right;
        delete tmp;
        UpdateHeightandBalance(pRoot);
        return;
    }
    if (!pRoot->right) {
        Node* tmp = pRoot;
        pRoot = pRoot->left;
        delete tmp;
        tmp = nullptr;
        UpdateHeightandBalance(pRoot);
        return;
    }
    Node* successor = findLeftMost(pRoot->right);
    pRoot->base = successor->base;
    RemoveAVL(pRoot->right, successor->base);

    UpdateHeightandBalance(pRoot);
}
//Tree
void printNodesAtLevelK(Node* root, int k) {
    if (root == nullptr)
        return;

    if (k == 0) {
        printFlight(root->base);
    } else {
        printNodesAtLevelK(root->left, k - 1);
        printNodesAtLevelK(root->right, k - 1);
    }
}

void printNodesAtHeightK(Node* root, int k) {
    if (root == nullptr)
        return;
    if (root->height == k) {
        printFlight(root->base);
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
void findMaxFlightTime(Node* root, int currentLevel, int& maxTime) {
    if (root == nullptr)
        return;

    int time = flightTime(root->base);
    if (time > maxTime) {
        maxTime = time;
    }

    findMaxFlightTime(root->left, currentLevel + 1, maxTime);
    findMaxFlightTime(root->right, currentLevel + 1, maxTime);
}


//GRAPH GRAPH GRAPH
Graph createGraph (vector <Flight> flights)
{
    Graph g;
    for (Flight f : flights)
    {
        g.base.push_back(f);
        if (g.name2id.find(f.src) == g.name2id.end()) {
            g.name2id.insert({f.src, g.id2name.size()});
            g.id2name.push_back(f.src);
        }
        if (g.name2id.find(f.des) == g.name2id.end()) {
            g.name2id.insert({f.des, g.id2name.size()});
            g.id2name.push_back(f.des);
        }
    }

    int n = g.id2name.size();
    g.adjMatrix.resize(n, vector<int>(n, - 1));
    for (int i = 0; i < flights.size(); ++i) {
        Flight f = flights[i];
        int u = g.name2id[f.src];
        int v = g.name2id[f.des];
        g.adjMatrix[u][v] = i;
        g.adjMatrix[v][u] = i;
    }

    return g;
}
void dfs(int u, Graph g, vector <bool> &visited)
{
    visited[u] = 1;
    cout << g.id2name[u] << '\n';
    int n = g.id2name.size();
    for (int v = 0; v < n; ++v) {
        if (g.adjMatrix[u][v] != -1 && !visited[v]) {
            dfs(v, g, visited);
        }
    }
}
void bfs(int start, Graph g)
{
    int n = g.id2name.size();
    vector <bool> visited(n, 0);
    queue <int> q;

    q.push(start);
    visited[start] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << g.id2name[u] << '\n';

        for (int v = 0; v < n; ++v)
            if (g.adjMatrix[u][v] != -1 && !visited[v]) {
                q.push(v);
                visited[v] = 1;
            }
    }
}
vector <int> dijkstra (const Graph g, int source, vector <int> &backtrack)
{
    int n = g.id2name.size();
    vector <int> d (n, std::numeric_limits<int>::max());
    backtrack.assign(n, source);
    vector <bool> visited (n, 0);
    d[source] = 0;
    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || d[j] < d[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            int flightIndex = g.adjMatrix[u][v];
            if (flightIndex != -1) {
                const Flight& flight = g.base[flightIndex];
                int weight = flightTime(flight);
                if (!visited[v] && d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    backtrack[v] = u;
                }
            }
        }
    }
    return d;
}
vector <string> fromAtoB(Graph g, string a, string b, int &time)
{
    vector <int> backtrack;
    vector <int> dj = dijkstra(g, g.name2id[a], backtrack);
    stack <int> tracer;
    int u = g.name2id[b];
    time = dj[u];
    tracer.push(u);
    int v = backtrack[u];
    while (backtrack[u] != u) {
        tracer.push(backtrack[u]);
        u = backtrack[u];
    }
    vector <string> way;
    while (!tracer.empty()){
        way.push_back(g.id2name[tracer.top()]);
        tracer.pop();
    }
    return way;
}
int prim(const Graph& g) {
    int n = g.id2name.size();
    int total = 0;
    std::vector<bool> visited(n, 0);
    std::vector<int> weights(n, std::numeric_limits<int>::max()); // Stores weights

    weights[0] = 0;

    for (int v = 0; v < n; ++v) {
        int minWeight = std::numeric_limits<int>::max();
        int minWeightVertex = -1;

        for (int u = 0; u < n; ++u) {
            if (!visited[u] && weights[u] < minWeight) {
                minWeight = weights[u];
                minWeightVertex = u;
            }
        }

        if (minWeightVertex == -1) {
            break; // All vertices have been included in the MST
        }

        visited[minWeightVertex] = 1;
        total += minWeight;

        // Update weights of adjacent vertices
        for (int u = 0; u < n; ++u) {
            int flightIndex = g.adjMatrix[minWeightVertex][u];
            if (flightIndex != -1) {
                const Flight& flight = g.base[flightIndex];
                int weight = flight.hours * 60 + flight.mins;
                if (!visited[u] && weight < weights[u]) {
                    weights[u] = weight;
                }
            }
        }
    }

    return total;
}
void directA(Graph g, string country1)
{
    int n = g.id2name.size();
    cout << country1 << ": ";
    int u = g.name2id[country1];
    int cnt = 0;
    for (int v = 0; v<n; ++v)
    {
        int i = g.adjMatrix[u][v];
        if (i!=-1) {
            cout << g.id2name[v] << ", ";
            cnt++;
        }
        if (cnt == 10) break;
    }
    cout << endl;
}
vector <int> degree (Graph g)
{
    int n = g.id2name.size();
    vector <int> d (n, 0);
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<n; ++j)
            if (g.adjMatrix[i][j] != -1)
                d[i]++;
    return d;
}

void evenDegree(Graph g)
{
    int n = g.id2name.size();
    vector <int> d = degree(g);
    int even = 0, maxEven = 0;
    for (int i = 0; i<n; ++i) {
        if (d[i]%2 == 0) {
            even++;
            maxEven = max(maxEven, d[i]);
        }
    }
    cout << even << " even vertices, the highest: ";
    for (int i = 0; i<n; ++i)
        if (d[i] == maxEven)
            cout << g.id2name[i] << ", ";
}

void devArea(Graph g, string country1, string country2)
{
    int n = g.id2name.size();
    int c1 = g.name2id[country1], c2 = g.name2id[country2];
    if (g.adjMatrix[c1][c2] == -1){
        cout << "0 quad \n";
        return;
    }
    int quad = 0;
    vector <pair <int, int>> c34;
    for (int i = 0; i < n-1; ++i) {
        if (i == c1 || i == c2) continue;
        if (g.adjMatrix[c1][i] == -1 || g.adjMatrix[c2][i] == -1) continue;
        for (int j = i+1; j < n; ++j) {
            if (j == c1 || j == c2) continue;
            if (g.adjMatrix[c1][j] != -1 && g.adjMatrix[c2][j] != -1 && g.adjMatrix[i][j] != -1) {
                quad++;
                if (quad<=3)
                    c34.push_back({i, j});
            }
        }
    }
    cout << quad << " quad.\n";
    for (int i = 0; i<3; ++i)
        cout << country1 << ", " << country2 << ", " << g.id2name[c34[i].fi] << ", " << g.id2name[c34[i].se] << endl;
}

void todo(string flightdata_filename, string data_filename){
    // TODO
    vector <Flight> flights;
    vector <int> dj;
    vector <int> backtrack;
    input(flightdata_filename, flights);
    Graph g = createGraph(flights);

    ifstream ifs(data_filename);
    string data;
    getline (ifs, data);
    stringstream ss(data);
    string country1, country2;
    getline(ss, country1, ',');
    getline(ss, country2, ' ');
    directA(g, country1);
    cout << "======\n";
    evenDegree(g);
    cout << "=====\n";
    devArea(g, country1, country2);
    ifs.close();
}



void main_debug(){
    // Main for student
    todo("g1.v2.jl", "data.txt");

}
