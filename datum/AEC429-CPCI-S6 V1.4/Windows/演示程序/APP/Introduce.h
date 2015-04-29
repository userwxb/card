#if !defined(AFX_INTRODUCE_H__95C600E1_361B_4BDC_900B_C57AE5C30C70__INCLUDED_)
#define AFX_INTRODUCE_H__95C600E1_361B_4BDC_900B_C57AE5C30C70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Introduce.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntroduce dialog

class CIntroduce : public CDialog
{
// Construction
public:
	CIntroduce(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIntroduce)
	enum { IDD = IDD_INTRODUCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntroduce)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntroduce)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTRODUCE_H__95C600E1_361B_4BDC_900B_C57AE5C30C70__INCLUDED_)
