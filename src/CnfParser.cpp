//
// Created by PC on 2019/2/17.
//
#include "Global.h"

HeadNode* CreateClause(int &VARNUM,string &filename) {
    //FileOpen
    string HFilePath = R"(C:\Users\PC\CLionProjects\Workshop\)";
    string path = HFilePath + filename;
    ifstream fis(path);
    if(!fis){
        cout<<"File can not open.";
        exit;
    }
    char ch;
    char buf[100];
    fis>>ch;
    while (ch != 'p') {
        fis.getline(buf,100);
        fis>>ch;
    }
    string cnf;
    int VarNum,ClauseNum;
    fis>>cnf>>VarNum>>ClauseNum;
    fis.get();

    /*and write into 2 dimensional link lists*/
    //loading the initial node
    HeadNode* HEAD = new HeadNode;
    HeadNode* headRear = HEAD;
    HeadNode* END = new HeadNode;
    for (int i = 0 ; i < ClauseNum ; i++) {
        //load on the data lists
        int temp;
        fis>>temp;
        //load the first data node
        DataNode* front = new DataNode;
        front->data = temp;
        headRear->right = front;
        headRear->Num++;
        //the >2th data loading
        fis >> temp;
        while (temp != 0) {
            DataNode* rear = new DataNode;
            front->next = rear;
            rear->data = temp;
            front = front->next;
            headRear->Num++;
            fis >> temp;
        }
        front->next = nullptr;
        fis.get();//换行符
        HeadNode *tp = new HeadNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;

    //output link lists
    HeadNode* Phead = HEAD;
    DataNode* front;
    cout<<"CnfParser\n";
    while(Phead != nullptr) {
        front = Phead->right;
        while(front != nullptr) {
            cout<<front->data<<" ";
            front = front->next;
        }
        cout<<endl;
        Phead = Phead->down;
    }

    VARNUM = VarNum;
    return HEAD;
}