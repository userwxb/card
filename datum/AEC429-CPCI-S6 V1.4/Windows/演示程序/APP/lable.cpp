// lable.cpp : implementation file
//

#include "stdafx.h"
#include "Dialg.h"
#include "lable.h"
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
extern BYTE  SdLable[8][4][256];
extern BYTE  SdLable_bk[8][4][256];

extern BYTE dialog[3];

BYTE btlable[8][256]={0};
BYTE btsd[8]={0};

BOOL blsd[8]={0};
BOOL bllable[8]={0};

HWND hwButton_Label[256];
HWND hwStatic_hnum[16];
HWND hwStatic_lnum[16];
BYTE btcb[8]={0};

#define LABELDLG_BASE_XB		80
#define LABELDLG_BASE_YB		50
#define LABELDLG_BASE_WIDTHB	20
#define LABELDLG_BASE_HEIGHTB	18

BOOL isLabelEn=FALSE;
/////////////////////////////////////////////////////////////////////////////
// Clable dialog


Clable::Clable(CWnd* pParent /*=NULL*/)
	: CDialog(Clable::IDD, pParent)
{
	//{{AFX_DATA_INIT(Clable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Clable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Clable)
	DDX_Control(pDX, IDC_COMBO_SD, m_cbsd);
	DDX_Control(pDX, IDC_TAB_lable, m_tablable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Clable, CDialog)
	//{{AFX_MSG_MAP(Clable)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_lable, OnSelchangeTABlable)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_lable, OnSelchangingTABlable)
	ON_CBN_SELCHANGE(IDC_COMBO_SD, OnSelchangeComboSd)
	ON_BN_CLICKED(IDC_BTSCANCEL, OnBtscancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Clable message handlers

BOOL Clable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int i=0;
	char c[80];

	for(i=0; i<CHNO_RMAX; i++)
	{
		sprintf(c, "通道[%d]", i);
		this->m_tablable.InsertItem(i, c);
	}
	
	this->m_cbsd.AddString("0");
	this->m_cbsd.AddString("1");
	this->m_cbsd.AddString("2");
	this->m_cbsd.AddString("3");
	this->m_cbsd.SetCurSel(0);

	this->ResumeConfig(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Clable::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	dialog[2]=0;
	CDialog::OnCancel();
	CDialog::OnClose();
}

int Clable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	int i=0, j=0;
	char c[80];

	for(i=0; i<16; i++)
	{
		hwStatic_lnum[i] = ::CreateWindow("STATIC", NULL, 
									SS_CENTER | WS_CHILD,
									LABELDLG_BASE_XB-2 + i*LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_YB-LABELDLG_BASE_HEIGHTB,
									LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_HEIGHTB,
									this->m_hWnd,
									NULL,
									0,
									0);
		::ShowWindow(hwStatic_lnum[i], SW_SHOW);
		::UpdateWindow(hwStatic_lnum[i]);
		sprintf(c, "%02x", i);
		::SetWindowText(hwStatic_lnum[i], c);
	}

	for(i=0; i<16; i++)
	{
		memset(c, 0, sizeof(c));

		hwStatic_hnum[i] = ::CreateWindow("STATIC", NULL, 
									SS_CENTER | WS_CHILD,
									LABELDLG_BASE_XB-LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_YB +i*LABELDLG_BASE_HEIGHTB,
									LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_HEIGHTB,
									this->m_hWnd,
									NULL,
									0,
									0);
		::ShowWindow(hwStatic_hnum[i], SW_SHOW);
		::UpdateWindow(hwStatic_hnum[i]);
		sprintf(c, "%02x", i*16);
		::SetWindowText(hwStatic_hnum[i], c);
	}

	for (i=0; i<16; i++)
	{
		for (j=0; j<16; j++)
		{
			hwButton_Label[i*16+j] = ::CreateWindow("BUTTON", NULL, 
									BS_AUTOCHECKBOX | WS_CHILD,
									LABELDLG_BASE_XB + j*LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_YB + i*LABELDLG_BASE_HEIGHTB,
									LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_HEIGHTB,
									this->m_hWnd,
									NULL,
									0,
									0);
			::ShowWindow(hwButton_Label[i*16+j], SW_SHOW);
			::UpdateWindow(hwButton_Label[i*16+j]);
		}
	}	


	return 0;
}

void Clable::OnOK() 
{
	int i=0, j=0;
	char c[80];
	this->StoreConfig(this->m_tablable.GetCurSel());

#ifndef CARD_DEBUG
	for(i=0; i<CHNO_RMAX; i++)
	{
		for(j=0; j<256; j++)
		{
			SdLable[i][0][j]=0;
			SdLable[i][1][j]=0;
			SdLable[i][2][j]=0;
			SdLable[i][3][j]=0;
			if(bllable[i])
			{
				SdLable[i][0][j]=SdLable_bk[i][0][j];
				SdLable[i][1][j]=SdLable_bk[i][1][j];
				SdLable[i][2][j]=SdLable_bk[i][2][j];
				SdLable[i][3][j]=SdLable_bk[i][3][j];
			}
		/*	if((blsd[i])&&(bllable[i]))
			{
				SdLable[i].btsdlable[btsd[i]][j]=SdLable_bk[i].btsdlable_bk[btsd[i]][j];
			}
			else if((blsd[i])&&(!bllable[i]))
			{
				SdLable[i].btsdlable[btsd[i]][j]=1;
			}
			else if((!blsd[i])&&(bllable[i]))
			{
				SdLable[i].btsdlable[0][j]=SdLable_bk[i].btsdlable_bk[btsd[i]][j];
				SdLable[i].btsdlable[1][j]=SdLable_bk[i].btsdlable_bk[btsd[i]][j];
				SdLable[i].btsdlable[2][j]=SdLable_bk[i].btsdlable_bk[btsd[i]][j];
				SdLable[i].btsdlable[3][j]=SdLable_bk[i].btsdlable_bk[btsd[i]][j];
			}
			else if((!blsd[i])&&(!bllable[i]))
			{
				SdLable[i].btsdlable[0][j]=0;
				SdLable[i].btsdlable[1][j]=0;
				SdLable[i].btsdlable[2][j]=0;
				SdLable[i].btsdlable[3][j]=0;			
			}*/
		}
	}
	
	for(i=0; i<CHNO_RMAX; i++)
	{
		if(!AEC429D6_SetLabelFilter(hDevce, i, SdLable[i]))
		{
			sprintf(c, "通道[%d]设置标号过滤表失败!", i);
			MessageBox(c, "错误", MB_OK | MB_ICONERROR);
			return;		
		}
	//	if((blsd[i])||(bllable[i]))
		if(bllable[i])
		{
			if(!AEC429D6_StartLabelFilter(hDevce, i, TRUE))
			{
				sprintf(c, "通道[%d]使能标号过滤失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
		}
		else
		{
			if(!AEC429D6_StartLabelFilter(hDevce, i, FALSE))
			{
				sprintf(c, "通道[%d]关闭使能标号过滤失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
		}
	}
//	btlable[0][17]=1;
/*	for(i=0; i<CHNO_RMAX; i++)
	{
	
		if(!AEC429A_SetLabelFilter(hDevce, 4, btlable))
		{
			sprintf(c, "通道[%d]设置标号过滤表失败!", i+1);
			MessageBox(c, "错误", MB_OK | MB_ICONERROR);
			return;		
		}
		if((blsd[i])||(bllable[i]))
		{
			if(!AEC429A_StartLabelFilter(hDevce, 4, TRUE))
			{
				sprintf(c, "通道[%d]使能标号过滤失败!", 2+1);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
	}
		else
		{
			if(!AEC429A_StartLabelFilter(hDevce, i, FALSE))
			{
				sprintf(c, "通道[%d]关闭使能标号过滤失败!", i+1);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return;		
			}
		}
	}*/
#endif	
	dialog[2]=0;
	CDialog::OnOK();
}

void Clable::OnCancel() 
{
	// TODO: Add extra cleanup here
}

void Clable::ResumeConfig(int idx)
{
	int i=idx;
	int j=0;

	if(isLabelEn)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ADALLS), BST_CHECKED);
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ADALLS), BST_UNCHECKED);
	}

	this->m_cbsd.SetCurSel(btsd[i]);
	for(j=0; j<256; j++)
	{
		if(SdLable_bk[i][btsd[i]][j]==1)
			Button_SetCheck(hwButton_Label[j], BST_CHECKED);
		else
			Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
	}
	if(blsd[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SD), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SD), BST_UNCHECKED);

	if(bllable[i])
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LABLE), BST_CHECKED);
	else
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LABLE), BST_UNCHECKED);
}

