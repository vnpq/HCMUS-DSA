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
struct Node {
    vector <int> A;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
};
struct Graph {
   map <string, int> name2id;
   vector<string> id2name;
   vector<vector<int>> adjMatrix;
   vector<Flight> base;
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

bool vowel(Flight f)
{
    int cnt = 0;
    for (char a: f.src) {
        if (a == 'a' || a == 'A' || a == 'o' || a == 'O' || a == 'e' || a == 'E')
            cnt++;
        else
            if (a == 'u' || a == 'U' || a == 'i' || a == 'I')
                cnt++;
    }
    for (char a : f.des) {
        if (a == 'a' || a == 'A' || a == 'o' || a == 'O' || a == 'e' || a == 'E')
            cnt++;
        else
            if (a == 'u' || a == 'U' || a == 'i' || a == 'I')
                cnt++;
    }
    if (cnt>=2) return 1;
    return 0;
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
        //printFlight(f);
        if (vowel(f)) //dk cua f
            flights.push_back(f);
        //g.adjList[f.src].push_back(g.id2name.size() - 1);
    }

    ifs.close();
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

void CPDegree(Graph g)
{
    int n = g.id2name.size();
    vector <int> d = degree(g);
    int CP = 0, maxCP = 0;
    for (int i = 0; i<n; ++i) {
        int k = (int)sqrt(d[i]);
        if (k*k == d[i]) {
            CP++;
            maxCP = max(maxCP, d[i]);
        }
    }
    cout << CP << " perfect square vertices, the highest: ";
    for (int i = 0; i<n; ++i)
        if (d[i] == maxCP)
            cout << g.id2name[i] << ", ";
}

bool checkDev(Graph g, int a, int b)
{
    //cout << g.id2name[a] << g.id2name[b] << printFlight(g.base[g.adjMatrix[a][b]]) << endl;
    if (g.adjMatrix[a][b] != -1) return 1;

    int n = g.id2name.size();
    for (int i = 0; i<n; ++i)
        if (g.adjMatrix[a][i] != -1 && g.adjMatrix[b][i] != -1) return 1;
    return 0;
}

void devArea(Graph g, vector <string> country)
{
    int n = country.size();
    vector <vector <int>> dev(n);
    for (int i = 0; i<n; ++i) {
        dev[i].push_back(i);
        for (int j = 0; j<n; ++j) {
            if (i == j) continue;
            int b = g.name2id[country[j]];
            bool inDev = 1;
            for (int k : dev[i]) {
                int a = g.name2id[country[k]];
                if (!checkDev(g, a, b)){
                    inDev = 0;
                    break;
                }
            }
            if (inDev) dev[i].push_back(j);
        }
    }
    int m = 0;
    for (int i = 0; i < n; ++i)
        if (m < dev[i].size())
            m = i;
    for (int i : dev[m])
        cout << country[i] << ",";
    cout << endl;
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
    getline(ifs, data);
    stringstream ss(data);
    vector <string> country;
    while (ss)
    {
        string c;
        getline(ss, c, ',');
        if (c != "") country.push_back(c);
    }
    directA(g, country[0]);
    cout << "=====\n";
    CPDegree(g);
    cout << endl;
    cout << "=====\n";
    devArea(g, country);
    cout << "=====\n";
    ifs.close();
}



void main_debug(){
    // Main for student
    todo("g1.v2.jl", "data.txt");
}
