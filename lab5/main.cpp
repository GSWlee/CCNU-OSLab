#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <direct.h>
using namespace std;

class UED{
private:
    string Username;
    string Password;
    vector<string> filename;
    string file[5];
    FILE * it[5]={0};
public:
    UED() = default;;
    UED(string name, string pass){
        this->Password=pass;
        this->Username=name;
    }
    void Open(){//打开文件
        string name;
        int n;
        int flag = -1;
        cout<<"Input the file name"<<endl;
        cin>>name;
        for(n=0; 5 > n; n++){
            if(!this->it[n]){
                flag = 0;
                break;
            }
        }
        if(flag==-1){
            cout<<"this is not space to open file;"<<endl;
            return;
        }
        this->file[n]=name;
        this->it[n]=fopen((this->Username+"\\"+name).c_str(),"w+");
        if(this->it[n]==0){
            cout<<"open file failed;"<<endl;
            return;
        }else{
            cout<<"open success!"<<endl;
            return;
        }
    }
    bool open(string name){//打开文件
        //fstream file;
        int n;
        int flag = -1;
        for(n=0; 5 > n; n++){
            if(this->it[n]){
                flag = 0;
                break;
            }
        }
        if(flag==-1){
            cout<<"this is not space to open file;"<<endl;
            return false;
        }
        this->file[n]=name;
        this->it[n]=fopen((this->Username+"\\"+name).c_str(),"w+");
        if(!this->it[n]){
            cout<<"open file failed;"<<endl;
            return false;
        } else{
            return true;
        }
    }
    bool Check(string name){
        vector<string>::iterator it;
        for(it=this->filename.begin();it!=this->filename.end();it++){
            if(*it==name){
                return true;
            }
        }
        return false;
    }
    void Creat(){//创建文件
        string name;
        fstream file;
        cout<<"Input the file name"<<endl;
        cin>>name;
        if(Check(name)){
            cout<<"file exist"<<endl;
            return;
        }
        this->filename.push_back(name);
        name = this->Username+"\\"+name;
        FILE * fp=fopen(name.c_str(),"w+");
        if(fp){
            cout<<"create success!"<<endl;
            fclose(fp);
            return;
        }else{
            cout<<"create failed;"<<endl;
            fclose(fp);
            return;
        }
    }
    void CloseO(){//关闭单个文件
        string filename;
        cout<<"Input the file name"<<endl;
        cin>>filename;
        int q=0;
        for(int i=0;i<5;i++){
            if(this->file[i]==filename){
                this->file[i]="";
                q=i;
                break;
            }
        }
        if (this->it[q]!=0){
            fclose(this->it[q]);
            this->it[q]=0;
            return;
        } else{
            cout<<"the file is closed!"<<endl;
            return;
        }
    }
    void Close(){
        for(int i=0;i<5;i++){
            if (this->it[i]!=0) {
                fclose(this->it[i]);
                this->it[i]=0;
            }else{
                cout<<"closed file["<<i<<"]"<<endl;
                continue;
            }
        }
    }
    void Delete(){
        cout<<"Input the filename:"<<endl;
        string str;
        cin>>str;
        int t = -1;
        for(int i=0;i<this->filename.size();i++){
            if(this->filename[i]==str){
                this->filename.erase(this->filename.begin()+i);
                t=0;
                break;
            }
        }
        str = this->Username+"\\"+str;
        if(t==0){
            if (remove(str.c_str())==0){
                cout<<"removed"<<endl;
            } else{
                cout<<"remove failed"<<endl;
            }
        }else{
            cout<<"remove failed"<<endl;
        }

    }
    void Write(){
        cout<<"Input the file name:"<<endl;
        string filename;
        cin>>filename;
        cout<<"input the context:"<<endl;
        string cont;
        cin>>cont;
        int t=-1;
        int empy=-1;
        for(int i=0;i<5;i++){
            if(this->file[i]==filename){
                t=i;
                break;
            }else if(!this->it[i]){
                empy=i;
            }
        }
        if(t==-1 && empy!=-1){
            cout<<"this file is not open"<<endl;
            this->file[empy]=filename;
            filename=this->Username+"//"+filename;
            this->it[empy]=fopen(filename.c_str(),"w");
            if(this->it[empy]){
                fputs("ssss",this->it[empy]);
                cout<<"complete"<<endl;
                //fclose(this->it[empy]);
                return;
            } else{
                cout<<"open faild"<<endl;
                //fclose(this->it[empy]);
                return;
            }
        }  else if(t!=-1){
            fputs(cont.c_str(),this->it[t]);
            cout<<"complete"<<endl;
            return;
        }else{
            cout<<"YOU can not open a file, there is not empty ptr! please try to close one!"<<endl;
            return;
        }
    }
    void Read(){
        string filename;
        char cont[100];
        cout<<"input the filename:"<<endl;
        cin>>filename;
        int t=-1;
        int empy=-1;
        for(int i=0;i<5;i++){
            if(this->file[i]==filename){
                t=i;
                break;
            }else if(!this->it[i]){
                empy=i;
            }
        }
        if(t==-1 && empy!=-1){
            cout<<"this file is not open, open it by "<<empy<<endl;
            this->file[empy]=filename;
            filename = this->Username+"\\"+filename;
            this->it[empy]=fopen(filename.c_str(),"r");
            if( this->it[empy]){
                fgets(cont,100,this->it[empy]);
                cout<<"complete"<<endl;
                cout<<"> "<<cont<<endl;
                return;
            }else{
                cout<<"open faild"<<endl;
                return;
            }
        } else if(t!=-1){
           fgets(cont,100,this->it[t]);
            cout<<"complete"<<endl;
            cout<<"> "<<cont<<endl;
            return;
        }else{
            cout<<"YOU can not open a file, there is not empty ptr! please try to close one!"<<endl;
            return;
        }
    }
    void Show(){
        cout<<"file:"<<endl;
        for(auto it=this->filename.begin(); this->filename.end() != it; it++){
            cout<<(*it)<<endl;
        }
        cout<<"opening file:"<<endl;
        for(int i=0;i<5;i++){
            if(this->it[i]!=0){
                cout<<this->file[i]<<endl;
            }
        }
    }
    string name(){
        return this->Username;
    }
    string pass(){
        return this->Password;
    }
};

