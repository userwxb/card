// APPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "APP.h"
#include "APPDlg.h"
#include "Logo.h"
#include "cardid.h"
#include "BSTIOD48_lib.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE hCard=NULL;
BYTE CardId=0;
#define TIMER_ID_INPUT	100
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAPPDlg dialog

CAPPDlg::CAPPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAPPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAPPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAPPDlg)
	DDX_Control(pDX, IDC_LIST_DI, m_listDI);
	DDX_Control(pDX, IDC_LIST_DO, m_listDO);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAPPDlg, CDialog)
	//{{AFX_MSG_MAP(CAPPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OUTPUT, OnBtnInput)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_VERSION, OnVersion)
	ON_COMMAND(IDM_TYPE_DOA1, OnSelStatusDOA1)
	ON_COMMAND(IDM_TYPE_DOA2, OnSelStatusDOA2)
	ON_COMMAND(IDM_TYPE_DOB1, OnSelStatusDOB1)
	ON_COMMAND(IDM_TYPE_DOB2, OnSelStatusDOB2)
	ON_COMMAND(IDM_TYPE_DIA, OnSelTypeDIA)
	ON_COMMAND(IDM_TYPE_DIB, OnSelTypeDIB)
	ON_BN_CLICKED(IDC_BTN_INPUT, OnBtnOutput)
	ON_BN_CLICKED(IDC_BTN_INPUT_STOP, OnBtnInputStop)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_VALIDATE, OnEndLabelEditVariableCriteria)
	ON_MESSAGE(WM_SET_ITEMS, PopulateComboList)
//	ON_MESSAGE(WM_MYERROR_MESSAGE, OnMyErrorMessage)		
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAPPDlg message handlers

BOOL CAPPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DWORD dwSn=0;
	char ch[100];

	this->InitListctrlDO();
	OnSelStatusDOA1();
	
	this->InitListctrlDI();
	OnSelTypeDIA();
	
	CLogo logo;
	logo.DoModal();
	
	CCardId cardid;
	if(cardid.DoModal()!=IDOK)
	{
		::ExitProcess(0);
		return 0;
	}
#ifdef MY_DEBUG
	if(!BSTIOD48_Open ( &hCard,  CardId))
	{
		MessageBox("打开板卡失败!","信息提示",MB_OK|MB_ICONINFORMATION);
		::ExitProcess(0);
		return 0;
	}
	
	if(!BSTIOD48_Reset ( hCard))
	{
		MessageBox("复位板卡失败!","信息提示",MB_OK|MB_ICONINFORMATION);
		::ExitProcess(0);
		return 0;
	}
	
	
	dwSn = BSTIOD48_GetSN ( hCard);
	sprintf(ch,"BST34208 SN:%08x",dwSn);
	this->SetWindowText(ch);
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAPPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAPPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAPPDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CAPPDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
void CAPPDlg::InitListctrlDI()
{
	int i=0;
	CString str;
	
	this->m_listDI.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	this->m_listDI.InsertColumn(0,_T("通道号"),LVCFMT_CENTER,50);
	this->m_listDI.InsertColumn(1,_T("输入类型"),LVCFMT_CENTER,130);
	this->m_listDI.InsertColumn(2,_T("输入状态"),LVCFMT_CENTER,100);
	
	m_listDI.SetReadOnlyColumns(0);
	m_listDI.SetComboColumns(1,true);
	m_listDI.SetReadOnlyColumns(2);
	
	m_listDI.EnableVScroll();
	
	for(i=0;i<DI_CHNO_MAX;i++)
	{
		str.Format("%d",i+DI_CHNO_MAX);
		m_listDI.InsertItem(LVIF_TEXT|LVIF_STATE, i, 
			str, LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
		
		m_listDI.SetItemText(i,1,"电源/电源断");	
	}
}
void CAPPDlg::InitListctrlDO()
{
	int i=0;
	CString str;

	this->m_listDO.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	this->m_listDO.InsertColumn(0,_T("通道号"),LVCFMT_CENTER,50);
	this->m_listDO.InsertColumn(1,_T("输出类型"),LVCFMT_CENTER,130);
	this->m_listDO.InsertColumn(2,_T("输出状态"),LVCFMT_CENTER,100);

	m_listDO.SetReadOnlyColumns(0);
	m_listDO.SetComboColumns(1,true);
	m_listDO.SetComboColumns(2,true);
	
	m_listDO.EnableVScroll();
	
	for(i=0;i<DO_CHNO_MAX;i++)
	{
		str.Format("%d",i);
		m_listDO.InsertItem(LVIF_TEXT|LVIF_STATE, i, 
			str, LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);

		m_listDO.SetItemText(i,1,"电源/电源断");	
		m_listDO.SetItemText(i,2,"电源");
	}
}

LRESULT CAPPDlg::OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)lParam;
	// TODO: Add your control notification handler code here

	int i=0;
	return 1;
}

