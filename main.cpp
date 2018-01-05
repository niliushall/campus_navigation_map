#include<fstream>
#include<unistd.h>
#include"map.h"

void SchoolMap::print() const {
    EdgeNode *p;
    for(int i = 0; i < numVertexes; i++) {
        p = Map[i].FirstEdge;
        while(p) {
            cout << Map[p->adjvex].name << endl;
            p = p->next;
        }
        cout << endl;
    }
}

void SchoolMap::menu_login() {
    int choice;

    do {
        CLEAR;
        cout << "============================================" << endl;
        cout << "=========       登录 or 注册        ==========" << endl;
        cout << "============================================" << endl;
        cout << "======        1. 注册                 =======" << endl;
        cout << "======        2. 个人帐号登录          =======" << endl;
        cout << "======        3. 管理员帐号登录        =======" << endl;
        cout << "======        0. 退出                 =======" << endl;
        cout << "============================================" << endl << endl;
        cout << "请选择你要登录的类型：\n";
        cin >> choice;

        if(cin.fail()) {
            cout << "输入错误...\n";
            cin.clear();
            char ch;
            while(cin.get(ch) && ch != '\n') ;
            continue;
        }

        switch(choice) {
            case 0: return;
            case 1: Register(); break;
            case 2: login(); break;
            case 3: administer_login(); break;
            default:
                cout << "输入数字超出范围...\n";
        }

    }while(true);

}

void SchoolMap::Register() const {
    CLEAR;

    string account, password, filename;
    cout << "请输入：\n\n";
    cout << "帐号: ";
    cin >> account;
    cout << "密码: ";
    system("stty -echo");
    cin >> password;
    system("stty echo");
    filename = DIR_ACCOUNT + account;

    ofstream fout;
    fout.open(filename);
    if(!fout.is_open()) {
        cout << "帐号新建错误...\n";
        return;
    }

    fout << password;
    fout.close();

    cout << "用户新建成功...\n";
    WAIT;
}

void SchoolMap::administer_login() {
    CLEAR;
    
    string account, password, tpassword, filename;
    cout << "请输入管理员帐号: ";
    cin >> account;
    cout << "请输入密码: ";
    system("stty -echo");
    cin >> tpassword;
    system("stty echo");

    filename = DIR_ADMINISTER + account;

    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "登录出错...\n";
        return;
    }

    fin.close();
    menu_administer();  //进入管理员界面
}

void SchoolMap::menu_administer() {
    do {
        CLEAR;

        cout << "\t1. 添加地点\n\n";
        cout << "\t2. 删除地点\n\n";
        cout << "\t0. 退出\n\n";

        int choice;
        cin >> choice;
        if(cin.fail()) {
            cout << "输入错误...\n";
            cin.clear();
            char ch;
            while(cin.get(ch) && ch != '\n') ;
            continue;
        }

        switch(choice) {
            case 0: return;
            case 1: addPlace(); break;
            // case 2: delPlace(); break;
            default:
                cout << "输入错误...\n";
                WAIT;
                return;
        }
    }while(true);
}

void SchoolMap::addPlace() {
    int n;
    string name, len;
    cout << "请输入要添加的地点个数: ";
    cin >> n;

    //添加第i个结点
    for(int i = 0; i < n; i++) {
        VertexNode *pNew = new VertexNode;
        cout << "第" << i+1 << "个地点信息:\n";
        cout << "名称 : ";
        cin >> name;
        pNew->name = name;
        pNew->FirstEdge = NULL;

        Map.push_back(*pNew);

        //添加邻边
        int num;
        cout << "请输入相邻的地点个数 : ";
        cin >> num;
        for(int j = 0; j < num; j++) {
            cout << "请输入第" << j+1 << "个相邻的地点名称 : ";
            cin >> name;

            //在新结点后添加邻边
            EdgeNode *p = new EdgeNode;
            int index;
            index = findVertexNum(name);
            p->adjvex = index;
            p->next = NULL;
            Map[numVertexes-1].FirstEdge = p;

            //在邻接点后添加新边
            p = new EdgeNode;
            p->adjvex = numVertexes-1;
            p->next = Map[index].FirstEdge;
            Map[index].FirstEdge = p;
        }
        numVertexes++;  //结点个数加1           
    }
}

