/*====================================================================
//---------------File - Sample_ContinueTask--------------------
//
//----------Library for accessing the AEC429-PCI/S6 cards.----------
//
//-------It accesses the hardware via vxworks functions.----------
// 
//====================================================================*/
#include "copyright_wrs.h"

#ifdef VXWORKSP
#include <configInum.h>
#else
#include <intlib.h> 
#endif

#include <iv.h>

#include "vxWorks.h"
#include "sysLib.h"
#include "vmlib.h"
#include "memLib.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

#include "AEC429D6_lib.h"

#define CHNO_MAX	8


RXCFGWORD_STRUCT stRxCfgWord={0};
TXCFGWORD_STRUCT stTxCfgWord={0};
CARDTYPE_STRUCT stCardType={0};

HANDLE hDev;

unsigned long txbuf[5]={0}, txlen=0;
unsigned long rxbuf[5]={0}, rxlen=0;

int main(void)
{
	int i=0;
	unsigned char CHNO_TMAX=0;
	unsigned char CHNO_RMAX=0;
	unsigned short rt=0;
	unsigned char chno=0;
	unsigned long cnt=0;

	stRxCfgWord.RBaudSel=0;      /* 100Kbps */
	stRxCfgWord.RWLSel=0;		 /* 32BIT */
	stTxCfgWord.TBaudSel=0; 
	stTxCfgWord.TWLSel=0;
	stTxCfgWord.TParityEn=FALSE; /* parity enable */
	stTxCfgWord.TParitySel=FALSE;/* parity select */
	stTxCfgWord.SelfTest=TRUE;


	if (!AEC429D6_Open (&hDev, 0))
	{
		printf("Error: AEC429D6_Open\n");
		return 0;
	}

	if(!AEC429D6_Reset(hDev))
	{
		printf("Error: AEC429D6_Open\n");
		goto end;
	}

	AEC429D6_GetCardType(hDev, &stCardType);
	CHNO_TMAX=stCardType.TChannelNumber;
	CHNO_RMAX=stCardType.RChannelNumber;


	for(i=0; i<CHNO_MAX; i=i+2)
	{
		if(!AEC429D6_SetRxCfgWord(hDev, i/2, &stRxCfgWord))
		{
			printf("Error: AEC429D6_Open\n");
			goto end;
		}
	}

	for(i=0; i<CHNO_MAX; i++)
	{
		if((CHNO_RMAX==4)&&(CHNO_TMAX==2)&&(i==1))
		{
			if(!AEC429D6_SetTxCfgWord(hDev, i+1, &stTxCfgWord))
			{
				printf("Error: AEC429D6_SetTxCfgWord\n");
				goto end;
			}
		}
		else
		{
			if(!AEC429D6_SetTxCfgWord(hDev, i, &stTxCfgWord))
			{
				printf("Error: AEC429D6_SetTxCfgWord\n");
				goto end;
			}
		}
		if (!AEC429D6_ResetRxFIFO (hDev, i))
		{
			printf("Error: AEC429D6_ResetRxFIFO\n");
			goto end;
		}
		if (!AEC429D6_ResetTxFIFO (hDev, i))
		{
			printf("Error: AEC429D6_ResetTxFIFO\n");
			goto end;
		}
		if (!AEC429D6_Rx_Start(hDev, i, TRUE))
		{
			printf("Error: AEC429D6_Rx_Start(TRUE)\n");
			goto end;
		}
	}


	for(i=0; i<CHNO_RMAX; i++)
	{
		if(!AEC429D6_AddTimeTag(hDev, i, FALSE))
		{
			printf("Error: AEC429D6_AddTimeTag\n");
			goto end;
		}
	}
			
	AEC429D6_StartTimeTag(hDev, FALSE);
	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_RMAX==4)&&(CHNO_TMAX==2)&&(i==1))
		{
			if(!AEC429D6_InnerTriggerEnable(hDev, i+1, TRUE))
			{
				printf("Error: AEC429D6_InnerTriggerEnable\n");
				goto end;	
			}
			if(!AEC429D6_SetInnerTriggerPeriod(hDev, i+1, 5000))
			{
				printf("Error: AEC429D6_SetInnerTriggerPeriod\n");
				goto end;
			}
			if(!AEC429D6_SetWordInterval(hDev, i+1, 0))
			{
				printf("Error: AEC429D6_SetWordInterval\n");
				goto end;
			}
			if(!AEC429D6_SetTriggerLevel(hDev, i+1, TRUE, FALSE))
			{
				printf("Error: AEC429D6_SetTriggerLevel\n");
				goto end;
			}
			if(!AEC429D6_TriggerCnt(hDev, i+1, 10))
			{
				printf("Error: AEC429D6_TriggerCnt\n");
				goto end;
			}
		}
		else
		{
			if(!AEC429D6_InnerTriggerEnable(hDev, i, TRUE))
			{
				printf("Error: AEC429D6_InnerTriggerEnable\n");
				goto end;
			}
			if(!AEC429D6_SetInnerTriggerPeriod(hDev, i, 5000))
			{
				printf("Error: AEC429D6_SetInnerTriggerPeriod\n");
				goto end;
			}
			if(!AEC429D6_SetWordInterval(hDev, i, 0))
			{
				printf("Error: AEC429D6_SetWordInterval\n");
				goto end;
			}
			if(!AEC429D6_SetTriggerLevel(hDev, i, TRUE, FALSE))
			{
				printf("Error: AEC429D6_SetTriggerLevel\n");
				goto end;
			}
			if(!AEC429D6_TriggerCnt(hDev, i, 10))
			{
				printf("Error: AEC429D6_TriggerCnt\n");
				goto end;
			}

		}
	}



	for(chno=0; chno<CHNO_RMAX; chno++)
	{
		if(!AEC429D6_SetTriggerDepth(hDev, chno, 4))
		{
			printf("Error: AEC429D6_SetTriggerDepth\n");
			goto end;
		}
	}

	AEC429D6_SetIntMaskReg(hDev, TRUE);


	printf("Tx ----------------------\n");
	txlen = 5;
	for (i=0; i<txlen; i++)
	{
		txbuf[i] = i;
	}

	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_RMAX==4)&&(CHNO_TMAX==2)&&(i==1))
		{
			AEC429D6_EnableTimerMode(hDev, i+1, TRUE);
			AEC429D6_TxStart(hDev, i+1, FALSE);
			if((AEC429D6_TxFIFOSTR(hDev, i+1)&FIFOEMPTY)==FIFOEMPTY)
			{
				AEC429D6_TxWrite (hDev, i+1, txlen, txbuf, &rt);
				printf("CH %d = write %d\n", i, rt);
			}

		}
		else
		{
			AEC429D6_EnableTimerMode(hDev, i, TRUE);
			AEC429D6_TxStart(hDev, i, FALSE);
			if((AEC429D6_TxFIFOSTR(hDev, i)&FIFOEMPTY)==FIFOEMPTY)
			{
				AEC429D6_TxWrite (hDev, i, txlen, txbuf, &rt);
				printf("CH %d = write %d\n", i, rt);
			}

		}
	}
	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_RMAX==4)&&(CHNO_TMAX==2)&&(i==1))
		{
			AEC429D6_TxStart(hDev, i+1, TRUE);

		}
		else
		{
			AEC429D6_TxStart(hDev, i, TRUE);
		}
	}


	while (cnt<10)
	{
		printf("Rx ----------------------\n");
		for (chno=0; chno<CHNO_RMAX; chno++)
		{
			rxlen=(unsigned short)AEC429D6_RxLen (hDev, chno);
			while (rxlen<5)
			{
				rxlen=(unsigned short)AEC429D6_RxLen (hDev, chno);
			}
			AEC429D6_RxRead (hDev, chno, rxlen, rxbuf, &rt);
			printf("data: ");
			for (i=0; i<rt; i++)
			{
				printf("%08x ", rxbuf[i]);
			}
			printf("\nrx chno=%d is ok.\n", chno);
		}
		cnt++;
		printf("count=%ld\n", cnt);
	}


end:
	AEC429D6_Reset(hDev);
	if (!AEC429D6_Close (hDev))
	{
		printf("Error: AEC429D6_Close\n");
	}

	printf("\nDone!\n");

	return 0;
}



