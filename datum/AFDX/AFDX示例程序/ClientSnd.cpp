 /* ClientSnd.c  AFDX-ES send test application*/

/* 
 * Copyright 2010, ACTRI.
 *
 * All rights reserved.  No part of this software may
 * be published, distributed, translated or otherwise
 * reproduced by any means or for any purpose without
 * the prior written consent of ACTRI.
 * 
 */


/*
 *Revision History(Modification history)
 *--------------------------------------
 *rev. 0.01 2010-11-9, BaiYang created.
 */

/*includes(standard header file)  */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "afdxLib.h"
#include "CfgTable.h"
#include "afdxQportLib.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "afdxDrvLib.lib")
/* Macro */
#define BUF_LEN 50
#define DELAY 100


/***************************** globals ****************************/




/* initCfg - Cofiguration Load function.
 *
 * Description:
 *     The function loads configuration information for ES which print “load cfg successful” if succeed,
 * else print “load cfg error”. No return value.
 *
 * Parameters:
 *     No.
 * Return:
 *     No.
 *
*/
void  initCfg()
{
	printf("\nBegin load.....\n");    /* load configuration table */
	if(AFDX_ES_TAB.ESNum == 1)			//AFDX_ES_TAB.ESNum设置系统安装的板卡数
	{
		if(loadCfg(escfg,0)!=0)
		{
			printf("es1 load cfg error\n");		
		}
		else
		{
			printf("\nes1 nload cfg successful!\n");
		}
	}
	else if(AFDX_ES_TAB.ESNum == 2)
	{
		if(loadCfg(escfg,0)!=0)							//加载1号板卡的配置表
		{
			printf("es1 load cfg error\n");		
		}
		else
		{
			printf("\nes1 nload cfg successful!\n");
		}
		if(loadCfg(escfg,1)!=0)							//加载2号板卡的配置表
		{
			printf("es2 load cfg error\n");		
		}
		else
		{
			printf("\nes2 nload cfg successful!\n");
		}
	}
}

 /* main - Main data send function。
 *
 * Description:
 *     The function implement entire process of message sending, including 
 * configuration load, ES initialization, port creation and message send. 
 *
 * Parameters:
 *     No.
 *
 * Return:
 *     No.
*/

