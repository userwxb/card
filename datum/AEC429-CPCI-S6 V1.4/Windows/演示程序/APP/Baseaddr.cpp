// Baseaddr.cpp : implementation file
//

#include "stdafx.h"
#include "Dialg.h"
#include "Baseaddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BYTE Cardid;
/////////////////////////////////////////////////////////////////////////////
// CBaseaddr dialog


CBaseaddr::CBaseaddr(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseaddr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseaddr)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBaseaddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseaddr)
	DDX_Control(pDX, IDC_EDIT1, m_edbaseaddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseaddr, CDialog)
	//{{AFX_MSG_MAP(CBaseaddr)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_KILLFOCUS()
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BTCANCEL, OnBtcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseaddr message handlers

BOOL CBaseaddr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char c[80];
	this->m_edbaseaddr.LimitText(3);
	ultoa(Cardid, c, 10);
	this->m_edbaseaddr.SetWindowText(c);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseaddr::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();
	CDialog::OnClose();
}

void CBaseaddr::OnChangeEdit1() 
{
	char c[80];
	int i=0;

	this->m_edbaseaddr.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>7)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(7, c, 10);
		this->m_edbaseaddr.SetWindowText(TEXT(c));
		this->m_edbaseaddr.SetSel(this->m_edbaseaddr.LineLength(-1), this->m_edbaseaddr.LineLength(-1), FALSE);
		this->m_edbaseaddr.SetFocus();
	}
}

void CBaseaddr::OnOK() 
{
	char c[80];
	this->m_edbaseaddr.GetWindowText(c, sizeof(c));
	Cardid=(BYTE)atoi(c);

	CDialog::OnOK();
}

void CBaseaddr::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here	
}

void CBaseaddr::OnKillfocusEdit1() 
{
	if (this->m_edbaseaddr.LineLength(-1)==0)
	{
		this->m_edbaseaddr.SetWindowText(TEXT("0"));
	}
	
}

void CBaseaddr::OnCancel() 
{
	// TODO: Add extra cleanup here
	//CDialog::OnCancel();
}

void CBaseaddr::OnBtcancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();	
}