void Clable::StoreConfig(int idx)
{
	int i=idx;
	int j=0,k=0,l=0;
	
	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SD))==BST_CHECKED)
		blsd[i]=TRUE;
	else
		blsd[i]=FALSE;
	btsd[i]=this->m_cbsd.GetCurSel();

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_LABLE))==BST_CHECKED)
		bllable[i]=TRUE;
	else
		bllable[i]=FALSE;

	for(j=0; j<256; j++)
	{
		if(Button_GetCheck(hwButton_Label[j])==BST_CHECKED)
		{
			SdLable_bk[i][btsd[i]][j]=1;
		}
		else
		{
			SdLable_bk[i][btsd[i]][j]=0;
		}
	}

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ADALLS))==BST_CHECKED)
	{
		for(k=0;k<CHNO_TMAX;k++)
		{
			blsd[k] = blsd[i];
			bllable[k] = bllable[i];
			for(j=0;j<256;j++)
			{
				SdLable_bk[k][btsd[i]][j] = SdLable_bk[i][btsd[i]][j];
			}
		}
		isLabelEn = TRUE;
	}
	else
	{
		isLabelEn = FALSE;
	}
}

void Clable::OnSelchangeTABlable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tablable.GetCurSel();
	this->ResumeConfig(i);
	
	*pResult = 0;
}

void Clable::OnSelchangingTABlable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i=0;
	i=this->m_tablable.GetCurSel();
	this->StoreConfig(i);
	
	*pResult = 0;
}


void Clable::OnSelchangeComboSd() 
{
	int i=0, j=0, chno=0;
	int sd=0;
	chno=this->m_tablable.GetCurSel();
	i=btcb[chno];

	for(j=0; j<256; j++)
	{
		if(Button_GetCheck(hwButton_Label[j])==BST_CHECKED)
		{
			SdLable_bk[chno][i][j]=1;
		}
		else
		{
			SdLable_bk[chno][i][j]=0;
		}
	}

	i=this->m_cbsd.GetCurSel();
	for(j=0; j<256; j++)
	{
		if(SdLable_bk[chno][i][j]==1)
			Button_SetCheck(hwButton_Label[j],BST_CHECKED);
		else
			Button_SetCheck(hwButton_Label[j],BST_UNCHECKED);
	}
	btcb[chno]=i;
}

void Clable::OnBtscancel() 
{
	// TODO: Add your control notification handler code here
	dialog[2]=0;
	CDialog::OnCancel();
}
