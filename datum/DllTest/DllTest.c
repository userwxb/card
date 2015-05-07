#include "afdxcfgRec.h"
#include "afdxLib.h"
#include "afdxQportLib.h"

#include "dlldemo.h"




int main(void)
{
	int temp = 0;
	
	ESCfg escfg_test;
	unsigned int datalen;/*输入输出参数*/
	unsigned int  ip_src;
    unsigned short udp_src;
		
	char buffer[1024];
	
		unsigned int Ssndportid = 3;	
	unsigned int Srcvportid = 6;
	unsigned int Qsndportid = 2;	
	unsigned int Qrcvportid = 5;
	unsigned int SAPsndportid = 1;	
	unsigned int SAPrcvportid = 4;


	char data_S[128] = {"SAMPLING"};
	char data_Q[128] = {"QUEUING"};
	char data_SAP[128] = {"SAP"};


	char data2[128] = {""};
	char data3[128] = {""};

	unsigned int RefreshFlag = 1;
	int timeStamp = 12;

	unsigned int ip_dst;
    unsigned short udp_dst;
	unsigned int ip_srcd;
    unsigned short udp_srcd;

	int flag = 0;

	int Snd_count_S = 0;
	int Snd_count_Q = 0;
	int Snd_count_SAP = 0;
	int Rcv_count_S = 0;
	int Rcv_count_Q = 0;
	int Rcv_count_SAP = 0;
	
	ip_dst = 0x12345678;
    ip_dst = (ip_dst);
		
    udp_dst = (1024);
    udp_dst = (udp_dst);

	ip_src = 0x12345678;          
    ip_src = (ip_src);
	
    udp_src = (1024);
    udp_src = (udp_src);

	unsigned int iBuff;

	

	afdxPortLibInitlib(2); 

	
	
	
	temp = Onadd(11,22);

	memset(&escfg_test,0,sizeof(escfg_test));

//	loadCfg( (ESCfg*)&escfg_test,0);
	
	afdxPortLibInitlib(2);
	
	//inet_addr_afdx("192.168.1.5");
  //   afdxSAPPortRcvMsg( 0x123,buffer,( unsigned int *)&datalen,/*输入输出参数*/(unsigned int  *)&ip_src,(unsigned short *)&udp_src);
					   datalen = 128;
	
		 flag = afdxComPortSndMsg(Ssndportid, data_S, datalen); 
		 
		 flag = afdxComPortRcvMsg(Srcvportid, data2, &datalen, &RefreshFlag, &timeStamp);	
		 
		 flag = afdxComPortSndMsg(Qsndportid, data_Q, datalen);
		 
		 flag = afdxComPortRcvMsg(Qrcvportid, data2, &datalen, &RefreshFlag, &timeStamp);
		 
	//	 flag = afdxSAPPortSndMsg(SAPsndportid, data_SAP, datalen, ip_dst, udp_dst);
		 
		 flag = afdxSAPPortRcvMsg(SAPrcvportid, data2, &datalen, &ip_src, &udp_src);	
		 
		 
	

	
	return 0;
}
