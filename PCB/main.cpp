//region Description
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

class PCB{
private:
    string name = "job0";     //进程名
    string info = "ssv";   //存储的信息
    int priority= 0;//进程的优先级，数值越大，优先级越高
    string pstatus="Ready";//进程的状态


public:
    int No = 0;
    int time = 00;
    PCB(string name, string info, int priority, string pstatus, int time){
        this->info = info;
        this->name = name;
        this->priority = priority;
        this->pstatus = pstatus;
        this->time = time;
    }
    PCB(){}
    void showInfo(){
        cout<<this->name<<"      "<<this->No<<"      "<<this->info<<"       "<<this->priority<<"          "<<this->pstatus<<"       "<<this->time<<endl;
    }
    void Run(){
        this->pstatus = "Run";
    }
    void Wait(){
        this->pstatus = "waite";
    }
    void Ready(){
        this->pstatus = "Ready";
    }
    string status(){
        return this->pstatus;
    }
    int getPriority(){
        return this->priority;
    }
};

void run_up(vector<PCB> &pcb){
    int min;
    int priority=1000;
    vector<PCB>::iterator it = pcb.begin();
    for(;it!= pcb.end();it++){
        if((*it).getPriority()<priority && (*it).status() == "Ready"){
            min = (*it).No;
        }
    }
    it = pcb.begin();
    for(;it != pcb.end();it++){
        if((*it).No == min){
            (*it).Run();
        }
    }
}

bool sout(PCB a, PCB b){
    if(a.getPriority()>b.getPriority()){
        return false;
    } else{
        return true;
    }
}

void Init(vector<PCB> &ReadPCB, vector<PCB> &PCB_Pond){
    string name;     //进程名
    string info;   //存储的信息
    int priority;//进程的优先级，数值越大，优先级越高
    string pstatus;//进程的状态
    int time;
    int i=0;
    ifstream infile;
    infile.open("C:\\Users\\ck\\Desktop\\PCB\\data.dat", ios::in);
    if (!infile){
        cout<<"ss"<<endl;
        exit(0);
    }
    while (infile.peek() != EOF){
        infile>>name>>info>>priority>>pstatus>>time;
        if(PCB_Pond.size()<1){
            cout<<"the PCB_Pond is empty!"<<endl;
            return;
        }
        PCB_Pond.pop_back();
        PCB ready(name,info,priority,pstatus,time);
        ready.No = rand();
        ReadPCB.push_back(ready);
        i++;

    }
    infile.close();
    sort(ReadPCB.begin(),ReadPCB.end(),sout);
}

void fastPhoto(vector<PCB> ReadyPCB, vector<PCB> PCB_Pond){
    cout<<"=====================Ready_PCB====================="<<endl;
    cout<<"Pr_Name  "<<"Pr_No  "<<"Pr_Info  "<<"Pr_priority  "<<"Pr_pstatus  "<<"Pr_time"<<endl;
    for(int i = 0; i<ReadyPCB.size(); i++){
        if(ReadyPCB[i].status() == "Ready"){
            ReadyPCB[i].showInfo();
        }
    }
    cout<<"=====================Run_PCB====================="<<endl;

    for(int i = 0; i<ReadyPCB.size(); i++){
        if(ReadyPCB[i].status() == "Run"){
            ReadyPCB[i].showInfo();
        }
    }
    cout<<"=====================Waite_PCB====================="<<endl;
    for(int i = 0; i<ReadyPCB.size(); i++){
        if(ReadyPCB[i].status() == "waite"){
            ReadyPCB[i].showInfo();
        }
    }
    cout<<"=====================PCB_Pond====================="<<endl;
    for(int i =0; i<PCB_Pond.size(); i++){
        PCB_Pond[i].showInfo();
    }

}

void check(vector<PCB> &pcb) {
    int willrun = -1;
    int will_priority = 1000;
    vector<PCB>::iterator it = pcb.begin();
    for (; it != pcb.end();) {
        if ((*it).status() == "Run") {
            (*it).Ready();
        }
        if ((*it).getPriority() < will_priority) {
            will_priority = (*it).getPriority();
            willrun = (*it).No;
        }
        it++;
    }
    it = pcb.begin();
    for (; it != pcb.end(); ) {
        if ((*it).No == willrun) {
            (*it).Run();
            break;
        }
        it++;
    }
}

void add_Process(vector<PCB> &pcb, vector<PCB> &pcb2){
    if(pcb2.size() < 1){
        cout<<"the PCB_Pond is empty!"<<endl;
        return;
    }
    string name;     //进程名
    string info;   //存储的信息
    int priority;//进程的优先级，数值越大，优先级越高
    string pstatus;//进程的状态
    int time;
    cout<<"Input the Process name:";
    cin>>name;
    cout<<"Input the Process info:";
    cin>>info;
    cout<<"Input the Process priority:";
    cin>>priority;
    cout<<"Input the Process pstatus:";
    cin>>pstatus;
    cout<<"Input the Process time:";
    cin>>time;
    PCB o(name,info,priority,pstatus,time);
    o.No = rand();
    pcb2.pop_back();
    pcb.push_back(o);
    cout<<"add it!"<<endl;
    run_up(pcb);
    check(pcb);
    sort(pcb.begin(),pcb.end(),sout);
}

