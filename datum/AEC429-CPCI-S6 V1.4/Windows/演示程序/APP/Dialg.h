// Dialg.h : main header file for the DIALG application
//

#if !defined(AFX_DIALG_H__51F5C8C5_B5B1_44DC_9A58_945F60C0A16B__INCLUDED_)
#define AFX_DIALG_H__51F5C8C5_B5B1_44DC_9A58_945F60C0A16B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialgApp:
// See Dialg.cpp for the implementation of this class
//

class CDialgApp : public CWinApp
{
public:
	CDialgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALG_H__51F5C8C5_B5B1_44DC_9A58_945F60C0A16B__INCLUDED_)
