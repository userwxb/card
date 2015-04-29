// setpulse.cpp : implementation file
//

#include "stdafx.h"
#include "Dialg.h"
#include "setpulse.h"
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

extern WORD wdperiod[8];
extern BOOL blLtouch[8];
extern WORD wdWordInt[8];
extern BOOL blWtouch[8];
extern WORD wddelaytime[8];
extern BOOL blFallEdge[8];
extern BOOL blRiseEdge[8];
extern WORD wdTimeNum[8];
extern WORD wdCount[8];

extern BYTE dialog[3];
extern BOOL blTimeTx[8];

BOOL isNAllSame=FALSE;
/////////////////////////////////////////////////////////////////////////////
// Csetpulse dialog


Csetpulse::Csetpulse(CWnd* pParent /*=NULL*/)
	: CDialog(Csetpulse::IDD, pParent)
{
	//{{AFX_DATA_INIT(Csetpulse)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Csetpulse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Csetpulse)
	DDX_Control(pDX, IDC_EDIT_TIMENUM, m_edtimenum);
	DDX_Control(pDX, IDC_EDIT_LWORDDELAY, m_edlworddelay);
	DDX_Control(pDX, IDC_EDIT_LTIME, m_edltime);
	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_eddelaytime);
	DDX_Control(pDX, IDC_EDIT_LPERIOD, m_edlperiod);
	DDX_Control(pDX, IDC_TAB_PULSE, m_tabpulse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Csetpulse, CDialog)
	//{{AFX_MSG_MAP(Csetpulse)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PULSE, OnSelchangeTabPulse)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_PULSE, OnSelchangingTabPulse)
	ON_BN_CLICKED(IDC_CHECK_IN, OnCheckIn)
	ON_BN_CLICKED(IDC_CHECK_EXT, OnCheckExt)
	ON_EN_CHANGE(IDC_EDIT_LPERIOD, OnChangeEditLperiod)
	ON_EN_CHANGE(IDC_EDIT_LWORDDELAY, OnChangeEditLworddelay)
	ON_EN_CHANGE(IDC_EDIT_DELAYTIME, OnChangeEditDelaytime)
	ON_EN_CHANGE(IDC_EDIT_LTIME, OnChangeEditLtime)
	ON_EN_CHANGE(IDC_EDIT_TIMENUM, OnChangeEditTimenum)
	ON_BN_CLICKED(IDC_CHECK_LENABLE, OnCheckLenable)
	ON_BN_CLICKED(IDC_CHECK_WENABLE, OnCheckWenable)
	ON_BN_CLICKED(IDC_BTTCANCEL, OnBttcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Csetpulse message handlers

BOOL Csetpulse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i=0;
	char c[80];

	for(i=0; i<CHNO_TMAX; i++)
	{
		sprintf(c, "通道[%d]", i);
		this->m_tabpulse.InsertItem(i, c);
	}

	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_RADIO_UP), FALSE);
	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_RADIO_DOWN), FALSE);
	this->m_edlperiod.LimitText(5);
	this->m_edltime.LimitText(5);
	this->m_edlworddelay.LimitText(5);
	this->m_edtimenum.LimitText(4);
	this->m_eddelaytime.LimitText(5);

	this->ResumeConfig(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Csetpulse::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	dialog[1]=0;
	CDialog::OnCancel();
	CDialog::OnClose();
}
void Csetpulse::ResumeConfig(int idx)
{
	int i=idx;
	char c[80];
	
	if(isNAllSame)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TRIGALL), BST_CHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TRIGALL), BST_UNCHECKED);
	}

	ultoa(wdperiod[i], c, 10);
	this->m_edlperiod.SetWindowText(c);

	sprintf(c, "%d", wdWordInt[i]);
	this->m_edlworddelay.SetWindowText(c);

	sprintf(c, "%d", wddelaytime[i]);
	this->m_eddelaytime.SetWindowText(c);

	sprintf(c, "%d", wdTimeNum[i]);
	this->m_edltime.SetWindowText(c);

	sprintf(c, "%d", wdCount[i]);
	this->m_edtimenum.SetWindowText(c);

	if(blLtouch[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_IN), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_IN), BST_UNCHECKED);

	if(blWtouch[i])
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd,IDC_CHECK_EXT), BST_CHECKED);
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_LPERIOD), FALSE);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_EXT), BST_UNCHECKED);
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_LPERIOD), TRUE);
	}

	if(blRiseEdge[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LENABLE), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LENABLE), BST_UNCHECKED);

	if(blFallEdge[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd,  IDC_CHECK_WENABLE), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd,  IDC_CHECK_WENABLE), BST_UNCHECKED);
}

