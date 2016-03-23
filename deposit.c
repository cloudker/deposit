#include "deposit.h"
#include "common.h"

DepositList* InitialDepositList(DepositList *pLst)
{
    pLst = (DepositList*)malloc(sizeof(DepositList));
    if(!pLst)
    {
        printf("内存不足！\n");
        exit(-1);
    }
    pLst->length = 0;
    pLst->head = NULL;

    return pLst;
}

void InsertDepositList(DepositList *pLst, deposit_type type, double rate)
{
    DepositNode *pTemp = NULL, *pNext = NULL;
    if(pLst->length == MAX_LIST_NODE)
    {
        printf("存款方式已满，插入失败！");
        return;
    }

    pTemp = (PDepositNode)malloc(sizeof(DepositNode));
    if(!pTemp)
    {
        printf("系统空间不足，插入失败！");
        return ;
    }
    pNext = NULL;

    pTemp->type = type;
    pTemp->money = 0;
    pTemp->rate = rate;
    pTemp->year = 0;
    pTemp->mode = nonrenewal;
    //头插法
    pNext = pLst->head;
    pLst->head = pTemp;
    pTemp->next = pNext;
}

void RemoveDepositNode(DepositList *pLst, deposit_type type)
{
    DepositNode *pCur = NULL, *pPrev = NULL;

    pPrev = pCur = pLst->head;

    while(pCur->type != type)
    {
        pPrev = pCur;
        pCur = pCur->next;
	if(!pCur)
		break;
    }

    if(!pCur)
    {
        printf("未找到待删除的存款方式！\n");
        return ;
    }
    pPrev->next = pCur->next;
    free(pCur);
    pLst->length--;
}

void UpdateDepositNodeByType(DepositList *pLst, deposit_type type, double *pMoney,
                             double *pRate,unsigned int *pYear, deposit_mode *pMode)
{
    DepositNode *pCur = pLst->head;
    while(pCur->type != type)
    {
        pCur = pCur->next;
	if(!pCur)
		break;
    }
  
    if(!pCur)
    {
        printf("未找到该存款方式！");
        return ;
    }
    if(pMoney)
        pCur->money = *pMoney;
    if(pRate)
        pCur->rate = *pRate;
    if(pYear)
        pCur->year = *pYear;
    if(pMode)
        pCur->mode = *pMode;
}

void CalcTotalMoney(DepositList *pLst, deposit_type type)
{
	double totalMoney = 0;
	DepositNode *p = SearchDepositNode(pLst, type);
	DepositNode *pAlive = SearchDepositNode(pLst, alive);
	if(!p)
	{
		printf("选择的存款方式已经被删除了！");
		return ;
	}
	switch(type)
	{
	case one:
		if(p->mode == renewal)
		{
			totalMoney = p->money * (1 + p->rate / 100 * p->year);					
		}else{
			if(!pAlive)
			{
				printf("不支持不约转!\n");
				break;
			}
			totalMoney = p->money * (1 + p->rate/100);
			totalMoney += totalMoney * ((p->year - 1) * pAlive->rate/100);
		}
		printf("总金额为：%lf\n\n",totalMoney);		
		break;
	case two:
		if(p->year < 2 || p->year % 2 != 0)
		{
			printf("输入年份不是2的倍数!\n");
			break;
		}
		if(p->mode == renewal)
		{
			totalMoney = p->money * (1 + p->rate / 100 * p->year);			
		}else{
			if(!pAlive)
			{
				printf("不支持不约转!\n");
				break;
			}
			totalMoney = p->money * (1 + 2 * p->rate / 100);
			totalMoney += totalMoney * ((p->year - 2) * pAlive->rate/100);
		}
		printf("总金额为：%lf\n\n",totalMoney);
		break;
	case three:
		if(p->year < 3 || p->year % 3 != 0)
		{
			printf("输入年份不是3的倍数!\n");
			break;
		}
		if(p->mode == renewal)
		{
			totalMoney = p->money * (1 + p->rate / 100 * p->year);			
		}else{
			if(!pAlive)
			{
				printf("不支持不约转!\n");
				break;
			}
			totalMoney = p->money * (1 + 3 * p->rate / 100);
			totalMoney += totalMoney * ((p->year - 3) * pAlive->rate / 100);
		}
		printf("总金额为：%lf\n\n",totalMoney);
		break;
	case five:
		if(p->year < 5 || p->year % 5 != 0)
		{
			printf("输入年份不是5的倍数!\n");
			break;
		}
		if(p->mode == renewal)
		{
			totalMoney = p->money * (1 + p->rate / 100 * p->year);			
		}else{
			if(!pAlive)
			{
				printf("不支持不约转!\n");
				break;
			}
			totalMoney = p->money * (1 + 5 * p->rate / 100);
			totalMoney += totalMoney * ((p->year - 2) * pAlive->rate / 100);
		}
		printf("总金额为：%lf\n\n",totalMoney);
		break;
	case alive:
		totalMoney = p->money * (1 + p->year * p->rate / 100);
		printf("总金额为：%lf\n\n",totalMoney);
		break;
	default:
		printf("未知错误！\n");
		break;
	}
}

DepositNode *SearchDepositNode(DepositList *pLst, deposit_type type)
{
	DepositNode *p = pLst->head;
	
	while(p->type != type)
	{
		p = p->next;
		if(!p)
		{
			return NULL;
		}
	}
	return p;
}

/*
void printDepositList(DepositList *pLst)
{
	DepositNode *p = pLst->head;
	while(p)
	{
		printf("Type:%d\n",p->type);
		printf("Money:%lf\n",p->money);
		printf("Rate:%lf\n", p->rate);
		printf("Year:%u\n", p->year);
		printf("Mode:%d\n\n\n", p->mode);
		
		p = p->next;
	}
}
*/
