#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;
vector<vector<int>> inputMatrix (const string filename)
{
    ifstream ifs(filename);
    int n; ifs >> n;
    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; ++i)  {
        matrix[i].resize(n);
        for (int j = 0; j < n; ++j) {
            ifs >> matrix[i][j];
        }
        //cout
    }

    ifs.close();
    return matrix;
}

vector<vector<int>> matrixToList(vector<vector<int>> matrix)
{
    int n = matrix.size();

    vector<vector<int>> adjList(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1)
                adjList[i].push_back(j);
        }

        for (int x : adjList[i])
            cout << x << " ";

        cout << "\n";
    }
    return adjList;
}

vector<vector<int>> inputList(const string filename)
{
    ifstream ifs(filename);
    int n; ifs >> n;
    string dump;
    getline(ifs, dump);

    vector<vector<int>> adjList(n);;
    for (int i = 0; i < n; ++i) {
        string data;
        getline(ifs, data);
        stringstream ss(data);
        int j;
        char space;
        while (ss >> j) {
            adjList[i].push_back(j);
            ss >> space;
        }
    }
    ifs.close();

    return adjList;
}

vector<vector<int>> ListToMatrix(vector<vector<int>> adjList)
{
    int n = adjList.size();

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            matrix[i].push_back(0);
        for (int j : adjList[i])
            matrix[i][j] = 1;
        for (int x : matrix[i]) cout << x << " ";

        cout << endl;
    }

    return matrix;
}
/*int matrix** = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            ifs >> matrix[i][j];
    }*/

bool directGraph(vector<vector<int>> a)
{
    int n = a.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++ j)
            if (a[i][j] != a[j][i]) return 1;
    return 0;
}

vector<int> degreeOfUndirect(vector<vector<int>> adjList)
{
    int n = adjList.size();
    vector<int> d (n, 0);
    for (int i = 0; i < n; ++i) {
        d[i] = adjList[i].size();
    }
    return d;
}
vector<int> outDegree(vector<vector<int>> adjList)
{
    int n = adjList.size();
    vector<int> d(n, 0);
    for (int i = 0; i < n; ++i) {
        d[i] = adjList[i].size();
    }
    return d;
}
vector<int> inDegree(vector<vector<int>> adjList)
{
    int n = adjList.size();
    vector<int> d(n, 0);
    for (int i=0; i<n; ++i) {
        for (int j : adjList[i])
            d[j]++;
    }
    return d;
}

int edges(vector<vector<int>> adjList)
{
    int n = adjList.size();
    int edge = 0;
    for (int i = 0; i < n; ++i)
    {
        edge += adjList[i].size();
    }
    if (!directGraph(adjList)) edge /=2;
    return edge;
}

void dfs(int u, vector<vector<int>> adjList, vector<bool>& visited) {
    if (visited[u]) return;
    visited[u] = 1;

    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfs(v, adjList, visited);
        }
    }
}

int connectedComponents(vector<vector<int>> adjList)
{
    int components = 0;
    int n = adjList.size();

    vector <bool> visited (n, 0);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adjList, visited);
            components++;
        }
    }
    return components;
}

int countTrees(vector<vector<int>> adjList) {
    int components = ConnectedComponents(adjList);
    int edges = 0;
    for (int i = 0; i < V; ++i) {
        edges += adjList[i].size();
    }
    edges /= 2;

    // Number of trees = Number of connected components - Number of edges
    return components - edges;
}

int main()
{
    vector<vector<int>> adjList;
    vector<vector<int>> matrix = inputMatrix("graph1.txt");
    adjList = matrixToList(matrix);
    cout << "=====\n";
    adjList = inputList("graph2.txt");
    matrix = ListToMatrix(adjList);
    cout << connectedComponents(adjList);
}
