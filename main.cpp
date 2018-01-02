#include<fstream>
#include"map.h"

int SchoolMap::findVertexNum(const string & str) const {
    int i;
    for(i = 0; i < numVertexes; i++) {
        if(str == Map[i].name) {
            return i;
        }
    }
    return 0;
}

void SchoolMap::CreateMapFromFile() {
    //读取顶点信息
    ifstream fin;
    fin.open("vertex.txt");
    if(!fin.is_open()) {
        cout << "打开文件 vertex.txt 错误\n";
        return;
    }

    fin >> numVertexes;
    VertexNode t;
    for(int i = 0; i < numVertexes; i++) {
        fin >> t.name;
        t.FirstEdge = NULL;
        Map.push_back(t);
    }

    fin.close();
    fin.clear();

    //读取邻边信息
    fin.open("map.txt");
    if(!fin.is_open()) {
        cout << "打开文件 map.txt 错误\n";
        return;
    }

    fin >> numEdges;
    string str1, str2;
    int index1, index2, value;

    for(int i = 0; i < numEdges; i++) {
        fin >> str1 >> str2 >> value;
        index1 = findVertexNum(str1);
        index2 = findVertexNum(str2);

        //将点str2添加到str1后, 头插法        
        EdgeNode *pNew = new EdgeNode;
        pNew->adjvex = index2; 
        pNew->length = value;        
        pNew->next = Map[index1].FirstEdge;        
        Map[index1].FirstEdge = pNew;

        //将点str1添加到str2后, 头插法
        pNew = new EdgeNode;
        pNew->adjvex = index1; 
        pNew->length = value;
        pNew->next = Map[index2].FirstEdge;
        Map[index2].FirstEdge = pNew;
    }
}

int SchoolMap::info() const {
    string filename;
    cout << "请输入要查询信息的地点： ";
    cin >> filename;

    istream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "打开文件 " << filename << " 错误\n";
        return 0;
    }

    fin >> 
}

int main() {
    SchoolMap map;
    map.CreateMapFromFile();

    return 0;
}