void delete_Process(vector<PCB> &pcb,vector<PCB> &pcb2){
    cout<<"Input the PID you want to delete:"<<endl;
    int PID;
    cin>>PID;
    vector<PCB>::iterator it = pcb.begin();
    for(;it != pcb.end();){
        if ((*it).No == PID){
            pcb2.push_back((*it));
            it = pcb.erase(it);
            cout<<"delete it!"<<endl;
            sort(pcb.begin(),pcb.end(),sout);
            run_up(pcb);
            check(pcb);
            return;
        } else{
            it = it+1;
        }
    }
    cout<<"can not find the PID!"<<endl;
    sort(pcb.begin(),pcb.end(),sout);
    run_up(pcb);
    check(pcb);
}

void delete_Process(vector<PCB> &pcb, int PID, vector<PCB> &pcb2){
    vector<PCB>::iterator it = pcb.begin();
    for(;it != pcb.end();){
        if ((*it).No == PID){
            pcb2.push_back((*it));
            it = pcb.erase(it);
            cout<<"delete it!"<<endl;
            sort(pcb.begin(),pcb.end(),sout);
            run_up(pcb);
            check(pcb);
            return;
        } else{
            it = it+1;
        }
    }
    cout<<"can not find the PID!"<<endl;
    sort(pcb.begin(),pcb.end(),sout);
    run_up(pcb);
    check(pcb);
}

void hang_up(vector<PCB> &pcb){
    cout<<"Input the PID:"<<endl;
    int PID;
    cin>>PID;
    vector<PCB>::iterator it = pcb.begin();
    for(;it!=pcb.end();it++){
        if((*it).No == PID){
            (*it).Wait();
            cout<<"hang up: "<<PID<<endl;
        }
    }
    sort(pcb.begin(),pcb.end(),sout);
    run_up(pcb);
    check(pcb);
}

void hang_up(vector<PCB> &pcb, int PID){
    vector<PCB>::iterator it = pcb.begin();
    for(;it!=pcb.end();it++){
        if((*it).No == PID){
            (*it).Wait();
            cout<<"hang up: "<<PID<<endl;
        }
    }
    sort(pcb.begin(),pcb.end(),sout);
}

void hang_down(vector<PCB> &pcb){
    cout<<"Input the PID:"<<endl;
    int PID;
    cin>>PID;
    vector<PCB>::iterator it = pcb.begin();
    for(;it!=pcb.end();it++){
        if ((*it).No == PID){
            if((*it).status() == "waite"){
                (*it).Ready();
            }else{
                cout<<"the process is not waite!"<<endl;
                break;
            }
        }
    }
    run_up(pcb);
    check(pcb);
}

int run(vector<PCB> &pcb, vector<PCB> &pcb2){
    int time_pice=20;
    vector<PCB>::iterator it = pcb.begin();
    for(;it!=pcb.end();it++){
        if((*it).status()=="Run"){
            break;
        }
    }
    while(time_pice){
        (*it).time--;
        time_pice --;
        if((*it).time==0){
            delete_Process(pcb,(*it).No,pcb2);
            fastPhoto(pcb,pcb2);
            return 0;
        }
    }
    hang_up(pcb,(*it).No);
    fastPhoto(pcb,pcb2);
    return 1;
}

int main() {
    srand((unsigned)time(NULL));
    vector<PCB> PCB_Queue;
    vector<PCB> PCB_pond(3);
    //cout<<PCB_pond.size();
    fastPhoto(PCB_Queue,PCB_pond);
    Init(PCB_Queue, PCB_pond);
    cout<<"1.fastPhoto\n2.add_Process\n3.delete_Process\n4.hang_up\n5.hang_down\n6.run\n#.quit"<<endl;
    char a;
    while(a!='#'){
        cout<<"input the number to choice:"<<endl;
        cin>>a;
        switch (a){
            case '1':
                fastPhoto(PCB_Queue,PCB_pond);
                break;
            case '2':
                add_Process(PCB_Queue,PCB_pond);
                break;
            case '3':
                delete_Process(PCB_Queue,PCB_pond);
                break;
            case '4':
                hang_up(PCB_Queue);
                break;
            case '5':
                hang_down(PCB_Queue);
                break;
            case '6':
                run(PCB_Queue,PCB_pond);
                break;
            default:
                fastPhoto(PCB_Queue,PCB_pond);
                break;
    }
}

}
//endregion