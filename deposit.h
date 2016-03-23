#ifndef DEPOSIT_H_INCLUDED
#define DEPOSIT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_NODE 10
#define DEFAULT_TYPE_CNT 5

typedef enum deposit_type{one,two,three,five,alive}deposit_type;
typedef enum deposit_mode{renewal,nonrenewal}deposit_mode;

typedef struct _DepositNode{
    struct _DepositNode *next;  //next指针
    deposit_type type;      //存款方式
    double money;           //存款本金
    double rate;            //存款利率
    unsigned int year;               //存款年限
    deposit_mode mode;      //约转？不约转？
}DepositNode, *PDepositNode;

typedef struct _DepositList{
    DepositNode *head;     //链表头
    unsigned int length;    //链表成员个数
}DepositList;

DepositList* InitialDepositList(DepositList *pLst);
void InsertDepositList(DepositList *pLst, deposit_type type, double rate);
void RemoveDepositNode(DepositList *pLst, deposit_type type);
void UpdateDepositNodeByType(DepositList *pLst, deposit_type type, double *pMoney,
                             double *pRate,unsigned int *pYear, deposit_mode *pMode);
void CalcTotalMoney(DepositList *pLst, deposit_type type);
DepositNode *SearchDepositNode(DepositList *pLst, deposit_type type);
#endif // DEPOSIT_H_INCLUDED