void Csetpulse::StoreConfig(int idx)
{
	int i=idx,k=0;
	char c[80];

	this->m_edlperiod.GetWindowText(c, sizeof(c));
	wdperiod[i]=(WORD)atol(c);

	this->m_edlworddelay.GetWindowText(c, sizeof(c));
	wdWordInt[i]=(WORD)atol(c);

	this->m_eddelaytime.GetWindowText(c, sizeof(c));
	wddelaytime[i]=(WORD)atol(c);

	this->m_edltime.GetWindowText(c, sizeof(c));
	wdTimeNum[i]=(WORD)atol(c);

	this->m_edtimenum.GetWindowText(c, sizeof(c));
	wdCount[i]=(WORD)atol(c);

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_IN))==BST_CHECKED)
		blLtouch[i]=TRUE;
	else
		blLtouch[i]=FALSE;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_EXT))==BST_CHECKED)
		blWtouch[i]=TRUE;
	else
		blWtouch[i]=FALSE;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LENABLE))==BST_CHECKED)
		blRiseEdge[i]=TRUE;
	else
		blRiseEdge[i]=FALSE;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_WENABLE))==BST_CHECKED)
		blFallEdge[i]=TRUE;
	else
		blFallEdge[i]=FALSE;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TRIGALL))==BST_CHECKED)
	{
		for(k=0;k<8;k++)
		{
			wdperiod[k] = wdperiod[i];
			wdWordInt[k] = wdWordInt[i];
			wddelaytime[k] =wddelaytime[i];
			wdTimeNum[k] = wdTimeNum[i];
			wdCount[k] = wdCount[i];
			blLtouch[k] = blLtouch[i];
			blWtouch[k] = blWtouch[i];
			blRiseEdge[k] = blRiseEdge[i];
			blFallEdge[k] = blFallEdge[i];
		}
		isNAllSame = TRUE;
	}
	else
	{
		isNAllSame = FALSE;
	}
}

void Csetpulse::OnSelchangeTabPulse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tabpulse.GetCurSel();
	this->ResumeConfig(i);

	*pResult = 0;
}

void Csetpulse::OnSelchangingTabPulse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tabpulse.GetCurSel();
	this->StoreConfig(i);
	*pResult = 0;
}

