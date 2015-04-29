// APP.h : main header file for the APP application
//

#if !defined(AFX_APP_H__0C0C8EB7_E1B2_477B_AFA1_FA944B6F9D64__INCLUDED_)
#define AFX_APP_H__0C0C8EB7_E1B2_477B_AFA1_FA944B6F9D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAPPApp:
// See APP.cpp for the implementation of this class
//

class CAPPApp : public CWinApp
{
public:
	CAPPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAPPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APP_H__0C0C8EB7_E1B2_477B_AFA1_FA944B6F9D64__INCLUDED_)
