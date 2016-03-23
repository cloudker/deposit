#include "common.h"
#include "deposit.h"

int main()
{
	system("Color 0A");
//	system("start Refrain.mp3");
	if(login() == -1)
	{
		printf("登录失败,退出程序!\n");
		exit(0);
	}
	Menu();
	return 0;
}




