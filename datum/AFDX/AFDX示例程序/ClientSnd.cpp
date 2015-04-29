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
 *     The function loads configuration information for ES which print ��load cfg successful�� if succeed,
 * else print ��load cfg error��. No return value.
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
	if(AFDX_ES_TAB.ESNum == 1)			//AFDX_ES_TAB.ESNum����ϵͳ��װ�İ忨��
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
		if(loadCfg(escfg,0)!=0)							//����1�Ű忨�����ñ�
		{
			printf("es1 load cfg error\n");		
		}
		else
		{
			printf("\nes1 nload cfg successful!\n");
		}
		if(loadCfg(escfg,1)!=0)							//����2�Ű忨�����ñ�
		{
			printf("es2 load cfg error\n");		
		}
		else
		{
			printf("\nes2 nload cfg successful!\n");
		}
	}
}

 /* main - Main data send function��
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
	//����portid�������ñ�(CfgTable.h)�и���
	unsigned int Ssndportid = 3;			//���Ͳ����˿�
	unsigned int Srcvportid = 6;			//���ղ����˿�
	unsigned int Qsndportid = 2;			//���Ͷ��ж˿�	
	unsigned int Qrcvportid = 5;			//���ն��ж˿�
	unsigned int SAPsndportid = 1;			//����SAP�˿�	
	unsigned int SAPrcvportid = 4;			//����SAP�˿�


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

	ip_dst = inet_addr_afdx("224.224.0.45");				//�鲥Ŀ�ĵ�ַ
    ip_dst = ReverseUInt(ip_dst);
		
    udp_dst = htons(1024);									//UDP�˿ڣ��忨1��2���շ�Ŀ�Ķ˿ھ�Ϊ1024
    udp_dst = ReverseUShort(udp_dst);

	ip_src = inet_addr_afdx("224.224.0.45");				//�鲥Դ��ַ
    ip_src = ReverseUInt(ip_src);
	
    udp_src = htons(1024);
    udp_src = ReverseUShort(udp_src);						//UDP�˿ڣ��忨1��2���շ�Դ�˿ھ�Ϊ1024

	unsigned int iBuff;

	printf("AFDX���������շ����Գ���(DeltaT = %d)����\n\n", DELAY);
	Sleep(DELAY);
	afdxPortLibInit();												//AFDX�忨���ʼ��
    initCfg();														//���ذ忨���ñ����ð忨
	while(true)
	{
		/******************Sampling �˿ڷ���ʾ��********************/
		flag = afdxComPortSndMsg(Ssndportid, data_S, datalen);		//����50���ַ�
		if(flag == 0)
		{	
			Snd_count_S++;											//���ͳɹ���������+1
			if((Snd_count_S) % 1 == 0)								//ÿ������ʾһ��	
			{
				printf("\nSampling port: %d data send succuess!\n", Snd_count_S);//��ʾ�����˿ڳɹ����Ͱ��ĸ���
				for(iBuff = 0; iBuff < datalen; iBuff++)      /* print sended frame */
				{
					printf("%c",data_S[iBuff]);						//��ʾ��������
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
				printf("Sampling �˿ڷ��ʹ���portid�Ƿ�!\n");
				break;
			case 5:
				printf("Sampling �˿ڷ��ʹ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 7:
				printf("Sampling �˿ڷ��ʹ��󣺷������ݳ���!\n");
				break;
			case 8:
				printf("Sampling �˿ڷ��ʹ��󣺻�������!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/******************Sampling �˿ڽ���ʾ��***********************/
		flag = afdxComPortRcvMsg(Srcvportid, data2, &datalen, &RefreshFlag, &timeStamp);	
		if(flag == 0)
		{
			Rcv_count_S++;											//���ճɹ���������+1
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
				printf("Sampling �˿ڽ��մ���portid�Ƿ�!\n");
				break;
			case 4:
				printf("Sampling �˿ڽ��մ��󣺶˿�û����!\n");
				break;
			case 5:
				printf("Sampling �˿ڽ��մ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 6:
				printf("Sampling �˿ڽ��մ��󣺶��ж˿��������!\n");
				break;
			}
			getch();
		}
		strcpy(data2, data3); /*���մ����������*/
		Sleep(DELAY);


		/************************Queueing �˿ڷ���ʾ��**********************/
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
				printf("Queueing �˿ڷ��ʹ���portid�Ƿ�!\n");
				break;
			case 5:
				printf("Queueing �˿ڷ��ʹ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 7:
				printf("Queueing �˿ڷ��ʹ��󣺷������ݳ���!\n");
				break;
			case 8:
				printf("Queueing �˿ڷ��ʹ��󣺻�������!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/************************Queueing �˿ڽ���ʾ��********************/
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
				printf("Queueing �˿ڽ��մ���portid�Ƿ�!\n");
				break;
			case 4:
				printf("Queueing �˿ڽ��մ��󣺶˿�û����!\n");
				break;
			case 5:
				printf("Queueing �˿ڽ��մ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 6:
				printf("Queueing �˿ڽ��մ��󣺶��ж˿��������!\n");
				break;
			}
			getch();
		}
// 		strcpy(data2, data3); /*���մ����������*/
		Sleep(DELAY);

		/**********************SAP �˿ڷ���ʾ��********************/
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
				printf("SAP �˿ڷ��ʹ���portid�Ƿ�!\n");
				break;
			case 4:
				printf("SAP �˿ڷ��ʹ��󣺶˿�û����!\n");
				break;
			case 5:
				printf("SAP �˿ڷ��ʹ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 8:
				printf("SAP �˿ڷ��ʹ��󣺻�������!\n");
				break;
			}
			getch();
		}
		Sleep(DELAY);

		/*******************SAP �˿ڽ���ʾ��******************/
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
				printf("SAP �˿ڽ��մ���portid�Ƿ�!\n");
				break;
			case 4:
				printf("SAP �˿ڽ��մ��󣺶˿�û����!\n");
				break;
			case 5:
				printf("SAP �˿ڽ��մ��󣺶˿ڿ�û�г�ʼ��!\n");
				break;
			case 6:
				printf("SAP �˿ڽ��մ�����Ϣ�������!\n");
				break;
			}
			getch();
		}
// 		strcpy(data2, data3); /*���մ����������*/
		Sleep(DELAY);
	}
    return 0;
}								

/************************************************��****ע***********************************************
1. �ò��Գ������ڲ���"�Ի�"״̬�����ݵķ��������;

2. ���ֻ��Ҫ���Է���, ����������ע�͵�����, ���ֻ��Ҫ���Խ���, ������ע�͵�����;

3. flag �ķ���ֵ�����������

(1) Sampling �� Queueing �˿ڷ���ʾ���е�flag���� �� afdxComPortSndMsg() �����ķ���ֵ,��������:
	0: ���ͳɹ�;
	2: portid�Ƿ�;
	5: �˿ڿ�û�г�ʼ��;
	7: �������ݳ���;
	8: ��������;

(2) Sampling �� Queueing �˿ڽ���ʾ���е�flag���� �� afdxComPortRcvMsg() �����ķ���ֵ,��������:
	0: ���ͳɹ�;
	2: portid�Ƿ�;
	3: ���������Ȳ���;
	4: �˿�������;
	5: �˿ڿ�û�г�ʼ��;
	6: ���ж˿��������;

(3) SAP �˿ڷ���ʾ���е�flag���� �� afdxSAPPortSndMsg �����ķ���ֵ,��������:
	0: ���ͳɹ�;
	2: portid�Ƿ�;
	4: �˿�û����;
	5: �˿ڿ�û�г�ʼ��;
	8: ��������;

(4) SAP �˿ڽ���ʾ���е�flag���� �� afdxSAPPortRcvMsg �����ķ���ֵ,��������:
	0: ���ͳɹ�;
	2: portid�Ƿ�;
	3: ���������Ȳ���;
	4: �˿�������;
	5: �˿ڿ�û�г�ʼ��;
	6: ��Ϣ�������;
	
4. loadCfg()��������ֵ��������
	0: ��ʼ�����óɹ�;
	1: ���ñ�����ES������Ϣ���߶˿�������Ϣ;
	2: �˿��������Ϣ���ȣ����ڸö˿�ʹ�õ�VL�е�Smaxֵ;
	3: �˿����ñ���Ϣ��û���ҵ���Ӧ��VL;
	4: ���ж˿�������;
	5: ES����Ϊ��;
	6: �˿��������ô���;
*******************************************************************************************************/