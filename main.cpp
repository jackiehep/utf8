#include <iostream>
#include <fstream>
#include "locale.h"
#include "hash_fun.h"
#include "map"
#include "algorithm"
#include "list"
#include "float.h"
#include "hash_fun.h"
#include <linux/sched.h>
#include "algorithm"
#include "thread"
#include "mutex"
using namespace std;
hash<string> hash_func;
int main1() {
    std::cout << "Hello, World!" << std::endl;
    ifstream  ifs;
    setlocale(LC_ALL,"C.UTF-8");
    //ifs.imbue(locale("chs"));
    ifs.open("/usr/local/bin/test.txt");
    char temp[256]={0};
    while(ifs.getline(temp,256)){
        string out=temp;
        cout<<out<<endl;
    }

    return 0;
}

class Process{
private:
    int count;
public:
    Process(int cnt):count(cnt){}
    int GetCount(){
        return count;
    }
    void AddCount(){
        count++;
    }
};

typedef map<string,string> IP_PROCESS_MAP;//IP PROCESS_NAME

typedef IP_PROCESS_MAP::iterator IP_PROCESS_MAP_IT;

IP_PROCESS_MAP ip_process_map;

IP_PROCESS_MAP_IT ip_process_it;

typedef IP_PROCESS_MAP::value_type value_type;

//MAP FOR PROCESS_NAME PROCESS
typedef map<string ,Process *> PROCESS_MAP;//PROCESS_NAME PROCESS

typedef PROCESS_MAP::iterator PROCESS_MAP_IT;

PROCESS_MAP  process_map;

PROCESS_MAP_IT process_it;

typedef PROCESS_MAP::value_type value_type_1;

typedef map<Process * ,list<string>*> PROCESS_IP_MAP;

typedef PROCESS_IP_MAP ::value_type value_type_2;
//it could compute key and also could compute value
bool cmp_process_count(const pair<Process * ,list<string>*> left,const pair<Process*,list<string>*> right){
    return left.first->GetCount()<right.first->GetCount();
}

void print_list(list<string > * pList){
    list<string> input=*pList;
    for (const auto &item: input) {
        cout<<item<<endl;
    }
}
void testMapProcessFunc(){
    PROCESS_IP_MAP  processIpMap;
    list<string> * listone=new list<string>;
    listone->push_back("10.20.4.171");
    listone->push_back("10.20.4.172");
    processIpMap.insert(value_type_2(new Process(2),listone));
    list<string> * listone1=new list<string>;
    listone1->push_back("10.20.4.173");
    listone1->push_back("10.20.4.174");
    processIpMap.insert(value_type_2(new Process(4),listone1));
    list<string> * listone2=new list<string>;
    listone2->push_back("10.20.4.175");
//    listone2->push_back("10.20.4.176");
    processIpMap.insert(value_type_2(new Process(1),listone2));
    auto ivalue= min_element(processIpMap.begin(),processIpMap.end(), cmp_process_count);
    cout<<ivalue->first->GetCount()<<"   "<<endl;
    ivalue->first->AddCount();
    list<string> * pList=ivalue->second;
    for (const auto &item: *pList) {
        cout<<item<<endl;
    }
    pList->push_back("10.20.4.199");
    print_list(pList);
    cout<<"DEBUG [0] SHOW COUNT"<<endl;
    cout<<ivalue->first->GetCount()<<endl;
}


bool cmp_value(const pair<string,Process *> left,const pair<string,Process*> right){
    return left.second->GetCount()<right.second->GetCount();
}

void testMinValue(){
    map<string,Process*> myvalueone;
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(1)));
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(2)));
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(3)));
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(4)));
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(5)));
    myvalueone.insert(map<string,Process*>::value_type("jackie1",new Process(6)));
    auto i= min_element(myvalueone.begin(),myvalueone.end(),cmp_value);
    cout<<i->first<<" "<<i->second->GetCount()<<endl;
}

class Info{
private:
    string sInput;
public:
    Info(string sin):sInput(sin){}
    void print_info(){
        cout<<sInput<<endl;
    }
    string GetInput(){
        return sInput;
    }
};

