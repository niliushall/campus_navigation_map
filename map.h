#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

#define CLEAR system("clear");
#define WAIT {cin.get(); cin.get();};
const int MAXVEX = 20;

struct EdgeNode {
    int adjvex;  //标号
    int length;  //距离
    struct EdgeNode *next;
};

struct VertexNode {
    string name;  //名称
    EdgeNode *FirstEdge;
};

class SchoolMap {
private:
    vector<VertexNode> Map;  //邻接表
    int numVertexes;  //结点个数
    int numEdges;  //边个数
public:
    SchoolMap() {numVertexes = numEdges = 0;};
    void menu() const;
    void CreateMapFromFile();  //创建邻接表
    int findVertexNum(const string & str) const;  //寻找结点下标
    int info() const;
    void allPath() const;  //所有简单路径
    void dfs(const int start, const int end, vector<bool> visited, vector<int> path) const;
    void shortestPath() const;  //中转次数最少路径
    void shortestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> & tmp, int & max, int len) const;
    void bestPath() const;  //最短路径
    void bestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> tmp, int & max, int len) const;
    void bestMap() const;  //最佳布网方案
    void print() const; 
};