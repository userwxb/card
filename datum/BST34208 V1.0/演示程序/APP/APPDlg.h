// APPDlg.h : header file
//

#if !defined(AFX_APPDLG_H__D4663882_654A_483A_AA57_E423F8D95EF4__INCLUDED_)
#define AFX_APPDLG_H__D4663882_654A_483A_AA57_E423F8D95EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAPPDlg dialog
#include "ComboListCtrl.h"

class CAPPDlg : public CDialog
{
// Construction
public:
	void InitListctrlDO();
	void InitListctrlDI();
	CAPPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAPPDlg)
	enum { IDD = IDD_APP_DIALOG };
	CComboListCtrl	m_listDI;
	CComboListCtrl	m_listDO;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAPPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnInput();
	afx_msg void OnClose();
	afx_msg void OnVersion();
	afx_msg void OnSelStatusDOA1();
	afx_msg void OnSelStatusDOA2();
	afx_msg void OnSelStatusDOB1();
	afx_msg void OnSelStatusDOB2();
	afx_msg void OnSelTypeDIA();
	afx_msg void OnSelTypeDIB();
	afx_msg void OnBtnOutput();
	afx_msg void OnBtnInputStop();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	afx_msg LRESULT OnEndLabelEditVariableCriteria(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT PopulateComboList(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	void EnableMenu(DWORD menuID, BOOL eORd);
	void CheckMenu(DWORD menuID, BOOL eORd);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPDLG_H__D4663882_654A_483A_AA57_E423F8D95EF4__INCLUDED_)
