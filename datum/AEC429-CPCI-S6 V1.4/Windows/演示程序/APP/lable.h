#if !defined(AFX_LABLE_H__A18664CA_7FDE_48C8_AD9D_189BF8820EF0__INCLUDED_)
#define AFX_LABLE_H__A18664CA_7FDE_48C8_AD9D_189BF8820EF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// lable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Clable dialog

class Clable : public CDialog
{
// Construction
public:
	Clable(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Clable)
	enum { IDD = IDD_DIALOG3 };
	CComboBox	m_cbsd;
	CTabCtrl	m_tablable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Clable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void StoreConfig(int idx);
	void ResumeConfig(int idx);
	// Generated message map functions
	//{{AFX_MSG(Clable)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeTABlable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTABlable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSd();
	afx_msg void OnBtscancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABLE_H__A18664CA_7FDE_48C8_AD9D_189BF8820EF0__INCLUDED_)