LRESULT CAPPDlg::PopulateComboList(WPARAM wParam, LPARAM lParam)
{
	// Get the Combobox window pointer
	CComboBox* pInPlaceCombo = static_cast<CComboBox*> (GetFocus());

	// Get the inplace combbox top left
	CRect obWindowRect;

	pInPlaceCombo->GetWindowRect(&obWindowRect);
	
	CPoint obInPlaceComboTopLeft(obWindowRect.TopLeft()); 
	
	// Get the active list
	// Get the control window rect
	// If the inplace combobox top left is in the rect then
	// The control is the active control
	
	int iColIndex = (int )wParam;
	int iRowIndex = 0;
	CStringList* pComboList = reinterpret_cast<CStringList*>(lParam);
	pComboList->RemoveAll(); 

	if (obWindowRect.PtInRect(obInPlaceComboTopLeft)) 
	{	
		UINT uID = iColIndex;
		switch(uID)
		{
			case 1:
			{
				pComboList->AddTail("电源/电源断");
				pComboList->AddTail("电源地/电源地断");				
				break;
			}
			case 2:
			{
				POSITION   pos   =   m_listDO.GetFirstSelectedItemPosition(); 
				iRowIndex = m_listDO.GetNextSelectedItem(pos);
				CString cstrType = m_listDO.GetItemText(iRowIndex,1);
				if(cstrType.Compare(_T("电源/电源断")) == 0)
				{
					pComboList->AddTail("电源");
					pComboList->AddTail("电源断");	
				}
				if(cstrType.Compare(_T("电源地/电源地断")) == 0)
				{
					pComboList->AddTail("电源地");
					pComboList->AddTail("电源地断");	
				}				
				break;
			}
		}
	}
	return true;
}

void CAPPDlg::OnBtnInput() 
{
	char ch[100];
	BYTE ChanNo=0;
	BYTE btstatus = 0;
	BYTE btRetStatus = 0;
	
	char szErbuf[10240] = {0};
	int j =0,i=0;
	BOOL blEr = FALSE;
	j = sprintf(szErbuf,"%s","输出失败:\n");

	::EnableWindow(::GetDlgItem(this->m_hWnd,IDC_BTN_OUTPUT),FALSE);
	for(ChanNo=0;ChanNo<DO_CHNO_MAX;ChanNo++)
	{
		m_listDO.GetItemText(ChanNo,2,ch,sizeof(ch));
		if(strcmp(ch,"电源")==0 || strcmp(ch,"电源地")==0)
			btstatus = 1;
		else
			btstatus = 0;
		
		BSTIOD48_Relay_SetStatus_Single(hCard,ChanNo,btstatus);
		BSTIOD48_Relay_GetStatus_Single(hCard,ChanNo,&btRetStatus);
		if(btstatus != btRetStatus)
		{
			blEr = TRUE;
			i +=1;
			if(i%3 == 0)
				j += sprintf( szErbuf + j, "通道:%d\n",ChanNo);
			else
				j += sprintf( szErbuf + j, "通道:%d,",ChanNo);
		}

	}
	::EnableWindow(::GetDlgItem(this->m_hWnd,IDC_BTN_OUTPUT),TRUE);

	if(blEr)
	{
		if(szErbuf[j-1] == ',')
			szErbuf[j-1] = '\0';
		MessageBox(szErbuf, TEXT("错误提示"));
	}
}

void CAPPDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	if (MessageBox(TEXT("您确定要退出吗?"), TEXT("退出提示"), MB_YESNO | MB_ICONQUESTION)!=IDYES)
	{
		return;
	}

	if(!BSTIOD48_Reset ( hCard))
	{
		MessageBox("复位板卡失败!","信息提示",MB_OK|MB_ICONINFORMATION);
	}

	if(!BSTIOD48_Close ( hCard))
	{
		MessageBox("关闭板卡失败!","信息提示",MB_OK|MB_ICONINFORMATION);
	}
	
	this->DestroyWindow();
	CDialog::OnClose();
}

