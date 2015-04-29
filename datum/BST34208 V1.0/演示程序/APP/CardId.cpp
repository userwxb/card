// CardId.cpp : implementation file
//

#include "stdafx.h"
#include "APP.h"
#include "CardId.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HANDLE hcard;
extern BYTE CardId;
/////////////////////////////////////////////////////////////////////////////
// CCardId dialog


CCardId::CCardId(CWnd* pParent /*=NULL*/)
	: CDialog(CCardId::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardId)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCardId::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardId)
	DDX_Control(pDX, IDC_EDIT_CARDID, m_edtID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCardId, CDialog)
	//{{AFX_MSG_MAP(CCardId)
	ON_EN_CHANGE(IDC_EDIT_CARDID, OnChangeEditCardid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardId message handlers

void CCardId::OnOK() 
{
	// TODO: Add extra validation here
	char ch[100];

	memset(ch,0,sizeof(ch));
	this->m_edtID.GetWindowText(ch,sizeof(ch));
	CardId = atoi(ch);
	CDialog::OnOK();
}

void CCardId::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CCardId::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_edtID.SetWindowText("0");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCardId::OnChangeEditCardid() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;
	
	this->m_edtID.GetWindowText(c, sizeof(c));
	i = atoi(c);
	if(i>7)
	{
		MessageBox(TEXT("°å¿¨ºÅ³¬³ö·¶Î§(0~7)"), TEXT("¾¯¸æ"), MB_OK | MB_ICONWARNING);
		this->m_edtID.SetWindowText(TEXT("0"));
		this->m_edtID.SetSel(this->m_edtID.LineLength(-1), this->m_edtID.LineLength(-1), FALSE);
		this->m_edtID.SetFocus();
	}
}