class MFD{
private:
    vector<UED> ma;
public:
    void add(){
        string name;
        string pass;
        cout<<"input your name:"<<endl;
        cin>>name;
        cout<<"input your password:"<<endl;
        cin>>pass;
        UED a(name,pass);
        ma.push_back(a);
        int flag=mkdir(name.c_str());
        if(flag==0){
            cout<<"add success!"<<endl;
        } else{
            cout<<"add failed"<<endl;
        }
    }
    void de(){
        string name;
        cout<<"Input the name:"<<endl;
        cin>>name;
        for(int i =0;i<ma.size();i++){
            if(ma[i].name()==name){
                ma.erase(ma.begin()+i);
                cout<<"delete success!"<<endl;
                break;
            }
        }
        rmdir(name.c_str());
    }
    void show(){
        cout<<"user:"<<endl;
        for(auto &i : this->ma){
            cout<<i.name()<<endl;
        }
    }
    void login(){
        string name;
        string pass;
        cout<<"Username:";
        cin>>name;
        cout<<"Password:";
        cin>>pass;
        vector<UED>::iterator it;
        for(it=ma.begin();it!=ma.end();it++){
            if((*it).name()==name){
                break;
            }
        }
        if((*it).pass()==pass){
            cout<<"login success"<<endl;
            char s='0';
            cout<<"0. show all file"<<endl;
            cout<<"1. Create file"<<endl;
            cout<<"2. Open file"<<endl;
            cout<<"3. Close file"<<endl;
            cout<<"4. Read file"<<endl;
            cout<<"5. Write file"<<endl;
            cout<<"6. Delete file"<<endl;
            cout<<"#. exit"<<endl;
            while(s!='#'){
                cin>>s;
                switch (s){
                    case '0': (*it).Show();
                        break;
                    case '1': (*it).Creat();
                        break;
                    case '2': (*it).Open();
                        break;
                    case '3': (*it).CloseO();
                        break;
                    case '4': (*it).Read();
                        break;
                    case '5': (*it).Write();
                        break;
                    case '6': (*it).Delete();
                        break;
                    default:(*it).Show();
                }
;
            }
            (*it).Close();
        }
    }
};

int main() {
    MFD s;
    char q = '0';
    cout<<"0. show all user"<<endl;
    cout<<"1. add user"<<endl;
    cout<<"2. delete user"<<endl;
    cout<<"3. login"<<endl;
    cout<<"#. exit"<<endl;
    while (q != '#'){
        cin>>q;
        switch (q){
            case '0': s.show();
                break;
            case '1': s.add();
                break;
            case '2': s.de();
                break;
            case '3': s.login();
                break;
            default:s.show();
        }
}
}