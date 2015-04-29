#if !defined(AFX_SETPULSE_H__898A93B9_4988_40BB_8FD8_F6976E28DF9C__INCLUDED_)
#define AFX_SETPULSE_H__898A93B9_4988_40BB_8FD8_F6976E28DF9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// setpulse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Csetpulse dialog

class Csetpulse : public CDialog
{
// Construction
public:
	Csetpulse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Csetpulse)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_edtimenum;
	CEdit	m_edlworddelay;
	CEdit	m_edltime;
	CEdit	m_eddelaytime;
	CEdit	m_edlperiod;
	CTabCtrl	m_tabpulse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Csetpulse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void StoreConfig(int idx);
	void ResumeConfig(int idx);
	// Generated message map functions
	//{{AFX_MSG(Csetpulse)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelchangeTabPulse(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabPulse(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCheckIn();
	afx_msg void OnCheckExt();
	afx_msg void OnChangeEditLperiod();
	afx_msg void OnChangeEditLworddelay();
	afx_msg void OnChangeEditDelaytime();
	afx_msg void OnChangeEditLtime();
	afx_msg void OnChangeEditTimenum();
	afx_msg void OnCheckLenable();
	afx_msg void OnCheckWenable();
	afx_msg void OnBttcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPULSE_H__898A93B9_4988_40BB_8FD8_F6976E28DF9C__INCLUDED_)
