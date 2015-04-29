// Introduce.cpp : implementation file
//

#include "stdafx.h"
#include "Dialg.h"
#include "Introduce.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ID	200

int timerloop=0;

/////////////////////////////////////////////////////////////////////////////
// CIntroduce dialog
CIntroduce::CIntroduce(CWnd* pParent /*=NULL*/)
	: CDialog(CIntroduce::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntroduce)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CIntroduce::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntroduce)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIntroduce, CDialog)
	//{{AFX_MSG_MAP(CIntroduce)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntroduce message handlers

void CIntroduce::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CIntroduce::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL CIntroduce::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	timerloop = 0;
	this->SetTimer(TIMER_ID, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIntroduce::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->KillTimer(TIMER_ID);		
	CDialog::OnClose();
}

void CIntroduce::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	timerloop++;
	if (timerloop>2)
		PostMessage(WM_CLOSE, 0, 0);
	CDialog::OnTimer(nIDEvent);
}

void CIntroduce::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE, 0, 0);		
	CDialog::OnLButtonDown(nFlags, point);
}
