// setup.cpp : implementation file
//

#include "stdafx.h"
#include "Dialg.h"
#include "setup.h"
#include "AEC429D6_lib.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HDEVICE hDevce;
extern int CHNO_TMAX;
extern int CHNO_RMAX;
extern RXCFGWORD_STRUCT  RXcfgword[8];
extern TXCFGWORD_STRUCT  TXcfgword[8];
extern WORD wddepth[8];
extern BOOL bladdtag[8];
extern BOOL blrexmode;
extern SYSTEMTIME stSysTime;

extern BYTE dialog[3];
extern DWORD dwTime;

extern HANDLE hevent;

BOOL isTxAll=FALSE,isRxAll=FALSE;
/////////////////////////////////////////////////////////////////////////////
// Csetup dialog


Csetup::Csetup(CWnd* pParent /*=NULL*/)
	: CDialog(Csetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(Csetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Csetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Csetup)
	DDX_Control(pDX, IDC_EDIT_DEPTH, m_eddepth);
	DDX_Control(pDX, IDC_COMBO_JO, m_cbjo);
	DDX_Control(pDX, IDC_COMBO_RXBIT, m_cbrxbit);
	DDX_Control(pDX, IDC_COMBO_TXBIT, m_cbtxbit);
	DDX_Control(pDX, IDC_COMBO_RXBR, m_cbrxbr);
	DDX_Control(pDX, IDC_COMBO_BR, m_cbtxbr);
	DDX_Control(pDX, IDC_TAB_RX, m_tabrx);
	DDX_Control(pDX, IDC_TAB_TX, m_tabtx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Csetup, CDialog)
	//{{AFX_MSG_MAP(Csetup)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_TX, OnSelchangeTabTx)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_TX, OnSelchangingTabTx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_RX, OnSelchangeTabRx)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_RX, OnSelchangingTabRx)
	ON_CBN_SELCHANGE(IDC_COMBO_TXBIT, OnSelchangeComboTxbit)
	ON_CBN_SELCHANGE(IDC_COMBO_RXBIT, OnSelchangeComboRxbit)
	ON_EN_CHANGE(IDC_EDIT_DEPTH, OnChangeEditDepth)
	ON_BN_CLICKED(IDC_SETBCANCEL, OnSetbcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Csetup message handlers

BOOL Csetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i=0;
	char c[80];

	for(i=0; i<CHNO_TMAX; i++)
	{
		sprintf(c, "通道[%d]", i);
		this->m_tabtx.InsertItem(i, c);
	}

	for(i=0; i<CHNO_RMAX; i++)
	{
		sprintf(c, "通道[%d]", i);
		this->m_tabrx.InsertItem(i, c);
	}		

	this->m_cbtxbr.AddString("100Kbps");
	this->m_cbtxbr.AddString("50Kbps");
	this->m_cbtxbr.AddString("48Kbps");
	this->m_cbtxbr.AddString("12.5Kbps");
	this->m_cbtxbr.SetCurSel(0);

	this->m_cbrxbr.AddString("100Kbps");
	this->m_cbrxbr.AddString("50Kbps");
	this->m_cbrxbr.AddString("48Kbps");
	this->m_cbrxbr.AddString("12.5Kbps");
	this->m_cbrxbr.SetCurSel(0);

	this->m_cbtxbit.AddString("32bit");
	this->m_cbtxbit.AddString("25bit");
	this->m_cbtxbit.SetCurSel(0);

	this->m_cbrxbit.AddString("32bit");
	this->m_cbrxbit.AddString("25bit");
	this->m_cbrxbit.SetCurSel(0);

	this->m_cbjo.AddString("无");
	this->m_cbjo.AddString("奇校验");
	this->m_cbjo.AddString("偶校验");
	this->m_cbjo.SetCurSel(0);

	this->m_eddepth.LimitText(5);

	this->TXResumeConfig(0);
	this->RXResumeConfig(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Csetup::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	dialog[0]=0;
	CDialog::OnCancel();
	CDialog::OnClose();
}

void Csetup::OnOK() 
{
	int i=0, j=0;
	char c[80];
	int chno_Tx=0, chno_Rx=0;
	BOOL blneedtag=FALSE;

	this->RXStoreConfig(this->m_tabrx.GetCurSel());
	this->TXStoreConfig(this->m_tabtx.GetCurSel());
	chno_Tx=this->m_tabtx.GetCurSel();
	chno_Rx=this->m_tabrx.GetCurSel();
#ifndef CARD_DEBUG	

	for(i=0; i<CHNO_RMAX; i=i+2)
	{
		if(!AEC429D6_SetRxCfgWord(hDevce, i/2, &RXcfgword[i]))
		{
			sprintf(c, "通道[%d]通道[%d]设置接收配置字失败!", i, i+1);
			MessageBox(c, "错误", MB_OK | MB_ICONERROR);
			return;
		}
	}
	for(i=0; i<CHNO_RMAX; i++)
	{
		if(!AEC429D6_SetTriggerDepth(hDevce, i, wddepth[i]))
		{
			sprintf(c, "通道[%d]设置接收触发深度失败!", i);
			MessageBox(c, "错误", MB_OK | MB_ICONERROR);
			return;
		}
		if(bladdtag[i])
		{
			blneedtag=TRUE;
			if(!AEC429D6_AddTimeTag(hDevce, i, bladdtag[i]))
			{
				sprintf(c, "通道[%d]设置添加时标使能失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;				
			}
		}
		else
		{
			if(!AEC429D6_AddTimeTag(hDevce, i, bladdtag[i]))
			{
				sprintf(c, "通道[%d]设置添加时标使能失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;				
			}
		}
		if(blneedtag)
		{
			AEC429D6_StartTimeTag(hDevce, TRUE, &stSysTime);
			if ((stSysTime.wHour + 8) > 24)
			{
				stSysTime.wHour = stSysTime.wHour + 8 - 24;
			}
			else
			{
				stSysTime.wHour = stSysTime.wHour + 8;
			}
			
			dwTime = stSysTime.wHour*3600000 + stSysTime.wMinute*60000 + stSysTime.wSecond*1000 + stSysTime.wMilliseconds;
		}
		else
		{
			AEC429D6_StartTimeTag(hDevce, FALSE, &stSysTime);
			dwTime = 0;
		}
	}

	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
		{
			if(!AEC429D6_SetTxCfgWord(hDevce, i+1, &TXcfgword[i]))
			{
				sprintf(c, "通道[%d]设置发送配置字失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
		}
		else
		{
			if(!AEC429D6_SetTxCfgWord(hDevce, i, &TXcfgword[i]))
			{
				sprintf(c, "通道[%d]设置发送配置字失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	if(hevent!=NULL)
	{
		CloseHandle(hevent);
		hevent = NULL;
	}

	if(blrexmode)
	{
		hevent=::CreateEvent(NULL, TRUE, FALSE, NULL);
		if(!AEC429D6_SetEvent(hDevce, hevent))
		{
			MessageBox("创建中断事件失败!", "错误", MB_OK | MB_ICONWARNING);
			return ;
		}
	}

	if(blrexmode)
	{
 		AEC429D6_SetIntMaskReg(hDevce, TRUE);
	}	
	else
	{
		AEC429D6_SetIntMaskReg(hDevce, FALSE);
	}
#endif
	dialog[0]=0;
	CDialog::OnOK();
}

void Csetup::OnCancel() 
{
	// TODO: Add extra cleanup here
	//CDialog::OnCancel();
}

int Csetup::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	
	// TODO: Add your specialized creation code here
	return 0;
}

void Csetup::TXStoreConfig(int idx)
{
	int i=idx,k=0;

	TXcfgword[i].TBaudSel=this->m_cbtxbr.GetCurSel();
	TXcfgword[i].TWLSel=this->m_cbtxbit.GetCurSel();

	if((i==0)||(i==2)||(i==4)||(i==6))
		RXcfgword[i].RWLSel=this->m_cbtxbit.GetCurSel();

	switch(this->m_cbjo.GetCurSel())
	{
	case 0:
		TXcfgword[i].TParityEn=FALSE;
		break;
	case 1:
		TXcfgword[i].TParityEn=TRUE;
		TXcfgword[i].TParitySel=0;
		break;
	case 2:
		TXcfgword[i].TParityEn=TRUE;
		TXcfgword[i].TParitySel=1;
		break;
	}

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_WORK2)) == BST_CHECKED)
	{
		TXcfgword[i].SelfTest=TRUE;
	}
	else
	{
		TXcfgword[i].SelfTest=FALSE;
	}

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGTXALL))==BST_CHECKED)
	{
		for(k=0;k<CHNO_TMAX;k++)
		{
			RXcfgword[i].RWLSel=this->m_cbtxbit.GetCurSel();
			TXcfgword[k].TBaudSel = TXcfgword[i].TBaudSel;
			TXcfgword[k].TWLSel = TXcfgword[i].TWLSel; 
			RXcfgword[k].RWLSel = RXcfgword[i].RWLSel;
			TXcfgword[k].TParityEn = TXcfgword[i].TParityEn;
			TXcfgword[k].TParitySel = TXcfgword[i].TParitySel;
			TXcfgword[k].SelfTest = TXcfgword[i].SelfTest;
		}
		isTxAll=TRUE;
	}
	else
	{
		isTxAll=FALSE;
	}
}

void Csetup::TXResumeConfig(int idx)
{
	int i=idx;

	if(isTxAll)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGTXALL), BST_CHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGTXALL), BST_UNCHECKED);
	}

	this->m_cbtxbr.SetCurSel(TXcfgword[i].TBaudSel);
	this->m_cbtxbit.SetCurSel(TXcfgword[i].TWLSel);
	if(!TXcfgword[i].TParityEn)
		this->m_cbjo.SetCurSel(0);
	else if(TXcfgword[i].TParitySel==0)
		this->m_cbjo.SetCurSel(1);
	else if(TXcfgword[i].TParitySel==1)
		this->m_cbjo.SetCurSel(2);

	if(TXcfgword[i].SelfTest)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_WORK2), BST_CHECKED);
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_WORK1), BST_UNCHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_WORK2), BST_UNCHECKED);
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_WORK1), BST_CHECKED);
	}
}

