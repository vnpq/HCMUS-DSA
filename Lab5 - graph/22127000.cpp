#include "func.cpp"
#include <map>
#include <queue>

void readFlight(ifstream &fi, map<string, vector<Flight>> &adj)
{
    string lineData;
    while (getline(fi, lineData))
    {
        stringstream ss(lineData);
        Flight data;
        data.src = data.des = "";
        data.bus = data.eco = 0;
        data.hours = data.mins = 0;
        string dumpData;
        getline(ss, dumpData, '\"');
        getline(ss, data.src, ',');
        getline(ss, data.des, '\"');

        getline(ss, dumpData, '\"');
        getline(ss, data.airliner, '\"');

        getline(ss, dumpData, '\"');
        ss >> data.bus;
        getline(ss, dumpData, ',');
        // truong hop khong co business
        if (dumpData[1] == 'e')
        {
            data.eco = data.bus;
            data.bus = 0;
        }
        else
        {
            // truong hop co eco
            if (dumpData.back() != '\"'){
                ss >> data.eco;
                getline(ss, dumpData, ',');
            }
        }
        getline(ss, dumpData, '\"');

        ss >> data.hours;
        getline(ss, dumpData, ',');
        // khong co hours
        if (dumpData[1] != 'h')
        {
            data.mins = data.hours;
            data.hours = 0;
        }

        // co minutes
        if (dumpData.back() != '}')
            ss >> data.mins;

        adj[data.src].push_back(data);
    }
}

void dfs(string src, map<string, vector<Flight>> adj, map<string, bool> &visited)
{
    // da tham
    if (visited[src]) return;
    visited[src] = 1;
    cout << src << '\n';
    for (auto flight : adj[src])
        dfs(flight.des, adj, visited);
}

void bfs(string start, map<string, vector<Flight>> adj, map<string, bool> &visited)
{
    queue<string> q;
    q.push(start);
    while (!q.empty())
    {
        string src = q.front(); q.pop();
        cout << src << '\n';
        if (visited[src]) continue;
        visited[src] = 1;
        for (auto flight : adj[src])
            q.push(flight.des);
    }
}

void todo(string flightdata_filename, string data_filename){
    ifstream fi(flightdata_filename);
    map<string, vector<Flight>> adj;
    map<string, bool> visited;
    readFlight(fi, adj);

    // for (auto e : adj)
    // {
    //     cout << "FROM : " << e.first << "\n";

    //     cout << "TO :\n";
    //     for (auto f : e.second)
    //         cout << f.des << '\n';
    //     cout << "--------------------------------------\n";

    // }

    dfs("Myanmar", adj, visited);

    // bfs("Italy", adj, visited);

    fi.close();
}


void main_debug(){
    // Main for student
    todo("g1.v2.jl", "data.txt");
    //writeNode(root);
}
