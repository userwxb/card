// DialgDlg.h : header file
//

#if !defined(AFX_DIALGDLG_H__E9F90D1D_B960_4772_81BB_5E157F0EE4BE__INCLUDED_)
#define AFX_DIALGDLG_H__E9F90D1D_B960_4772_81BB_5E157F0EE4BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialgDlg dialog

class CDialgDlg : public CDialog
{
// Construction
public:
	void EnRedraw(BYTE chno,BOOL En);
	void EnRxRec(BYTE chno);
	void RevData(BYTE i,DWORD len);

	CDialgDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CDialgDlg)
	enum { IDD = IDD_DIALG_DIALOG };
	CListCtrl	m_list1;
	CListCtrl	m_list8;
	CListCtrl	m_list7;
	CListCtrl	m_list6;
	CListCtrl	m_list5;
	CListCtrl	m_list4;
	CListCtrl	m_list3;
	CListCtrl	m_list2;
	CListCtrl	m_listtx;
	CButton	m_btrex;
	CTabCtrl	m_tabrev;
	CEdit	m_txnum;
	CEdit	m_edsddata;
	CButton	m_bttx;
	CButton	m_btsave;
	CButton	m_btload;
	CButton	m_btdele;
	CButton	m_btclea;
	CButton	m_btadd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	
	// Generated message map functions
	//{{AFX_MSG(CDialgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDele();
	afx_msg void OnButtonClea();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonLoad2();
	afx_msg void OnChangeEDITSendData();
	afx_msg void OnKillfocusEDITSendData();
	afx_msg void OnSelchangeTabRev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMemuword();
	afx_msg void OnMemupulse();
	afx_msg void OnMemusd();
	afx_msg void OnButtonRex();
	afx_msg void OnButtonTx();
	afx_msg void OnButtonStoptx();
	afx_msg void OnMessage(WPARAM subidx, LPARAM data);
	afx_msg void OnButtonAllselect();
	afx_msg void OnButtonNoneselect();
	afx_msg void OnCheckTmit();
	afx_msg void OnMemureset();
	afx_msg void OnButtonRxenableall();
	afx_msg void OnButtonRxenablenone();
	afx_msg void OnCheckRxenable0();
	afx_msg void OnCheckRxenable1();
	afx_msg void OnCheckRxenable2();
	afx_msg void OnCheckRxenable3();
	afx_msg void OnCheckRxenable4();
	afx_msg void OnCheckRxenable5();
	afx_msg void OnCheckRxenable6();
	afx_msg void OnCheckRxenable7();
	afx_msg void OnButtonRall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALGDLG_H__E9F90D1D_B960_4772_81BB_5E157F0EE4BE__INCLUDED_)