void SchoolMap::login() const {
    CLEAR;

    string account, tpassword, password;
    cout << "请输入 :\n\n";
    
    cout << "\t帐号 : ";
    cin >> account;
    cout << "\t密码 : ";
    system("stty -echo");
    cin >> tpassword;
    system("stty echo");
    
    string filename = DIR_ACCOUNT + account;
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "没有该用户 " << account << " ...\n";
        WAIT;
        return ;
    }
    fin >> password;
    if(password == tpassword) {
        cout << "\n\n登录成功...\n";
        WAIT;
        menu();
    } else {
        cout << "密码错误...\n";
        WAIT;
    }
}

void SchoolMap::menu() const {
    int choice;

    do {
        CLEAR;
        cout << "============================================" << endl;
        cout << "=========       校园导航系统        ==========" << endl;
        cout << "============================================" << endl;
        cout << "======    1. 输出校园平面图              ======" << endl;
        cout << "======    2. 查询校园信息               ======" << endl;
        cout << "======    3. 查询两地间所有简单路径       ======" << endl;
        cout << "======    4. 查询两地间中转次数最少路径    ======" << endl;
        cout << "======    5. 查询两地间最佳访问路径       ======" << endl;
        cout << "======    6. 设计最佳布网方案            ======" << endl;
        cout << "======    0. 退出                      ======" << endl;
        cout << "============================================" << endl << endl;
        cout << "请选择你要查询的信息编号：\n";

        cin >> choice;

        if(cin.fail()) {
            cout << "输入数字错误...\n";
            char ch;
            cin.clear();
            while(cin.get(ch) && ch != '\n');
            cin.get();
            continue;
        }

        switch(choice) {
            case 0: return;
            case 1: system("eog map1.jpg"); WAIT; break;
            case 2: info(); WAIT; break;
            case 3: SchoolMap::allPath(); WAIT; break;
            case 4: SchoolMap::shortestPath(); WAIT; break;
            case 5: SchoolMap::bestPath(); WAIT; break;
            case 6: SchoolMap::bestMap(); WAIT; break;
            default:
                cout << "数字超出范围，按任意键返回...\n";
                fflush(stdin);
                // cin.get();
                WAIT;
                break;

        }
    }while(true);
}

int SchoolMap::findVertexNum(const string & str) const {
    int i;
    for(i = 0; i < numVertexes; i++) {
        if(str == Map[i].name) {
            return i;
        }
    }
    
    cout << "未找到该地点 - " << str << endl;
    return -1;
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
    string filename, t("information/");
    cout << "请输入要查询信息的地点： ";
    cin >> filename;
    filename = t + filename;

    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "打开文件 " << filename << " 错误\n";
        return 0;
    }

    char ch;
    while(fin.get(ch)) {
        cout << ch;
    }

    fin.close();
}

void SchoolMap::allPath() const {
    string str1, str2;
    int start, end;
    vector<bool> visited(MAXVEX, false);
    vector<int> path;    

    cout << "请输入路径的起点：\n";
    cin >> str1;
    cout << "请输入路径的终点：\n";
    cin >> str2;

    start = findVertexNum(str1);
    end = findVertexNum(str2);

    //地点输入错误
    if(start == -1 || end == -1) {
        return;
    }

    dfs(start, end, visited, path);
}

void SchoolMap::dfs(const int start, const int end, vector<bool> visited, vector<int> path) const {
    EdgeNode *p;
    p = Map[start].FirstEdge;
    visited[start] = true;
    path.push_back(start);  //将该函数的起点放入数组    

    while(p) {
        if(p->adjvex != end && !visited[p->adjvex]) {
            dfs(p->adjvex, end, visited, path);
        } else if(p->adjvex == end) {
            for(vector<int>::iterator it = path.begin(); it != path.end(); it++) {
                cout << Map[*it].name << " --> ";
            }
            cout << Map[end].name << endl;
        }
        p = p->next;
    }
    visited[start] = false;
    path.pop_back();
}