class InfoList{
private:
    typedef list<Info*> INFO_LIST;
    INFO_LIST  m_list;
    typedef INFO_LIST ::iterator  INFO_LIST_IT;
    INFO_LIST_IT m_it;
public:
    void AddElement(Info * info){
        m_list.push_back(info);
    }
    void DeleteElement(string input){
        m_it=m_list.begin();
        for(;m_it!=m_list.end();){
            if ((*m_it)->GetInput()==input){
                m_list.erase(m_it++);
                break;
            }else
            {
                m_it++;
            }
        }
    }
    void PrintElement(){
        m_it=m_list.begin();
        for(;m_it!=m_list.end();m_it++){
            Info * info=(*m_it);
            cout<<info->GetInput()<<endl;
        }
    }
};

void TestListFunc(){
    InfoList infoList;
    Info * pInfo1=new Info("jackie1 hepeng");
    Info * pInfo2=new Info("jackie2 hepeng");
    Info * pInfo3=new Info("jackie3 hepeng");
    Info * pInfo4=new Info("jackie4 hepeng");
    infoList.AddElement(pInfo1);
    infoList.AddElement(pInfo2);
    infoList.AddElement(pInfo3);
    infoList.AddElement(pInfo4);
    infoList.DeleteElement("jackie2 hepeng");
    infoList.PrintElement();
}

class CJackie{
private:
    string sinput;
    string soutput;
public:
    CJackie(string sin,string sout):sinput(sin),soutput(sout){}
    void print_all_info(){
        cout<<sinput<<" "<<soutput<<endl;
    }
};
class CJackie1:public CJackie{
private:
    string sout;
public:
    CJackie1(string sin1,string sin2 ,string sout):sout(sout), CJackie(sin1,sin2){}
    void pirnt_all_info(){
        CJackie::print_all_info();
        cout<<sout<<endl;
    }
};
class CDefine{
private:
    string sinput;
    int    ninput;
public:
    CDefine(string sin,int nin):ninput(nin),sinput(sin){}
    void play_info(){
        cout<<sinput<<" "<<ninput<<endl;
    }
};

class CDialog{
private:
    string sinput;
    CDefine& define;
public:
    CDialog(CDefine * definevalue):define(*definevalue){}
    void show_info(){
        define.play_info();
    }
};

class CInformation{
private:
    CDialog * pDialog;
public:
    CInformation(CDialog & dialog):pDialog(&dialog){}
    void show_info(){
        pDialog->show_info();
    }
};

class virtualBase{
private:
    string input;
public:
    virtualBase(){}
    virtual void play_on_it()=0;
};
class virtualDrive1:public virtualBase{
private:
    int value;
public:
    virtualDrive1(int ival):value(ival){}
    virtual void play_on_it(){
        cout<<value <<" peng print "<<endl;
    }
};
class virtualDrive2:public virtualBase{
private:
public:
    virtualDrive2(){}
    virtual void play_on_it(){
        cout<<"This is virtual Driver2 print "<<endl;
    }
};

void Action(){
    virtualBase * pbase=NULL;
    pbase=new virtualDrive1(1000);
    pbase->play_on_it();
    pbase=new virtualDrive2();
    pbase->play_on_it();
}
int main2(){
    Action();
    CDefine define("test",100);
    CDialog dialog(&define);
    dialog.show_info();
    CInformation information(dialog);
    information.show_info();
    TestListFunc();

    string input="hepengjackie";
    string input1="hepengjackie";
    testMapProcessFunc();
}

#include <iostream>
#include <vector>

using namespace std;

// 定义物品结构体
struct Item {
    int weight;
    int value;
};

// 背包问题函数
int knapsack(int W, vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], items[i - 1].value + dp[i - 1][j - items[i - 1].weight]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][W];
}
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void slidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    int windowSum = 0;

    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }

    cout << "初始窗口的和为: " << windowSum << endl;

    for (int i = k; i < n; i++) {
        windowSum += nums[i] - nums[i - k];
        cout << "窗口[" << (i - k + 1) << ", " << i << "] 的和为: " << windowSum << endl;
    }
}


