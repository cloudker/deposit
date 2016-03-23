#include "common.h"
#include "deposit.h"

const char Login_Password[10] = "88888888";
//global
DepositList *g_lst = NULL;

int login()
{
	int IF_Pass = 3;
	char UserEnter_password[10];

	do
	{
		printf("请输入登入口令,您还有%d次机会:",IF_Pass);
		scanf("%s",UserEnter_password);
		if(strcmp(Login_Password,UserEnter_password) != 0)
		{
			IF_Pass--;
		}
		else
		{
			printf("密码正确!登录成功!\n");
			return 0;
		}
	}while(IF_Pass != 0);

	return -1;
}

void ShowInfo()
{
    printf("\n\n");
    printf("/************请选择菜单************/\n");
    printf("    ①  初始化存款利率  \n");
    printf("    ②  输入存款事宜，计算存款总额    \n");
    printf("    ③  修改存款利率  \n");
    printf("    ④  移除存款方式  \n");
    printf("    ⑤  退出    \n");
    printf("/***********************************\n");
    printf("请选择:");
}

void Menu()
{
	char MenuIF[256];
    int i, bFlag = 0;
    double rate, money;
    unsigned int year;
    deposit_mode mode;
    char input[256];
    deposit_type typeArray[DEFAULT_TYPE_CNT] = {one, two, three, five, alive};
    char typeArrayStr[DEFAULT_TYPE_CNT][64] = {"一年定期", "两年定期", "三年定期", "五年定期", "活期"};

	do
	{
	    ShowInfo();
		memset(MenuIF, 0, sizeof(MenuIF));
		scanf("%s",MenuIF);
		if(strlen(MenuIF) != 1)
        {
            printf("输入无效，请重试！\n");
            continue;
        }
		switch(MenuIF[0])
		{
			case '1':
			    printf("初始化以下5种存款方式利率：\n");
                g_lst = InitialDepositList(g_lst);
                for(i=0;i<DEFAULT_TYPE_CNT;i++)
                {
                    printf("存款方式：%s\n请输入利率：(如3.5)", typeArrayStr[i]);
                    scanf("%lf", &rate);
                    InsertDepositList(g_lst, typeArray[i], rate);
                }
                printf("初始化完毕！\n");
                bFlag = 1;
			    break;
			case '2':
			    if(!bFlag)
                {
                    printf("请先初始化！\n");
                    break;
                }
                printf("请输入想要选择的存款方式：\n");
                printf("1:一年定期\n");
                printf("2:两年定期\n");
                printf("3:三年定期\n");
                printf("4:五年定期\n");
                printf("5:活期\n");
                scanf("%s", MenuIF);
                if(strlen(MenuIF) != 1)
                {
                    printf("无效的操作！\n");
                    break;
                }
                printf("请输入本金：");
                scanf("%lf",&money);
                printf("请输入存款时间（单位: 年）:");
                scanf("%d",&year);
                printf("请输入是否采用约转模式：(Y/N)");
                scanf("%s",input);
                input[0] &= 0xdf;
                if(input[0] == 'Y')
                    mode = renewal;
                else
                    mode = nonrenewal;
                UpdateDepositNodeByType(g_lst, typeArray[atoi(MenuIF)-1], &money, NULL, &year, &mode);
		CalcTotalMoney(g_lst, typeArray[atoi(MenuIF)-1]);
			    break;
            case '3':
                if(!bFlag)
                {
                    printf("请先初始化！\n");
                    break;
                }
                printf("请输入想要改变利率的存款方式：\n");
                printf("1:一年定期\n");
                printf("2:两年定期\n");
                printf("3:三年定期\n");
                printf("4:五年定期\n");
                printf("5:活期\n");
                scanf("%s", MenuIF);
                if(strlen(MenuIF) != 1)
                {
                    printf("无效的操作！\n");
                    break;
                }
                printf("请输入新的利率：");
                scanf("%lf", &rate);
                UpdateDepositNodeByType(g_lst, typeArray[atoi(MenuIF)-1], NULL, &rate,
                                        NULL, NULL);
                //CalcTotalMoney(pLst, typeArray[atoi(MenuIF)-1]);
                break;
            case '4':
                if(!bFlag)
                {
                    printf("请先初始化！\n");
                    break;
                }
                printf("请输入想要删除的存款方式：\n");
                printf("1:一年定期\n");
                printf("2:两年定期\n");
                printf("3:三年定期\n");
                printf("4:五年定期\n");
                printf("5:活期\n");
                scanf("%s", MenuIF);
                if(strlen(MenuIF) != 1)
                {
                    printf("无效的操作！\n");
                    break;
                }
		if(atoi(MenuIF) == 5)
		{
			printf("不允许删除活期!\n");
			break;
		}
                RemoveDepositNode(g_lst, typeArray[atoi(MenuIF)-1]);
                break;
			case '5':
				printf("\n退出程序···\n");
				exit(0);
			default:
				printf("输入无效，请重试！\n");
				break;
		}
	}while(1);
}