void SchoolMap::shortestPath() const {
    string str1, str2;
    int start, end, min = 99999999, len = 1;
    vector<bool> visited(MAXVEX, false);
    vector<int> path;
    vector<int> tmp;

    cout << "请输入路径的起点：\n";
    cin >> str1;
    cout << "请输入路径的终点：\n";
    cin >> str2;

    start = findVertexNum(str1);
    end = findVertexNum(str2);

    //地点输入错误
    if(start == -1 || end == -1) {
        cout << "所输入地点不存在\n";
        return;
    }

    shortestPathDfs(start, end, visited, path, tmp, min, len);//dfs寻找最短路径

    cout << "最短路径（中转次数最少）为：\n";
    for(vector<int>::iterator it = path.begin(); it != path.end(); it++) {
        cout << Map[*it].name << " --> ";
    }
    cout << Map[end].name << endl;
}

void SchoolMap::shortestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> & tmp, int & min, int len) const {
    EdgeNode *p;
    p = Map[start].FirstEdge;
    visited[start] = true;
    tmp.push_back(start);

    while(p) {
        if(p->adjvex != end && !visited[p->adjvex]) {
            shortestPathDfs(p->adjvex, end, visited, path, tmp, min, len+1);
        } else if(p->adjvex == end) {
            if(min > len) {
                min = len;
                path = tmp;
            }
        }
        p = p->next;
    }
    visited[start] = false;
    tmp.pop_back();
}

void SchoolMap::bestPath() const {
    string str1, str2;
    int start, end, min = 9999999, len = 0;
    vector<bool> visited(MAXVEX, false);
    vector<int> path;
    vector<int> tmp;

    cout << "请输入路径的起点：\n";
    cin >> str1;
    cout << "请输入路径的终点：\n";
    cin >> str2;

    start = findVertexNum(str1);
    end = findVertexNum(str2);

    //地点输入错误
    if(start == -1 || end == -1) {
        cout << "所输入地点不存在\n";
        return;
    }

    bestPathDfs(start, end, visited, path, tmp, min, len);

    cout << "最短路径(距离最小)为：\n";
    for(vector<int>::iterator it = path.begin(); it != path.end(); it++) {
        cout << Map[*it].name << " --> ";
    }
    cout << Map[end].name << endl;
    cout << "最短路径长度为： " << min << endl;
}

void SchoolMap::bestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> tmp, int & min, int len) const {
    EdgeNode *p;
    p = Map[start].FirstEdge;
    visited[start] = true;
    tmp.push_back(start);

    while(p) {        
        if(p->adjvex != end && !visited[p->adjvex]) {
            bestPathDfs(p->adjvex, end, visited, path, tmp, min, len+p->length);
        } else if(p->adjvex == end) {
            if(min > len) {
                min = len;
                path = tmp;
            }
        }
        p = p->next;
    }
    visited[start] = false;
    tmp.pop_back();
}

void SchoolMap::bestMap() const {
    const int INFINITY = 65535;
    vector<int> adjvex(MAXVEX, 0);  //存储结点下标
    vector<int> lowcost(MAXVEX, 0);  //存储邻接边的权值，值为0表示该点已经在生成树中

    EdgeNode *p = Map[0].FirstEdge;

    for(int i = 1; i < numVertexes; i++) {
        lowcost[i] = INFINITY;
    }

    int i = 0;
    while(p) {  //假设从第一个点开始生成树
        lowcost[i++] = p->length;
        p = p->next;
    }

    cout << "最佳布网方案:\n\n";

    int min, current;  //current存储当前最小值的下标
    for(int i = 1; i < numVertexes; i++) {
        min = INFINITY;
        current = 0;

        for(int j = 1; j < numVertexes; j++) {
            if(lowcost[j] && lowcost[j] < min) {
                min = lowcost[j];
                current = j;
            }
        }
        lowcost[current] = 0;
        cout << "( " << Map[adjvex[current]].name << ", " << Map[current].name << " )" << endl;
        
        p = Map[current].FirstEdge;
        while(p) {
            if(lowcost[p->adjvex] && p->length < lowcost[p->adjvex]) {
                lowcost[p->adjvex] = p->length;
                adjvex[p->adjvex] = current;
            }
            p = p->next;
        }
    }
}

int main() {
    SchoolMap map;
    map.CreateMapFromFile();

    map.menu_login();

    return 0;
}