void Csetpulse::OnOK() 
{
	int i=0;
	char c[80];
	this->StoreConfig(this->m_tabpulse.GetCurSel());

#ifndef CARD_DEBUG

	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
		{
			if(!AEC429D6_ExternalTriggerEnable(hDevce, i+1, FALSE))
			{
				sprintf(c, "通道[%d]停止外触发失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_InnerTriggerEnable(hDevce, i+1, FALSE))
			{
				sprintf(c, "通道[%d]使能外触发失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_EnableTimerMode(hDevce, i+1, FALSE))
			{
				sprintf(c, "通道%d使能定时发送失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				return;
			}
			if(blLtouch[i])
			{
				if(!AEC429D6_ExternalTriggerEnable(hDevce, i+1, blLtouch[i]))
				{
					sprintf(c, "通道[%d]停止外触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				if(!AEC429D6_InnerTriggerEnable(hDevce, i+1, blLtouch[i]))
				{
					sprintf(c, "通道[%d]使能内触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				if(!AEC429D6_SetInnerTriggerPeriod(hDevce, i+1, wdperiod[i]))
				{
					sprintf(c, "通道[%d]设置内触发周期失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				blTimeTx[i]=TRUE;
			}
			if(blWtouch[i])
			{
				if(!AEC429D6_ExternalTriggerEnable(hDevce, i+1, blWtouch[i]))
				{
					sprintf(c, "通道[%d]使能外触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				
				if(!AEC429D6_InnerTriggerEnable(hDevce, i+1, blLtouch[i]))
				{
					sprintf(c, "通道[%d]停止内触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				blTimeTx[i]=TRUE;
			}

			if(!AEC429D6_SetDelayTime(hDevce, i+1, wddelaytime[i]))
			{
				sprintf(c, "通道[%d]设置内外触发延迟时间失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_SetTriggerLevel(hDevce, i+1, blFallEdge[i], blRiseEdge[i]))
			{
				sprintf(c, "通道[%d]设置内外触发边沿选择失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_SetWordInterval(hDevce, i+1, wdWordInt[i]))
			{
				sprintf(c, "通道[%d]设置内外触发429字间间隔失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_NumToSend(hDevce, i+1, wdTimeNum[i]))
			{
				sprintf(c, "通道[%d]设置内外触发发送次数失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
			if(!AEC429D6_TriggerCnt(hDevce, i+1, wdCount[i]))
			{
				sprintf(c, "通道[%d]设置内外触发发送数据量失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
		}
		else
		{
			if(!AEC429D6_ExternalTriggerEnable(hDevce, i, FALSE))
			{
				sprintf(c, "通道[%d]停止外触发失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_InnerTriggerEnable(hDevce, i, FALSE))
			{
				sprintf(c, "通道[%d]使能外触发失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_EnableTimerMode(hDevce, i, FALSE))
			{
				sprintf(c, "通道%d使能定时发送失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				return;
			}
			if(blLtouch[i])
			{
				if(!AEC429D6_ExternalTriggerEnable(hDevce, i, blWtouch[i]))
				{
					sprintf(c, "通道[%d]停止外触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}

				if(!AEC429D6_InnerTriggerEnable(hDevce, i, blLtouch[i]))
				{
					sprintf(c, "通道[%d]使能内触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				if(!AEC429D6_SetInnerTriggerPeriod(hDevce, i, wdperiod[i]))
				{
					sprintf(c, "通道[%d]设置内触发周期失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				blTimeTx[i]=TRUE;
			}
			if(blWtouch[i])
			{
				if(!AEC429D6_ExternalTriggerEnable(hDevce, i, blWtouch[i]))
				{
					sprintf(c, "通道[%d]使能外触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				if(!AEC429D6_InnerTriggerEnable(hDevce, i, blLtouch[i]))
				{
					sprintf(c, "通道[%d]停止内触发失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONERROR);
					return;
				}
				blTimeTx[i]=TRUE;
			}

			if(!AEC429D6_SetDelayTime(hDevce, i, wddelaytime[i]))
			{
				sprintf(c, "通道[%d]设置内外触发延迟时间失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_SetTriggerLevel(hDevce, i, blFallEdge[i], blRiseEdge[i]))
			{
				sprintf(c, "通道[%d]设置内外触发边沿选择失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_SetWordInterval(hDevce, i, wdWordInt[i]))
			{
				sprintf(c, "通道[%d]设置内外触发429字间间隔失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;
			}
			if(!AEC429D6_NumToSend(hDevce, i, wdTimeNum[i]))
			{
				sprintf(c, "通道[%d]设置内外触发发送次数失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
			if(!AEC429D6_TriggerCnt(hDevce, i, wdCount[i]))
			{
				sprintf(c, "通道[%d]设置内外触发发送数据量失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
		}
	}
#endif	
	dialog[1]=0;
	CDialog::OnOK();
}

void Csetpulse::OnCancel() 
{
	// TODO: Add extra cleanup here
	//CDialog::OnCancel();
}

void Csetpulse::OnCheckIn() 
{
	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_EXT))==BST_CHECKED)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_EXT), BST_UNCHECKED);
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_LPERIOD), TRUE);
	}	
}

void Csetpulse::OnCheckExt() 
{
	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_IN))==BST_CHECKED)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_IN), BST_UNCHECKED);	
	}

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_EXT))==BST_CHECKED)
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_LPERIOD), FALSE);
	else
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_LPERIOD), TRUE);
}

void Csetpulse::OnChangeEditLperiod() 
{
	char c[80];
	int i=0;

	this->m_edlperiod.GetWindowText(c, sizeof(c));

	i = atoi(c);
	if (i>65535)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(65535, c, 10);
		this->m_edlperiod.SetWindowText(c);
		this->m_edlperiod.SetSel(this->m_edlperiod.LineLength(-1), this->m_edlperiod.LineLength(-1), FALSE);
		this->m_edlperiod.SetFocus();
	}	
}

void Csetpulse::OnChangeEditLworddelay() 
{
	char c[80];
	int i=0;

	this->m_edlworddelay.GetWindowText(c, sizeof(c));

	i = atoi(c);
	if (i>65535)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(65535, c, 10);
		this->m_edlworddelay.SetWindowText(c);
		this->m_edlworddelay.SetSel(this->m_edlworddelay.LineLength(-1), this->m_edlworddelay.LineLength(-1), FALSE);
		this->m_edlworddelay.SetFocus();
	}
}

void Csetpulse::OnChangeEditDelaytime() 
{
	char c[80];
	int i=0;

	this->m_eddelaytime.GetWindowText(c, sizeof(c));

	i = atoi(c);
	if (i>65535)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(65535, c, 10);
		this->m_eddelaytime.SetWindowText(c);
		this->m_eddelaytime.SetSel(this->m_eddelaytime.LineLength(-1), this->m_eddelaytime.LineLength(-1), FALSE);
		this->m_eddelaytime.SetFocus();
	}
}

void Csetpulse::OnChangeEditLtime() 
{
	char c[80];
	int i=0;

	this->m_edltime.GetWindowText(c, sizeof(c));

	i = atoi(c);
	if (i>65535)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(65535, c, 10);
		this->m_edltime.SetWindowText(c);
		this->m_edltime.SetSel(this->m_edltime.LineLength(-1), this->m_edltime.LineLength(-1), FALSE);
		this->m_edltime.SetFocus();
	}
}

void Csetpulse::OnChangeEditTimenum() 
{
	char c[80];
	int i=0;

	this->m_edtimenum.GetWindowText(c, sizeof(c));

	i = atoi(c);
	if (i>1024)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(1024, c, 10);
		this->m_edtimenum.SetWindowText(c);
		this->m_edtimenum.SetSel(this->m_edtimenum.LineLength(-1), this->m_edtimenum.LineLength(-1), FALSE);
		this->m_edtimenum.SetFocus();
	}
}

void Csetpulse::OnCheckLenable() 
{
	// TODO: Add your control notification handler code here
//	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LENABLE))==BST_CHECKED)
	{
//		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_WENABLE),BST_UNCHECKED);		
	}
}

void Csetpulse::OnCheckWenable() 
{
	// TODO: Add your control notification handler code here
//	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_WENABLE))==BST_CHECKED)
	{
//		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LENABLE),BST_UNCHECKED);		
	}
}

void Csetpulse::OnBttcancel() 
{
	// TODO: Add your control notification handler code here
	dialog[1]=0;
	CDialog::OnCancel();
}