void CAPPDlg::EnableMenu(DWORD menuID, BOOL eORd)
{
	HMENU hMenu=NULL;
	
	hMenu = ::GetMenu(this->m_hWnd);
	if (eORd)
	{
		::EnableMenuItem(hMenu, menuID, MF_ENABLED);
	}
	else
	{
		::EnableMenuItem(hMenu, menuID, MF_DISABLED | MF_GRAYED);
	}
}

//	Check Menu Item by Menu ID
//
void CAPPDlg::CheckMenu(DWORD menuID, BOOL eORd)
{
	HMENU hMenu=NULL;
	
	hMenu = ::GetMenu(this->m_hWnd);
	if (eORd)
	{
		::CheckMenuItem(hMenu, menuID, MF_CHECKED);
	}
	else
	{
		::CheckMenuItem(hMenu, menuID, MF_UNCHECKED);
	}
}


void CAPPDlg::OnVersion()
{
	// TODO: Add your command handler code here
	CAboutDlg DlgAbout;
	DlgAbout.DoModal();
}

void CAPPDlg::OnSelStatusDOA1() 
{
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DOA1,TRUE);
	CheckMenu(IDM_TYPE_DOA2,FALSE);
	CheckMenu(IDM_TYPE_DOB1,FALSE);
	CheckMenu(IDM_TYPE_DOB2,FALSE);

	for(int i=0;i<DO_CHNO_MAX;i++)
	{		
		m_listDO.SetItemText(i,1,"电源/电源断");
		m_listDO.SetItemText(i,2,"电源");
	}
}

void CAPPDlg::OnSelStatusDOA2() 
{
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DOA1,FALSE);
	CheckMenu(IDM_TYPE_DOA2,TRUE);
	CheckMenu(IDM_TYPE_DOB1,FALSE);
	CheckMenu(IDM_TYPE_DOB2,FALSE);

	for(int i=0;i<DO_CHNO_MAX;i++)
	{		
		m_listDO.SetItemText(i,1,"电源/电源断");
		m_listDO.SetItemText(i,2,"电源断");
	}
}

void CAPPDlg::OnSelStatusDOB1() 
{
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DOA1,FALSE);
	CheckMenu(IDM_TYPE_DOA2,FALSE);
	CheckMenu(IDM_TYPE_DOB1,TRUE);
	CheckMenu(IDM_TYPE_DOB2,FALSE);

	for(int i=0;i<DO_CHNO_MAX;i++)
	{		
		m_listDO.SetItemText(i,1,"电源地/电源地断");
		m_listDO.SetItemText(i,2,"电源地");
	}
}

void CAPPDlg::OnSelStatusDOB2() 
{
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DOA1,FALSE);
	CheckMenu(IDM_TYPE_DOA2,FALSE);
	CheckMenu(IDM_TYPE_DOB1,FALSE);
	CheckMenu(IDM_TYPE_DOB2,TRUE);
	
	for(int i=0;i<DO_CHNO_MAX;i++)
	{		
		m_listDO.SetItemText(i,1,"电源地/电源地断");
		m_listDO.SetItemText(i,2,"电源地断");
	}
}
void CAPPDlg::OnSelTypeDIA() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DIA,TRUE);
	CheckMenu(IDM_TYPE_DIB,FALSE);
	
	for(int i=0;i<DI_CHNO_MAX;i++)
	{		
		m_listDI.SetItemText(i,1,"电源/电源断");;
	}
}
void CAPPDlg::OnSelTypeDIB() 
{
	// TODO: Add your command handler code here
	CheckMenu(IDM_TYPE_DIA,FALSE);
	CheckMenu(IDM_TYPE_DIB,TRUE);
	
	for(int i=0;i<DI_CHNO_MAX;i++)
	{		
		m_listDI.SetItemText(i,1,"电源地/电源地断");;
	}
}

void CAPPDlg::OnBtnOutput() 
{
	// TODO: Add your control notification handler code here
	this->SetTimer(TIMER_ID_INPUT, 1000, NULL);	
	::EnableWindow(::GetDlgItem(this->m_hWnd,IDC_BTN_INPUT),FALSE);
}

void CAPPDlg::OnBtnInputStop() 
{
	// TODO: Add your control notification handler code here
	this->KillTimer(TIMER_ID_INPUT);
	::EnableWindow(::GetDlgItem(this->m_hWnd,IDC_BTN_INPUT),TRUE);
}

