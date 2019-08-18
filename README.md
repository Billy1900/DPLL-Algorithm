# DPLL-Algorithm
An algorithm to solve SAT problem


## 系统总体设计


## 系统总流程

![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/1.png)
 
## 模块功能描述

1.Start模块：输出提示词，提示用户输入参数进行选择，输入1进入数独模块，输入2进入SAT问题模块。

2.CnfParser模块：读取后缀为.cnf的文件数据，将文件中的变元数和子句数提取出来保存，将每个子句保存入设定好的数据结构中，并将每个子句末尾的0丢弃。保存成功后，遍历输出结果人工与文件内容比对观察是否正确读取。

3.DPLLSolver模块：该模块主要实现DPLL算法框架，是本程序的核心框架。该算法计算cnf公式的变元真假值并将结果记录下来。若cnf文件中的算例有解的话，就会返回TRUE，将变元的结果输出；若算例无解返回FALSE，不输出结果。

4.Sudoku模块：该模块是数独模块。首先使用挖洞法生成数独终盘，再挖洞生成数独初盘。将数独初盘转化成SAT问题，即将其转换成CNF公式输入到.Cnf文件中，并将文件名返回main函数中。在经过CnfParser模块解析文件后，使用该模块中的SudokuDPLL函数计算出数独的结果并输出。
 
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/2.2.png)
 

## 系统详细设计


## 数据结构定义


1）子句头节点定义：

<pre>typedef struct HeadNode {
    
    int Num = 0;
    
    DataNode *right{};
    
    HeadNode *down{};

}HeadNode;
</pre>
子句头节点有三个成员；Num记录该行子句的数据个数，指针right指向到子句第一个数据节点，指针down指向到下一行子句。

2）子句数据节点定义：

<pre>typedef struct DataNode {
    
    int data = 0;
    
    DataNode *next{};

}DataNode;</pre>

数据节点有两个成员；data记录该数据节点的值，指针next指向下一个数据节点。

3）存储真值结构定义：

<pre>struct consequence {
    
    int value = -1;//存真值 真时为true-1，假时为false-0

};</pre>

value存入数组的某一元素的真值；若为真，value = 1；若为假，value = 0。

4）存储数独真值结构定义：

<pre>struct conse {
    
    int num = 0;
    
    int value = -1;//存真值 真时为true-1，假时为false-0

};</pre>

结构体conse有两个成员；num存储数独转换为cnf公式的数值，value存储真值；若为真，value = 1；若为假，value = 0。

5）系统总体存储结构关系

主要运用结构体HeadNode和DataNode存储数据，根据两种结构体的数据成员，下图展示出结构体之间的逻辑关系。
 
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.1.png)

## 主要算法设计


## CnfParser模块


该模块主要功能是将cnf文件中的数据读取出来并将它存储到数据结构中。根据文件的特点，现做如下算法设计。算法流程如下图：
 
 ![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.2.png)

## DPLLSolver模块
<pre>

DPLL算法思想如下：

Status DPLL( S) {

/* S为公式对应的子句集。若其满足，返回TURE；否则返回FALSE. */

while(S中存在单子句) { 

在S中选一个单子句L，并将单子句装入结果数组，value置为1；

依据单子句规则，利用L化简S；

if S = Φ return(TRUE);

else if (S中有空子句 ) return（FALSE）；

}

V = S第一个数据节点数值

if DPLL（S ∪v ）return(TURE);

return DPLL(S ∪¬v);

}</pre>

1）HeadNode*  IsSingleClause（HeadNode*）函数：寻找是否存在单子句。遍历头节点，若任意一行的Num存在为1的情况，即证明存在单子句，并返回单子句的指针。

2）void DeleteHeadNode(HeadNode* des, HeadNode* &src) 函数：在src指向的子句集中删掉des子句。此处应用了src的引用指针变量。

3）void DeleteDataNode(int data.HeadNode*&src) 函数：在src指向的子句集中若有节点的数值与data相等，则删除该变元所在的子句；若只是绝对值相等，则删除该变元。

4）status IsEmptyClause(HeadNode* src)函数：判断src函数中是否存在空子句，即遍历头节点，若存在头节点不为空且Num值为0的，即表示存在空子句，返回TRUE；否则，返回FALSE。

5）HeadNode* ADDSingleClause(HeadNode* src,int Var)函数：将变元Var装载成为单子句，并将该单子句装载到src的子句集中，依照函数内容，该单子句始终添加到头节点，最终返回头节点指针。

6）HeadNode* Duplication(HeadNode* src)函数：将src所指向的子句集复制一个副本，并将副本的头指针返回。

## Sudoku模块


该模块功能是①创建数独终盘，②通过挖洞法创建数独初盘，○3将数独初盘转换成SAT问题并转换成cnf公式输出到文件，并返回文件名。

1）CreateSudoku模块：

伪代码如下：

<pre>void createSudoku(int a[][COL]) { //生成数独
    
    randomFirstRow(a[0],COL);//随机生成第一行
    
    Digit(a,1,0);//递归生成后i行

}
</pre>
randomFirstRow函数算法流程：
 
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.3.png)

Digit函数算法流程：
 
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.4.png)

2）数独初盘生成模块
createStartinggrid函数算法流程：
 
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.5.png)

3）数独问题转换为SAT问题

ToCnf函数模块：

以下为函数算法说明：
![image](https://github.com/Billy1900/DPLL-Algorithm/blob/master/pic/3.6.png)
