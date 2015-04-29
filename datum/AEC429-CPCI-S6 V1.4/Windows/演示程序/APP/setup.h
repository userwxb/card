#if !defined(AFX_SETUP_H__DB384841_77F7_4802_85BB_AEAA4C5D4543__INCLUDED_)
#define AFX_SETUP_H__DB384841_77F7_4802_85BB_AEAA4C5D4543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// setup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Csetup dialog

class Csetup : public CDialog
{
// Construction
public:
	Csetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Csetup)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_eddepth;
	CComboBox	m_cbjo;
	CComboBox	m_cbrxbit;
	CComboBox	m_cbtxbit;
	CComboBox	m_cbrxbr;
	CComboBox	m_cbtxbr;
	CTabCtrl	m_tabrx;
	CTabCtrl	m_tabtx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Csetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void TXStoreConfig(int idx);
	void TXResumeConfig(int idx);
	void RXStoreConfig(int idx);
	void RXResumeConfig(int idx);

	// Generated message map functions
	//{{AFX_MSG(Csetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeTabTx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabTx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTabRx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabRx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinDepth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboTxbit();
	afx_msg void OnSelchangeComboRxbit();
	afx_msg void OnChangeEditDepth();
	afx_msg void OnSetbcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP_H__DB384841_77F7_4802_85BB_AEAA4C5D4543__INCLUDED_)
