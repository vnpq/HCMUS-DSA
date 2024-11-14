#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;
void print(vector<vector<int>> result)
{
	for(int i = 0; i < result.size();i++)
	{
		for(int j : result[i])
		{
			cout << j << " ";
		}
		cout << endl;
	}
}
vector<vector<int>> readFile(string filename)
{
	vector<vector<int>> infor;
	ifstream fread(filename);
	if(!fread.is_open())
	{
		cout << "Can't open";
		return infor;
	}
	int number;
	fread >> number;
	fread.ignore();
	cout << number << ' ';
	int num;
	while(!fread.eof())
	{
		vector<int> result;
		for(int i = 0; i < number;i++)
		{
			fread >> num;
			if(num==1)
			{
				result.push_back(i);
			}
		}
		infor.push_back(result);
	}
	fread.close();
	cout << '-' << infor.size() << ' ';
	return infor;
}

vector<vector<int>> listToMatrix(const string filename)
{
	ifstream ifs(filename);
	int n;
	ifs >> n;
	string dump;
	getline(ifs, dump);
	vector<vector<int>> matrix(n);

	for (int i = 0; i < n; ++i) {
		matrix[i].resize(n);
		for (int j = 0; j < n; ++j)
			matrix[i][j] = 0;
		//print()
		string data;
		getline(ifs, data);
		stringstream ss(data);
		char space;
		int j;
		while (ss >> j)
			matrix[i][j] = 1;
			//ss >> space;
	}
	return matrix;
}
bool isUndirected(vector<vector<int>> matrix)
{
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<i; j++)
		if(matrix[i][j] != matrix[j][i]) return false;
	}
	return true;
}

int getEdge(const vector<vector<int>> &adj)
{
	int numEdge = 0;
	bool isUndirec = isUndirected(adj);
	int n = isUndirec? 1 : adj.size();
	for(int i = 0; i < adj.size(); i++)
	{
		for(int j = 0; j < n; j++)
			if (adj[i][j]) numEdge++;
		if (isUndirec) n++;
	}

	return numEdge;
}

int getVertice(const vector<vector<int>> &adj)
{
	return adj.size();
}

int *DegreeUndirect(vector<vector<int>> a)
{
	int n = a.size();
	int* degree = new int[n];
	for (int i = 0; i < n; i++)
	{
		degree[i] = 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++)
			degree[i]++;
	return degree;
}

int *DegreeDirect(vector<vector<int>> a)
{

	int n = a.size();
	int* inDegree = new int[n];
	int * outDegree = new int[n];
	for (int i = 0; i < n; i++)
		inDegree[i] = outDegree[i] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j])
			{
				outDegree[i]++;
				inDegree[j]++;
			}
	int *degree = new int[n];
	for (int i = 0; i < n; i++)
		degree[i] = inDegree[i] + outDegree[i];
	return degree;
}

vector<int> isolatedVertex(vector<vector<int>> matrix)
{
	vector<int> result;
	int *degree = DegreeDirect(matrix);
	for (int i = 0; i < matrix.size(); ++i){
		//cout << degree[i] << '\n';
		if (degree[i] == 0) result.push_back(i);
	}
	return result;
}


vector<int> leafVertex(vector<vector<int>> matrix)
{
	vector<int> result;
	int *degree = DegreeDirect(matrix);
	for (int i = 0; i < matrix.size(); ++i){
		//cout << degree[i] << '\n';
		if (degree[i] == 1) result.push_back(i);
	}
	return result;
}
int main()
{
	vector<vector<int>> result = listToMatrix("list.txt");
	//vector<vector<int>> list = readFile("matrix.txt");
	//print(list);
//	cout<<isUndirected(result);
//	cout << '\n';
//	cout << getEdge(result) << '\n';
//	cout << getVertice(result) << '\n';
//	int *degree;
//	if (isUndirected(result))
//		degree = DegreeUndirect(result);
//	else degree = DegreeDirect(result);
//	cout << degree[3];
	vector<int> isolated = isolatedVertex(result);
	cout << '\n';
//	for (int i = 0; i < isolated.size(); ++i)
//		cout << isolated[i] << ' ';
	vector<int> leafs = leafVertex(result);
	for (int i = 0; i < leafs.size(); ++i)
		cout << leafs[i] << ' ';
	/*vector<vector<int>> matrix = listToMatrix("list.txt");
	print(matrix);*/
}