void CAPPDlg::OnTimer(UINT nIDEvent) 
{
	char ch[100];
	BYTE ChanNo=0;
	BYTE btstatus = 0;
	BOOL inputmode=0;
	
	for(ChanNo=48;ChanNo<CHNO_MAX;ChanNo++)
	{
		m_listDI.GetItemText(ChanNo-48,1,ch,sizeof(ch));
		if(strcmp(ch,"电源/电源断")==0)
			inputmode = 0;
		else
			inputmode = 1;
		
		BSTIOD48_IO_Get_Input_Status_Single( hCard, ChanNo, &btstatus);
		if(inputmode==0)
		{
			if(btstatus)
			{
				m_listDI.SetItemText(ChanNo-48,2,"电源");
			}
			else
			{
				m_listDI.SetItemText(ChanNo-48,2,"电源断");
			}
		}
		else
		{
			if(btstatus)
			{
				m_listDI.SetItemText(ChanNo-48,2,"电源地");
			}
			else
			{
				m_listDI.SetItemText(ChanNo-48,2,"电源地断");
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}
#define TType DWORD
inline TType EnableBit(BYTE bit,TType Tval)
{
	Tval |= (0x1<<(bit));
	return Tval;
}
inline TType EnableBits(BYTE stbit,BYTE enbit,TType Tval)
{
	BYTE i=0;
	assert(stbit<=enbit && enbit<=(sizeof(TType)*8-1) );
	for(i=stbit;i<=enbit;i++)
	{
		Tval = EnableBit(i,Tval);
	}
	return Tval;
}
inline TType GetBitsStatus(BYTE stbit,BYTE enbit,TType Tval,BOOL MoveBit)
{
	BYTE i=0;
	TType TvalTmp = 0;
	assert(stbit<=enbit && enbit<=(sizeof(TType)*8-1) );
	TvalTmp = EnableBits(stbit,enbit,TvalTmp);
	Tval &= TvalTmp;
	if(MoveBit)	
	{
		Tval >>= stbit;
		return Tval;
	}
	else
	{
		return Tval;
	}
}
inline BOOL Get_VersionInfo(const DWORD dwVersion,const char *szCONST,char *szVersion)
{
	if(szVersion == NULL)
		return FALSE;
	USHORT usH=0,usL=0; 
	USHORT usL_BCD0_3,usL_BCD4_7,usL_BCD8_11,usL_BCD12_15;
	USHORT usH_BCD16_19,usH_BCD22_23,usH_BCD24_27,usH_BCD28_31;
	usL_BCD0_3 = (USHORT)GetBitsStatus(0,3,dwVersion,true);
	usL_BCD4_7 = (USHORT)GetBitsStatus(4,7,dwVersion,true);
	usL_BCD8_11 = (USHORT)GetBitsStatus(8,11,dwVersion,true);
	usL_BCD12_15 = (USHORT)GetBitsStatus(12,15,dwVersion,true);
	usH_BCD16_19 = (USHORT)GetBitsStatus(16,19,dwVersion,true);
	usH_BCD22_23 = (USHORT)GetBitsStatus(22,23,dwVersion,true);
	usH_BCD24_27 = (USHORT)GetBitsStatus(24,27,dwVersion,true);
	usH_BCD28_31 = (USHORT)GetBitsStatus(28,31,dwVersion,true);
	usH = usH_BCD16_19 + usH_BCD22_23*10 + usH_BCD24_27*100 +usH_BCD28_31*1000;
	usL = usL_BCD0_3 + usL_BCD4_7*10 + usL_BCD8_11*100 +usL_BCD12_15*1000;
	sprintf(szVersion,"%s:%d.%d",szCONST,usH,usL);
	return TRUE;
}
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szhwVersion[128] = {0},szdriverVersion[128] = {0},szlibVersion[128] = {0};
	char sztmp[1024] = {0};
	VERSIONINFO_STRUCT ver;
#ifdef MY_DEBUG
	BSTIOD48_GetVersion(hCard,&ver);
#else
	ver.driverVersion = 0x00010000;
	ver.hwVersion = 0x00010000;
	ver.libVersion = 0x00010000;
#endif
	Get_VersionInfo(ver.hwVersion,"硬件版本",szhwVersion);
	Get_VersionInfo(ver.driverVersion,"驱动版本",szdriverVersion);	
	Get_VersionInfo(ver.libVersion,"接口库版本",szlibVersion);
	
	sprintf(sztmp,"%s  %s  %s ",szhwVersion,szdriverVersion,szlibVersion);
	((CStatic*)(GetDlgItem(IDC_STATIC_DEVINFO)))->SetWindowText(sztmp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
