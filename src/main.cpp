#include "Modular/Global.h"



int main() {
    Start();
    int choice = 0;
    cin>>choice;
    while (choice){
        if(choice == 1) {
        string filename = createSudokuToFile();
        int VARNUM;
        HeadNode* LIST = CreateClause(VARNUM,filename);
        conse SudoResult[VARNUM];//记录最终的真假值
        clock_t StartTime,EndTime;
        StartTime = clock();
        int value = SudoDPLL(LIST,SudoResult,VARNUM);
        EndTime = clock();
        cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
        if(value == 1)
            SudokuShow(SudoResult,VARNUM);
        else
            cout<<"there is no anwser.";
        }

        else if (choice == 2) {//SAT
            int VARNUM;
            string filename = "sud00009.cnf";
            HeadNode* LIST = CreateClause(VARNUM,filename);
            consequence result[VARNUM];//记录最终的真假值
            clock_t StartTime,EndTime;
            //cout<<"Result: \n";
            //StartTime = clock();
            //int value = DPLL(LIST,result);
            //EndTime = clock();
            //if(value) {
            //    cout << "S " << TRUE << endl;
            //    show(result, VARNUM);//输出解
            //}
            //else {
            //    cout << "S " << NoAnwser << endl;
            //    cout<<"V "<<endl;
            //}
            //cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";

             //写到文件
             string suffix = ".res";
             string name = "solution";
             string Outputfile = name + suffix;
             ofstream fos(Outputfile);
             if(!fos.is_open()) {
                 cout<<"Can not open a new file.\n";
                 exit;
             }

            StartTime = clock();
            int value = DPLL(LIST,result);
            EndTime = clock();
            //结果
            if(value) {
                fos << "S " << TRUE << endl;
                fos<<"V ";
                for(int i = 0; i < VARNUM; i++) {
                    if (result[i].value == TRUE)
                        fos<<i+1<<" ";
                    else if(result[i].value == FALSE)
                        fos<<-(i+1)<<" ";
                    else
                        fos<<(i+1)<<" ";//剩下一堆可true可false，就索性输出true
                }
                fos<<endl;
            }
            else {
                fos << "S " << NoAnwser << endl;
                fos<<"V ";
                fos<<endl;
            }
            //时间
            fos<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
            fos.close();

        }
        else { //其他值不理睬
            cout<<"Please input the right num! ";
            exit;
        }
        choice = 0;
    }
}