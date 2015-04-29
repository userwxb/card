#if !defined(AFX_BASEADDR_H__7B861A49_83C9_48AB_8BB9_C9A1CCC7D70E__INCLUDED_)
#define AFX_BASEADDR_H__7B861A49_83C9_48AB_8BB9_C9A1CCC7D70E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Baseaddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseaddr dialog

class CBaseaddr : public CDialog
{
// Construction
public:
	CBaseaddr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseaddr)
	enum { IDD = IDD_BASEADDR };
	CEdit	m_edbaseaddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseaddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseaddr)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnChangeEdit1();
	virtual void OnOK();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKillfocusEdit1();
	virtual void OnCancel();
	afx_msg void OnBtcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEADDR_H__7B861A49_83C9_48AB_8BB9_C9A1CCC7D70E__INCLUDED_)