void Csetup::RXStoreConfig(int idx)
{
	int i=idx,k=0;
	char c[80];

	switch(i)
	{
	case 0:
		RXcfgword[0].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[0].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[0].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 1:
		RXcfgword[0].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[0].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[0].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 2:
		RXcfgword[2].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[2].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[2].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 3:
		RXcfgword[2].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[2].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[2].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 4:
		RXcfgword[4].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[4].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[4].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 5:
		RXcfgword[4].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[4].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[4].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 6:
		RXcfgword[6].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[6].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[6].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	case 7:
		RXcfgword[6].RBaudSel=this->m_cbrxbr.GetCurSel();
		RXcfgword[6].RWLSel=this->m_cbrxbit.GetCurSel();
		TXcfgword[6].TWLSel=this->m_cbrxbit.GetCurSel();
		break;
	}
	this->m_eddepth.GetWindowText(c, sizeof(c));
	wddepth[i]=atoi(c);

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_INTT))==BST_CHECKED)
	{
		blrexmode=TRUE;
	}
	else
	{
		blrexmode=FALSE;
	}

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG))==BST_CHECKED)
		bladdtag[i]=TRUE;
	else
		bladdtag[i]=FALSE;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGRXALL))==BST_CHECKED)
	{
		for(k=0;k<CHNO_RMAX;k++)
		{
			RXcfgword[i].RBaudSel=this->m_cbrxbr.GetCurSel();
			RXcfgword[i].RWLSel=this->m_cbrxbit.GetCurSel();
			TXcfgword[i].TWLSel=this->m_cbrxbit.GetCurSel();
			RXcfgword[k].RBaudSel = RXcfgword[i].RBaudSel;
			RXcfgword[k].RWLSel = RXcfgword[i].RWLSel;
			TXcfgword[k].TWLSel = TXcfgword[i].TWLSel;
			wddepth[k] = wddepth[i]; 
			bladdtag[k] = bladdtag[i];
		}
		isRxAll=TRUE;
	}
	else
	{
		isRxAll=FALSE;
	}
}