void FillMeans(vector<int>& input){
    int sum=0;
    int count=0;
    for(auto value:input){
        if(sum!=-1){
            sum+=value;
            count++;
        }
    }
    int mean=sum/count;
    replace(input.begin(),input.end(),-1,mean);

}

void MapAction(map<int ,string> & mapInfo){
    auto it=mapInfo.begin();
    for(auto value:mapInfo){
        cout<<"hepeng print "<<value.first<<" second"<<value.second<<endl;
    }
    auto it1=mapInfo.find(10);
    if(it1!=mapInfo.end()){
        cout<<it1->second<<endl;
    }
}
#include "memory"
using namespace std;
void pointerSmart(){
    shared_ptr<int> pl= make_shared<int>(10);
    cout<<" 111 "<<*pl<<endl;
    pl.reset();

    shared_ptr<int> pl1(new int[10],[](int *p){
        delete [] p;
    });
    list<string> mylist;
    mylist.push_back("jackie1");
    mylist.push_back("hello1");
    for(auto value:mylist){
        if(value=="jackie1")
            cout<<"i am jackie"<<endl;
    }

}
void deleteVectInfo(vector<int> & info,int value){
    auto it=info.begin();
    for(;it!=info.end();){
        if(*it==value)
            info.erase(it++);
        else it++;
    }
}
void printVectInfo(vector <int> & info){
    for(auto value:info)
        cout<< value <<" ";
    cout<<endl;

}

void testThisCase(){
    vector<int> test{1,2,3,4,5,6};
    deleteVectInfo(test,2);
    printVectInfo(test);
    deleteVectInfo(test,5);
    printVectInfo(test);
}
int main7() {
    testThisCase();
    vector<int> nums = {1, 3, 2, 4, 5, 6, 7, 8};
    int k = 3;
    pointerSmart();
    slidingWindow(nums, k);
    vector<int> numbers={1,1,2,3,4,5,6,5,3,4,-1,10,7,8,9};
    vector<int> numbers1={1,1,2,3,4,5,6,5,3,4,-1,10,7,8,9};
    sort(numbers.begin(),numbers.end());
    auto it= unique(numbers.begin(),numbers.end());
    numbers.erase(it,numbers.end());
    int size=numbers.size();
    cout<<"size is "<<size<<endl;
    for(int i=0;i<size;i++)
        cout<<numbers[i]<<" ";
    cout<<endl;
    FillMeans(numbers1);
    for(auto value:numbers1)
        cout<<value <<" ";
    cout<<endl;

    map<int ,string> info;
    info.clear();
    info.insert(make_pair(10,"jackie"));
    info.insert(make_pair(20,"dialog"));
    info.insert(make_pair(30,"hello,world"));
    for(auto val:info){
        cout<<val.first<<" "<<val.second<<endl;
    }
    MapAction(info);

    map<string,vector<int> * >  vectMap;
    vector<int> * v1=new vector<int>();
    v1->push_back(10);
    v1->push_back(11);
    v1->push_back(12);
    vector<int> * v2=new vector<int>();
    v2->push_back(10);
    v2->push_back(11);
    v2->push_back(12);
    vectMap.insert(make_pair("jackie1",v1));
    vectMap.insert(make_pair("jackie2",v2));
    for(auto value:vectMap){
        cout<<value.first<<endl;
        for(auto value2:*value.second){
            cout<<value2<<endl;
        }
    }


    return 0;
}


int main3() {
    int W = 50;  // 背包容量

    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};  // 物品列表

    int max_value = knapsack(W, items);  // 背包问题求解

    cout << "背包能够容纳的最大价值为: " << max_value << endl;

    return 0;
}
int main2f(){
    const char *value="52132132231122";
    int64_t ivalue=atoi(value);
    float fvalue=atof(value);
    double dValue=strtod(value, nullptr);
    cout<<fvalue<<endl;
    cout<<dValue<<endl;
    cout<<ivalue<<endl;
    hash<string> hash_string;
    cout<<hash_string("jackie")<<endl;
    long hash_code=hash_string("jackie");
    cout<<hash_code<<endl;
    return 1;
}

