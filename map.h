#include<iostream>
#include<vector>
#include<string>
using namespace std;

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
    void CreateMapFromFile();  //创建邻接表
    int findVertexNum(const string & str) const;  //寻找结点下标
    int info() const;
};