// Logo.cpp : implementation file
//

#include "stdafx.h"
#include "APP.h"
#include "Logo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogo dialog

#define TIMERID 100

int looptime=0;

CLogo::CLogo(CWnd* pParent /*=NULL*/)
	: CDialog(CLogo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogo, CDialog)
	//{{AFX_MSG_MAP(CLogo)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogo message handlers

BOOL CLogo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	looptime =0;
	this->SetTimer(TIMERID, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogo::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE, 0, 0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CLogo::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	looptime++;
	if (looptime > 2)
	{
		PostMessage(WM_CLOSE, 0, 0);
	}

	CDialog::OnTimer(nIDEvent);
}

void CLogo::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->KillTimer(TIMERID);

	CDialog::OnClose();
}