int main()
{
	//以下portid均有配置表(CfgTable.h)中给出
	unsigned int Ssndportid = 3;			//发送采样端口
	unsigned int Srcvportid = 6;			//接收采样端口
	unsigned int Qsndportid = 2;			//发送队列端口	
	unsigned int Qrcvportid = 5;			//接收队列端口
	unsigned int SAPsndportid = 1;			//发送SAP端口	
	unsigned int SAPrcvportid = 4;			//接收SAP端口


	char data_S[BUF_LEN] = {"0SAMPLING"};	
	char data_Q[BUF_LEN] = {"0QUEUING"};
	char data_SAP[BUF_LEN] = {"0SAP"};


	char data2[BUF_LEN] = {""};
	char data3[BUF_LEN] = {""};
	unsigned int datalen = BUF_LEN;
	unsigned int RefreshFlag = 1;
	int timeStamp = 12;

	unsigned int ip_dst;
    unsigned short udp_dst;
	unsigned int ip_src;
    unsigned short udp_src;

	int flag = 0;

	int Snd_count_S = 0;
	int Snd_count_Q = 0;
	int Snd_count_SAP = 0;
	int Rcv_count_S = 0;
	int Rcv_count_Q = 0;
	int Rcv_count_SAP = 0;

	ip_dst = inet_addr_afdx("224.224.0.45");				//组播目的地址
    ip_dst = ReverseUInt(ip_dst);
		
    udp_dst = htons(1024);									//UDP端口，板卡1、2的收发目的端口均为1024
    udp_dst = ReverseUShort(udp_dst);

	ip_src = inet_addr_afdx("224.224.0.45");				//组播源地址
    ip_src = ReverseUInt(ip_src);
	
    udp_src = htons(1024);
    udp_src = ReverseUShort(udp_src);						//UDP端口，板卡1、2的收发源端口均为1024

	unsigned int iBuff;

	printf("AFDX单卡串行收发测试程序(DeltaT = %d)……\n\n", DELAY);
	Sleep(DELAY);
	afdxPortLibInit();												//AFDX板卡库初始化
    initCfg();														//加载板卡配置表，配置板卡
	while(true)
	{
		/******************Sampling 端口发送示例********************/
		flag = afdxComPortSndMsg(Ssndportid, data_S, datalen);		//发送50个字符
		if(flag == 0)
		{	
			Snd_count_S++;											//发送成功，计数器+1
			if((Snd_count_S) % 1 == 0)								//每两次显示一次	
			{
				printf("\nSampling port: %d data send succuess!\n", Snd_count_S);//显示采样端口成功发送包的个数
				for(iBuff = 0; iBuff < datalen; iBuff++)      /* print sended frame */
				{
					printf("%c",data_S[iBuff]);						//显示发送数据
				}
				printf("\n");
			}
		}
		else
		{
// 			printf("Sampling Send failed!\n");
			switch(flag)
			{
			case 2:
				printf("Sampling 端口发送错误：portid非法!\n");
				break;
			case 5:
				printf("Sampling 端口发送错误：端口库没有初始化!\n");
				break;
			case 7:
				printf("Sampling 端口发送错误：发送数据超长!\n");
				break;
			case 8:
				printf("Sampling 端口发送错误：缓冲区满!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/******************Sampling 端口接收示例***********************/
		flag = afdxComPortRcvMsg(Srcvportid, data2, &datalen, &RefreshFlag, &timeStamp);	
		if(flag == 0)
		{
			Rcv_count_S++;											//接收成功，计数器+1
			if((Rcv_count_S) % 1 == 0)
			{
				printf("\nSampling port: %d data receive succuess!\n",Rcv_count_S);
				for(iBuff = 0; iBuff < datalen; iBuff++)      /* print received frame */
				{
					printf("%c",data2[iBuff]);
				}
				printf("\n");
			}
		}
		else
		{
			//printf("Sampling Receive failed!\n");
			switch(flag)
			{
			case 2:
				printf("Sampling 端口接收错误：portid非法!\n");
				break;
			case 4:
				printf("Sampling 端口接收错误：端口没数据!\n");
				break;
			case 5:
				printf("Sampling 端口接收错误：端口库没有初始化!\n");
				break;
			case 6:
				printf("Sampling 端口接收错误：队列端口曾经溢出!\n");
				break;
			}
			getch();
		}
		strcpy(data2, data3); /*接收存放数组清零*/
		Sleep(DELAY);


		/************************Queueing 端口发送示例**********************/
		flag = afdxComPortSndMsg(Qsndportid, data_Q, datalen);
		if(flag == 0)
		{
			Snd_count_Q++;
			if((Snd_count_Q) % 1 == 0)
			{
				printf("\nQueuing port: %d data send succuess!\n",Snd_count_Q);
				for(iBuff = 0; iBuff < datalen; iBuff++)      /* print sended frame */
				{
					printf("%c",data_Q[iBuff]);
				}
				printf("\n");
			}
		}
		else
		{
			//printf("Queuing Send failed!\n");
			switch(flag)
			{
			case 2:
				printf("Queueing 端口发送错误：portid非法!\n");
				break;
			case 5:
				printf("Queueing 端口发送错误：端口库没有初始化!\n");
				break;
			case 7:
				printf("Queueing 端口发送错误：发送数据超长!\n");
				break;
			case 8:
				printf("Queueing 端口发送错误：缓冲区满!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/************************Queueing 端口接收示例********************/
		flag = afdxComPortRcvMsg(Qrcvportid, data2, &datalen, &RefreshFlag, &timeStamp);	
		if(flag == 0)
		{
			Rcv_count_Q++;
			if((Rcv_count_Q) % 1 == 0)
			{
				printf("\nQueuing port: %d data receive succuess!\n", Rcv_count_Q);
				for(iBuff = 0; iBuff < datalen; iBuff++)      /* print received frame */
				{
					printf("%c", data2[iBuff]);
				}
				printf("\n");
			}
		}
		else
		{
			//printf("Queuing Receive failed!\n");
			switch(flag)
			{
			case 2:
				printf("Queueing 端口接收错误：portid非法!\n");
				break;
			case 4:
				printf("Queueing 端口接收错误：端口没数据!\n");
				break;
			case 5:
				printf("Queueing 端口接收错误：端口库没有初始化!\n");
				break;
			case 6:
				printf("Queueing 端口接收错误：队列端口曾经溢出!\n");
				break;
			}
			getch();
		}
// 		strcpy(data2, data3); /*接收存放数组清零*/
		Sleep(DELAY);

		/**********************SAP 端口发送示例********************/
		flag = afdxSAPPortSndMsg(SAPsndportid, data_SAP, datalen, ip_dst, udp_dst);	
		if(flag == 0)
		{
			Snd_count_SAP++;
			if((Snd_count_SAP)%1==0)
			{
				printf("\nSAP port: %d data send succuess!\n",Snd_count_SAP);
				for(iBuff=0;iBuff<datalen;iBuff++)      /* print sended frame */
				{
					printf("%c",data_SAP[iBuff]);
				}
				printf("\n");
			}
		}
		else
		{
// 			printf("SAP Send failed!\n");
			switch(flag)
			{
			case 2:
				printf("SAP 端口发送错误：portid非法!\n");
				break;
			case 4:
				printf("SAP 端口发送错误：端口没数据!\n");
				break;
			case 5:
				printf("SAP 端口发送错误：端口库没有初始化!\n");
				break;
			case 8:
				printf("SAP 端口发送错误：缓冲区满!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/*******************SAP 端口接收示例******************/
		flag = afdxSAPPortRcvMsg(SAPrcvportid, data2, &datalen, &ip_src, &udp_src);	
		if(flag == 0)
		{
			Rcv_count_SAP++;
			if((Rcv_count_SAP)%1==0)
			{
				printf("\nSAP port: %d data receive succuess!\n",Rcv_count_SAP);
				for(iBuff=0;iBuff<datalen;iBuff++)      /* print received frame */
				{
					printf("%c",data2[iBuff]);
				}
				printf("\n");
			}
		}
		else
		{
//			printf("SAP Receive failed!\n");
			switch(flag)
			{
			case 2:
				printf("SAP 端口接收错误：portid非法!\n");
				break;
			case 4:
				printf("SAP 端口接收错误：端口没数据!\n");
				break;
			case 5:
				printf("SAP 端口接收错误：端口库没有初始化!\n");
				break;
			case 6:
				printf("SAP 端口接收错误：消息曾经溢出!\n");
				break;
			}
			getch();
		}
// 		strcpy(data2, data3); /*接收存放数组清零*/
		Sleep(DELAY);
	}
    return 0;
}								

/************************************************附****注***********************************************
1. 该测试程序用于测试"自环"状态下数据的发送与接收;

2. 如果只需要测试发送, 将接收用例注释掉即可, 如果只需要测试接收, 将发送注释掉即可;

3. flag 的返回值所代表的意义

(1) Sampling 和 Queueing 端口发送示例中的flag参数 是 afdxComPortSndMsg() 函数的返回值,意义如下:
	0: 发送成功;
	2: portid非法;
	5: 端口库没有初始化;
	7: 发送数据超长;
	8: 缓冲区满;

(2) Sampling 和 Queueing 端口接收示例中的flag参数 是 afdxComPortRcvMsg() 函数的返回值,意义如下:
	0: 发送成功;
	2: portid非法;
	3: 缓冲区长度不够;
	4: 端口无数据;
	5: 端口库没有初始化;
	6: 队列端口曾经溢出;

(3) SAP 端口发送示例中的flag参数 是 afdxSAPPortSndMsg 函数的返回值,意义如下:
	0: 发送成功;
	2: portid非法;
	4: 端口没数据;
	5: 端口库没有初始化;
	8: 缓冲区满;

(4) SAP 端口接收示例中的flag参数 是 afdxSAPPortRcvMsg 函数的返回值,意义如下:
	0: 发送成功;
	2: portid非法;
	3: 缓冲区长度不够;
	4: 端口无数据;
	5: 端口库没有初始化;
	6: 消息曾经溢出;
	
4. loadCfg()函数返回值代表意义
	0: 初始化配置成功;
	1: 配置表中无ES配置信息或者端口配置信息;
	2: 端口中最大消息长度，大于该端口使用的VL中的Smax值;
	3: 端口配置表信息中没有找到相应的VL;
	4: 队列端口已生成;
	5: ES配置为空;
	6: 端口类型配置错误;
*******************************************************************************************************/