void Csetup::RXResumeConfig(int idx)
{
	int i=idx;
	char c[80];

	if(isRxAll)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGRXALL), BST_CHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TXCONFIGRXALL), BST_UNCHECKED);
	}

	switch(i)
	{
	case 0:
		this->m_cbrxbr.SetCurSel(RXcfgword[0].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[0].RWLSel);
		break;
	case 1:
		this->m_cbrxbr.SetCurSel(RXcfgword[0].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[0].RWLSel);
		break;
	case 2:
		this->m_cbrxbr.SetCurSel(RXcfgword[2].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[2].RWLSel);
		break;
	case 3:
		this->m_cbrxbr.SetCurSel(RXcfgword[2].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[2].RWLSel);
		break;
	case 4:
		this->m_cbrxbr.SetCurSel(RXcfgword[4].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[4].RWLSel);
		break;
	case 5:
		this->m_cbrxbr.SetCurSel(RXcfgword[4].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[4].RWLSel);
		break;
	case 6:
		this->m_cbrxbr.SetCurSel(RXcfgword[6].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[6].RWLSel);
		break;
	case 7:
		this->m_cbrxbr.SetCurSel(RXcfgword[6].RBaudSel);
		this->m_cbrxbit.SetCurSel(RXcfgword[6].RWLSel);
		break;
	}
	
	itoa(wddepth[i], c, 10);
	this->m_eddepth.SetWindowText(c);

	if(blrexmode)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_INTT), BST_CHECKED);
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_INQU), BST_UNCHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_INQU), BST_CHECKED);
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_INTT), BST_UNCHECKED);
	}

	if(bladdtag[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG), BST_UNCHECKED);
}

