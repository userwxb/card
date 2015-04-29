#if !defined(AFX_LOGO_H__271BD937_9177_4CED_A2BE_B773ED914898__INCLUDED_)
#define AFX_LOGO_H__271BD937_9177_4CED_A2BE_B773ED914898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Logo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogo dialog

class CLogo : public CDialog
{
// Construction
public:
	CLogo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogo)
	enum { IDD = IDD_DIALOG_LOGO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogo)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGO_H__271BD937_9177_4CED_A2BE_B773ED914898__INCLUDED_)
