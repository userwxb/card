#if !defined(AFX_CARDID_H__6E003BE9_F8BF_4034_BC1E_E87AC0C4A2AF__INCLUDED_)
#define AFX_CARDID_H__6E003BE9_F8BF_4034_BC1E_E87AC0C4A2AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CardId.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCardId dialog

class CCardId : public CDialog
{
// Construction
public:
	CCardId(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCardId)
	enum { IDD = IDD_DIALOG_CARDID };
	CEdit	m_edtID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardId)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCardId)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditCardid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDID_H__6E003BE9_F8BF_4034_BC1E_E87AC0C4A2AF__INCLUDED_)