void Csetup::OnSelchangeTabTx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tabtx.GetCurSel();
	this->TXResumeConfig(i);
	*pResult = 0;
}

void Csetup::OnSelchangingTabTx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0, j=0;
	i=this->m_tabtx.GetCurSel();
	this->TXStoreConfig(i);
	j=this->m_tabrx.GetCurSel();
	this->RXStoreConfig(j);
	*pResult = 0;
}

void Csetup::OnSelchangeTabRx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tabrx.GetCurSel();
	this->RXResumeConfig(i);
	*pResult = 0;
}

void Csetup::OnSelchangingTabRx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0, j=0;
	i=this->m_tabrx.GetCurSel();
	this->RXStoreConfig(i);
	j=this->m_tabtx.GetCurSel();
	this->TXStoreConfig(j);
	*pResult = 0;
}

void Csetup::OnSelchangeComboTxbit() 
{
	int i=0, j=0;
	i=this->m_tabrx.GetCurSel();
	this->RXStoreConfig(i);
	j=this->m_tabtx.GetCurSel();
	this->TXStoreConfig(j);
	i=this->m_tabrx.GetCurSel();
	this->RXResumeConfig(i);
}

void Csetup::OnSelchangeComboRxbit() 
{
	int i=0, j=0;

	i=this->m_tabtx.GetCurSel();
	this->TXStoreConfig(i);
	j=this->m_tabrx.GetCurSel();
	this->RXStoreConfig(j);
	i=this->m_tabtx.GetCurSel();
	this->TXResumeConfig(i);
}

void Csetup::OnChangeEditDepth() 
{
	char c[80];
	int i=0;

	this->m_eddepth.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>16384)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(16384, c, 10);
		this->m_eddepth.SetWindowText(c);
		this->m_eddepth.SetSel(this->m_eddepth.LineLength(-1), this->m_eddepth.LineLength(-1), FALSE);
		this->m_eddepth.SetFocus();
	}		
}

void Csetup::OnSetbcancel() 
{
	// TODO: Add your control notification handler code here
	dialog[0]=0;
	CDialog::OnCancel();
}