class InfoManager{
private:
    list<string> stringLst;
public:
    void AddStringElement(string sElement){
        stringLst.push_back(sElement);
    }
    void DelEleemnt(string sElement){
        auto it=stringLst.begin();
        for(;it!=stringLst.end();){
            if(*it==sElement){
                stringLst.erase(it++);
            }else it++;
        }
    }
    void PrintAllInfo(){
        for(auto value:stringLst)
            cout<<value<<" ";
        cout<<endl;
    }
    void ModifyElement(string sElement,string value){
        auto it=stringLst.begin();
        for(;it!=stringLst.end();){
            if(*it==sElement){
                *it=value;
                break;
            }else
                it++;
        }
    }
};

class MapManager{
private:
    map<string,string>  InfoMap;
public:
    void AddEleeent(string s1,string s2){
        InfoMap.insert(make_pair(s1,s2));
    }
    void DelElement(string sinput){
        auto it = InfoMap.find(sinput);
        if(it!=InfoMap.end()){
            InfoMap.erase(sinput);
        }
    }
    void QueryList(){
        auto it=InfoMap.begin();
        for(;it!=InfoMap.end();it++)
        {
            cout<<" first "<<it->first<<" second "<<it->second<<endl;
        }
    }
};
#include "thread"
#include "mutex"

class ClassDefine{
private:
    int iValue;
public:
    explicit ClassDefine(int i){
        iValue =i;
    }
    void PrintAllInfo(){
        cout<<iValue<<endl;
    }
};
#include "chrono"
int test(int nvalue){
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Jakie hepeng print "<<nvalue<<endl;
    return nvalue;
}


int main10(){
    function<int(int)> myFunc;
    myFunc=bind(test,placeholders::_1);
    thread tt(myFunc,1000);
    tt.join();
    ClassDefine classDefine(100);
    classDefine.PrintAllInfo();
    MapManager manager;
    manager.AddEleeent("111","hepeng");
    manager.AddEleeent("222","jackie");
    manager.QueryList();
    manager.DelElement("111");
    manager.QueryList();
    InfoManager infoManager;
    infoManager.AddStringElement("HEPENG");
    infoManager.AddStringElement("JACKIE");
    infoManager.PrintAllInfo();
    infoManager.DelEleemnt("HEPENG");
    infoManager.PrintAllInfo();
    infoManager.ModifyElement("JACKIE","hepeng");
    infoManager.PrintAllInfo();

    int a=10;
    vector<int> params{1,2,3,4,5,2,12,23,2,2};
    mutex mutex_i;
    auto func=[&](int b){
        mutex_i.lock();
            for(int i=0;i<10;i++){
                cout<<params[i]+a+b <<" ";
                params[i]+=i;
            }
            cout<<endl;
        mutex_i.unlock();
    };
    thread self[5];
    for(int i=0;i<5;i++) {
        self[i]=thread(func, 100);;
    }
    for(int i=0;i<5;i++)
      self[i].join();
}
#include <condition_variable>
using namespace std;
class PoolTest{
private:
    list<thread> myThreadPool;
    mutex mtx;
    condition_variable cv;
    bool stop;
public:

    PoolTest() {
    }
    void Action(){
        stop= false;
        for(int i=0;i<5;i++){
        myThreadPool.push_back(thread([this](){
            while(true){
                this_thread::sleep_for(chrono::seconds(1));
                unique_lock<mutex> lock(mtx);
                cout<<"Jackie hepeng print"<<endl;
                cv.wait(lock,[this](){return stop;});
                return;

            }
        }));
        }
    }
    ~PoolTest(){
        auto it =myThreadPool.begin();
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for(;it!=myThreadPool.end();it++)
            (*it).join();
    }
};

int main(){
    PoolTest pt;
    pt.Action();
    return 1;
}