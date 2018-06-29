//
//  main.c
//  Closed Hashing (Open Addressing)
//
//  Created by Claire on 2018/6/29.
//  Copyright © 2018年 Claire. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

enum kind_of_entry{legitimate,empty,deleted};         //hash表是个结构数组，每个cell内加了一个枚举标识状态
struct hash_entry {
    int element;
    enum kind_of_entry info;
};

typedef struct hash_entry cell;

struct hash_table{
    int tablesize;
    cell * pcell;
//是个数组
};

typedef  struct hash_table *Hash_Table;
Hash_Table initialize_table(int tablesize);
int func(int a);                        //干扰函数，这里用的是线性
int Hash(int a,int tablesize);          //正常的散列函数
int hash(int Hash_,int func,int tablesize);        //加了干扰后的散列函数
int find(int value,Hash_Table HT,int tablesize);
void insert(Hash_Table HT,int value,int tablesize);
void delete(int value,Hash_Table HT,int tablesize);




//根据大小建立一个表
Hash_Table initialize_table(int tablesize){
    Hash_Table HT=malloc(sizeof(struct hash_table));
    (*HT).tablesize=tablesize;
//    next_prime(tablesize);
    (*HT).pcell=malloc(sizeof(cell)*(*HT).tablesize);
    for (int i=0; i<tablesize; i++) {
        (*HT).pcell[i].info=empty;
    }
    return HT;
}
//线性函数function        首项是0
int func(int a){
    return a;
}
//把元素映射成值，处理后返回key
int Hash(int a,int tablesize){
    return a%tablesize;
}

int hash(int Hash_,int func,int tablesize){
    return Hash_*func%tablesize;
}

//find 每次重定向后对比值，最终返回所在位置或最后找到的空位置
int find(int value,Hash_Table HT,int tablesize){
    for (int i=0;; i++) {
        int hash_=hash(Hash(value,tablesize),func(i),tablesize);
        if((*HT).pcell[hash_].info==empty) {
            return hash_;
        }
        else{
            if ((*HT).pcell[hash_].element==value) {
                return hash_;
            }
        }
    }
}

//先查找
void insert(Hash_Table HT,int value,int tablesize){
    int a=find(value, HT, tablesize);
    if ((*HT).pcell[a].info!=legitimate) {
        (*HT).pcell[a].element=value;
        (*HT).pcell[a].info=legitimate;
    }
}

//delete  先查找
void delete(int value,Hash_Table HT,int tablesize) {
    int a=find(value,HT,tablesize);
    if ((*HT).pcell[a].info==legitimate) {
        (*HT).pcell[a].info=deleted;
    }
}



int main(void) {
    int str[10]={1,21,2,35,6,8,9,5,6,2};
    Hash_Table HT= initialize_table(13);
//  元素挨个填充到表中
    for (int i=0;i<10;i++) {
        insert(HT,str[i],13);
    }
    delete(21,HT,13);
    insert(HT,21,13);
    for (int i=0; i<13; i++) {
        if ((*HT).pcell[i].info==legitimate) {
            printf("%d  \n",(*HT).pcell[i].element);
        }
    }
//    printf("%d",)
}























