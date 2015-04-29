// DialgDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Dialg.h"
#include "DialgDlg.h"
#include "Baseaddr.h"
#include "Introduce.h"
#include "AEC429D6_lib.h"
#include "setpulse.h"
#include "setup.h"
#include "lable.h"
#include <windowsx.h>
#include <math.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HDEVICE hDevce;

int CHNO_TMAX=0;
int CHNO_RMAX=0;

#define CM_INSERTITEM  WM_USER+6

CARDTYPE_STRUCT cardtype_struct;
RXCFGWORD_STRUCT  RXcfgword[8];
TXCFGWORD_STRUCT  TXcfgword[8];
BYTE  SdLable[8][4][256];
BYTE  SdLable_bk[8][4][256];
SYSTEMTIME stSysTime={0};
WORD wddepth[8]={0};
BOOL bladdtag[8]={0};

WORD wdperiod[8]={0};
BOOL blLtouch[8]={0};
WORD wdWordInt[8]={0};
BOOL blWtouch[8]={0};
WORD wddelaytime[8]={0};
BOOL blFallEdge[8]={0};
BOOL blRiseEdge[8]={0};
WORD wdTimeNum[8]={0};
WORD wdCount[8]={0};
BOOL blrexmode=0;
BOOL blTimeTx[8]={0};

BYTE dialog[3]={0};
DWORD dwTime;

BOOL blwait=0;

BYTE Cardid=0;

BOOL isNeedThread=FALSE;
HANDLE hThread=NULL; // handle to thread function
DWORD dwThreadId=0;

BOOL blRxNow=FALSE;
HWND ghWnd=NULL;

DWORD WINAPI ThreadFunc(LPVOID lpParam); 

HANDLE hevent=NULL;
FILE *file[8];

char AppPath[MAX_PATH];

CDialgDlg *dlgItem;

BOOL blrxreset[8]={0};
DWORD dwRexcnt[8]={0};
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialgDlg dialog

CDialgDlg::CDialgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialgDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialgDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST8, m_list8);
	DDX_Control(pDX, IDC_LIST7, m_list7);
	DDX_Control(pDX, IDC_LIST6, m_list6);
	DDX_Control(pDX, IDC_LIST5, m_list5);
	DDX_Control(pDX, IDC_LIST4, m_list4);
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST_TXX, m_listtx);
	DDX_Control(pDX, IDC_BUTTON_REX, m_btrex);
	DDX_Control(pDX, IDC_TAB_REV, m_tabrev);
	DDX_Control(pDX, IDC_EDIT_TXNUM, m_txnum);
	DDX_Control(pDX, IDC_EDIT_SendData, m_edsddata);
	DDX_Control(pDX, IDC_BUTTON_TX, m_bttx);
	DDX_Control(pDX, IDC_BUTTON_LOAD2, m_btsave);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_btload);
	DDX_Control(pDX, IDC_BUTTON_DELE, m_btdele);
	DDX_Control(pDX, IDC_BUTTON_CLEA, m_btclea);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btadd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialgDlg, CDialog)
	//{{AFX_MSG_MAP(CDialgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELE, OnButtonDele)
	ON_BN_CLICKED(IDC_BUTTON_CLEA, OnButtonClea)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_LOAD2, OnButtonLoad2)
	ON_EN_CHANGE(IDC_EDIT_SendData, OnChangeEDITSendData)
	ON_EN_KILLFOCUS(IDC_EDIT_SendData, OnKillfocusEDITSendData)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_REV, OnSelchangeTabRev)
	ON_COMMAND(ID_MEMUWORD, OnMemuword)
	ON_COMMAND(ID_MEMUPULSE, OnMemupulse)
	ON_COMMAND(ID_MEMUSD, OnMemusd)
	ON_BN_CLICKED(IDC_BUTTON_REX, OnButtonRex)
	ON_BN_CLICKED(IDC_BUTTON_TX, OnButtonTx)
	ON_BN_CLICKED(IDC_BUTTON_STOPTX, OnButtonStoptx)
	ON_MESSAGE(CM_INSERTITEM, OnMessage)
	ON_BN_CLICKED(IDC_BUTTON_ALLSELECT, OnButtonAllselect)
	ON_BN_CLICKED(IDC_BUTTON_NONESELECT, OnButtonNoneselect)
	ON_BN_CLICKED(IDC_CHECK_TMIT, OnCheckTmit)
	ON_COMMAND(ID_MEMURESET, OnMemureset)
	ON_BN_CLICKED(IDC_BUTTON_RXENABLEALL, OnButtonRxenableall)
	ON_BN_CLICKED(IDC_BUTTON_RXENABLENONE, OnButtonRxenablenone)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE0, OnCheckRxenable0)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE1, OnCheckRxenable1)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE2, OnCheckRxenable2)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE3, OnCheckRxenable3)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE4, OnCheckRxenable4)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE5, OnCheckRxenable5)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE6, OnCheckRxenable6)
	ON_BN_CLICKED(IDC_CHECK_RXENABLE7, OnCheckRxenable7)
	ON_BN_CLICKED(IDC_BUTTON_RALL, OnButtonRall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialgDlg message handlers

BOOL CDialgDlg::OnInitDialog()
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
	dlgItem = (CDialgDlg *)AfxGetMainWnd();

	int i=0;
	char c[80];
	DWORD dwsn=0;

	CIntroduce Introduce;
	Introduce.DoModal();

	CBaseaddr Baseaddr;

	if(Baseaddr.DoModal()!=IDOK)
	{
		ExitProcess(0);
		return(FALSE);
	}
	
	this->m_edsddata.LimitText(8);
	this->m_edsddata.SetWindowText("0");
	ghWnd=this->m_hWnd;

	for(i=0; i<8; i++)
	{
		RXcfgword[i].RBaudSel=0;      //100Kbps
		RXcfgword[i].RWLSel=0;			//32BIT
		TXcfgword[i].TBaudSel=0; 
		TXcfgword[i].TWLSel=0;
		TXcfgword[i].TParityEn=FALSE;     //parity enable
		TXcfgword[i].TParitySel=FALSE;		//parity select
		TXcfgword[i].SelfTest=FALSE;
	}
	::SetWindowText(::GetDlgItem(this->m_hWnd, IDC_EDIT_TXNUM), "0");
	this->m_listtx.SetBkColor(0x00696969);
	this->m_listtx.SetTextBkColor(0x00696969);
	this->m_listtx.SetTextColor(0x00ffffff);
	this->m_list1.SetBkColor(0x00696969);
	this->m_list1.SetTextBkColor(0x00696969);
	this->m_list1.SetTextColor(0x00ffffff);
	this->m_list2.SetBkColor(0x00696969);
	this->m_list2.SetTextBkColor(0x00696969);
	this->m_list2.SetTextColor(0x00ffffff);
	this->m_list3.SetBkColor(0x00696969);
	this->m_list3.SetTextBkColor(0x00696969);
	this->m_list3.SetTextColor(0x00ffffff);
	this->m_list4.SetBkColor(0x00696969);
	this->m_list4.SetTextBkColor(0x00696969);
	this->m_list4.SetTextColor(0x00ffffff);
	this->m_list5.SetBkColor(0x00696969);
	this->m_list5.SetTextBkColor(0x00696969);
	this->m_list5.SetTextColor(0x00ffffff);
	this->m_list6.SetBkColor(0x00696969);
	this->m_list6.SetTextBkColor(0x00696969);
	this->m_list6.SetTextColor(0x00ffffff);
	this->m_list7.SetBkColor(0x00696969);
	this->m_list7.SetTextBkColor(0x00696969);
	this->m_list7.SetTextColor(0x00ffffff);
	this->m_list8.SetBkColor(0x00696969);
	this->m_list8.SetTextBkColor(0x00696969);
	this->m_list8.SetTextColor(0x00ffffff);

	memset(AppPath, 0, sizeof(AppPath));

	if (GetCurrentDirectory(sizeof(AppPath), AppPath)==0)
	{
		MessageBox("加载环境配置信息失败!", "错误", MB_OK);
		return 0;
	}

#ifndef CARD_DEBUG	
	if(!AEC429D6_Open(&hDevce, Cardid))
	{
		MessageBox("打开板卡失败!", "错误", MB_OK | MB_ICONERROR);
		ExitProcess(0);
		return 0;
	}

	if(!AEC429D6_Reset(hDevce))
	{
		MessageBox("复位板卡失败!", "错误", MB_OK | MB_ICONERROR);
		if(!AEC429D6_Close(hDevce))
		{
			MessageBox("关闭板卡失败!", "错误", MB_OK | MB_ICONERROR);
			ExitProcess (0);
			return 0;
		}
		ExitProcess(0);
		return 0;
	}

	AEC429D6_GetCardType(hDevce, &cardtype_struct);
	CHNO_TMAX=cardtype_struct.TChannelNumber;
	CHNO_RMAX=cardtype_struct.RChannelNumber;
	if((CHNO_TMAX>8)||(CHNO_RMAX>8))
	{
		MessageBox("通道数大于8，程序退出", "", MB_OK | MB_ICONERROR);
		if(!AEC429D6_Reset(hDevce))
		{
			MessageBox("复位板卡失败!", "错误", MB_OK | MB_ICONERROR);
			if(!AEC429D6_Close(hDevce))
			{
				MessageBox("关闭板卡失败!", "错误", MB_OK | MB_ICONERROR);
				ExitProcess (0);
				return 0;
			}
			ExitProcess(0);
			return 0;
		}
		ExitProcess(0);
		return 0;
	}
	for(i=0; i<CHNO_RMAX; i=i+2)
	{
		if(!AEC429D6_SetRxCfgWord(hDevce, i/2, &RXcfgword[i/2]))
		{
			sprintf(c, "通道[%d]通道[%d]设置接收配置字失败!", i, i+1);
			MessageBox(c, "错误", MB_OK | MB_ICONERROR);
			return 0;
		}
	}
	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
		{
			if(!AEC429D6_SetTxCfgWord(hDevce, i+1, &TXcfgword[i]))
			{
				sprintf(c, "通道[%d]设置发送配置字失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return 0;
			}
		}
		else
		{
			if(!AEC429D6_SetTxCfgWord(hDevce, i, &TXcfgword[i]))
			{
				sprintf(c, "通道[%d]设置发送配置字失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONERROR);
				return 0;
			}
		}
	}
	dwsn=AEC429D6_GetCardSN(hDevce);
	if(cardtype_struct.BusType==0x01)
	{
		sprintf(c, "AEC429-PCI-%d%d/S6 SN:%08x", cardtype_struct.RChannelNumber, cardtype_struct.TChannelNumber, dwsn);
	}
	if(cardtype_struct.BusType==0x10)
	{
		sprintf(c, "AEC429-CPCI-%d%d/S6 SN:%08x", cardtype_struct.RChannelNumber, cardtype_struct.TChannelNumber, dwsn);
	}
	this->SetWindowText(c);

#else

	CHNO_TMAX=8;
	CHNO_RMAX=8;
	sprintf(c, "AEC429-CPCI/PCI-S6 SN:%08x", 0x07090301);
	this->SetWindowText(c);
#endif
	
	for(i=0; i<CHNO_RMAX; i++)
	{
		sprintf(c, "通道[%d]", i);
		this->m_tabrev.InsertItem(i, TEXT(c));
	}

	for(i=0; i<8; i++)
	{
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i), FALSE);
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i), FALSE);
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK1+i), FALSE);
	}

	for(i=0; i<CHNO_TMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i), BST_CHECKED);
	}

	for(i=0; i<8; i++)
	{
		if(i==0)
		{
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST1), TRUE);
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_STATIC_DNUM2), TRUE);
		}
		else
		{
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST1+i), FALSE);
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_STATIC_DNUM2+i), FALSE);
		}
	}

	for(i=0; i<CHNO_TMAX; i++)
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i), TRUE);

	for(i=0; i<CHNO_RMAX; i++)
	{
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i), TRUE);
		::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK1+i), TRUE);
	}

	this->m_list1.InsertColumn(0, "429数据");
	this->m_list1.SetColumnWidth(0, 80);
	this->m_list1.InsertColumn(1, "时标");
	this->m_list1.SetColumnWidth(1, 120);

	this->m_list2.InsertColumn(0, "429数据");
	this->m_list2.SetColumnWidth(0, 80);
	this->m_list2.InsertColumn(1, "时标");
	this->m_list2.SetColumnWidth(1, 120);

	this->m_list3.InsertColumn(0, "429数据");
	this->m_list3.SetColumnWidth(0, 80);
	this->m_list3.InsertColumn(1, "时标");
	this->m_list3.SetColumnWidth(1, 120);

	this->m_list4.InsertColumn(0, "429数据");
	this->m_list4.SetColumnWidth(0, 80);
	this->m_list4.InsertColumn(1, "时标");
	this->m_list4.SetColumnWidth(1, 120);

	this->m_list5.InsertColumn(0, "429数据");
	this->m_list5.SetColumnWidth(0, 80);
	this->m_list5.InsertColumn(1, "时标");
	this->m_list5.SetColumnWidth(1, 120);

	this->m_list6.InsertColumn(0, "429数据");
	this->m_list6.SetColumnWidth(0, 80);
	this->m_list6.InsertColumn(1, "时标");
	this->m_list6.SetColumnWidth(1, 120);

	this->m_list7.InsertColumn(0, "429数据");
	this->m_list7.SetColumnWidth(0, 80);
	this->m_list7.InsertColumn(1, "时标");
	this->m_list7.SetColumnWidth(1, 120);

	this->m_list8.InsertColumn(0, "429数据");
	this->m_list8.SetColumnWidth(0, 80);
	this->m_list8.InsertColumn(1, "时标");
	this->m_list8.SetColumnWidth(1, 120);
	
	this->m_listtx.InsertColumn(0, "429数据");
	this->m_listtx.SetColumnWidth(0, 100);

	//::EnableWindow(::GetDlgItem(this->m_hWnd, ID_MEMU1), FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialgDlg::OnPaint() 
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
HCURSOR CDialgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDialgDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDialgDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
//	CDialog::OnCancel();
}

void CDialgDlg::OnClose() 
{
	int i=0;
	if (MessageBox(TEXT("您确定要退出吗?"), TEXT("退出提示"), MB_YESNO | MB_ICONQUESTION)!=IDYES)
	{
		return;
	}
	if (hThread!=NULL)
	{
		isNeedThread = FALSE;
		::SetEvent(hevent);
		//  wait thread to terminated
		//
		{
			DWORD dwRet;
			do
			{
				dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
				if (dwRet != WAIT_OBJECT_0)
				{
					{
						MSG msg;
						while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
					}
				}
			} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
		}

		if(blrexmode)
		{
			blwait=TRUE;
		}
		
		if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE))==BST_CHECKED)
		{
			for(i=0; i<CHNO_RMAX; i++)
			{
				if(file[i]!=NULL)
					fclose(file[i]);
			}
		}
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE), TRUE);
		::CloseHandle(hThread);
		hThread = NULL;
	}
#ifndef CARD_DEBUG
	if(hDevce!=NULL)
	{
		AEC429D6_StartTimeTag(hDevce, FALSE, &stSysTime);
		AEC429D6_SetIntMaskReg(hDevce, FALSE);
		for(i=0;i<CHNO_RMAX;i++)
		{
			AEC429D6_Rx_Start(hDevce,i,FALSE);
		}
	}

	if(hevent!=NULL)
	{
		CloseHandle(hevent);
		hevent = NULL;
	}
	if(hDevce!=NULL)
	{

		if(!AEC429D6_Reset(hDevce))
		{
			MessageBox("复位板卡失败!", "错误", MB_OK | MB_ICONERROR);
		}
		if(!AEC429D6_Close(hDevce))
		{
			MessageBox("关闭板卡失败!", "错误", MB_OK | MB_ICONERROR);
		}
	}
#endif
	CDialog::OnCancel();
	CDialog::OnClose();
}

void CDialgDlg::OnButtonAdd() 
{
	int i=0;
	char c[80];
	DWORD bt=0;
	int itemidex=0;
	
	itemidex=this->m_listtx.GetSelectionMark();
	if (this->m_edsddata.LineLength(-1)==0)
	{
		MessageBox(TEXT("请先填写将要发送的数据!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

 	if (itemidex!=LB_ERR)
	{
		if ((this->m_listtx.GetItemCount())<FIFO_TMAX)
		{
			this->m_edsddata.GetWindowText(c, sizeof(c));
			bt = HEXS(c);
			sprintf(c, "%08x", bt);
			this->m_listtx.InsertItem(itemidex+1, c);
		}
	}
	else
	{
		if ((this->m_listtx.GetItemCount())<FIFO_TMAX)
		{
			this->m_edsddata.GetWindowText(c, sizeof(c));
			bt = HEXS(c);
			sprintf(c, "%08x", bt);
			this->m_listtx.InsertItem(this->m_listtx.GetItemCount(), c);
		}
	}

	i = this->m_listtx.GetItemCount();
	sprintf(c, "%d", i);
	this->m_txnum.SetWindowText(c);		
}

void CDialgDlg::OnButtonDele() 
{
	int i=0;
	int itemidex=0;
	char c[80];
                                      
	i = this->m_listtx.GetItemCount()-1;
	itemidex=this->m_listtx.GetSelectionMark();
	
	if (itemidex!=LB_ERR)
	{ 
		if ((this->m_listtx.GetItemCount())>0)
			this->m_listtx.DeleteItem(itemidex);		             
	}
	else
	{
		this->m_listtx.DeleteItem(i); 
	}

	i = this->m_listtx.GetItemCount();
	sprintf(c, "%ld", i);
	this->m_txnum.SetWindowText(c);			
}

void CDialgDlg::OnButtonClea() 
{
	int i=0;
	char c[80];

	this->m_listtx.DeleteAllItems();
	i = this->m_listtx.GetItemCount();
	sprintf(c, "%ld", i);
	this->m_txnum.SetWindowText(c);		
}

void CDialgDlg::OnButtonLoad() 
{
	char path[MAX_PATH];
	FILE *pf;
	char c[80];
	int i=0, l=0;
	DWORD bt=0;

	//  checking amount of Tx Data
	//
	i = this->m_listtx.GetItemCount();
	if (i>=FIFO_TMAX)
	{
		MessageBox(TEXT("发送数据列表中的数据已经达到最大限!\n\n请适当地删除发送列表窗口中的数据!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	l = i;

	//  show open file dialog
	//
	CFileDialog dlgOpenFile(TRUE, ".sdt", NULL, 
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						"sdt file(*.sdt)|*.sdt||", NULL);
	if ((dlgOpenFile.DoModal())!=IDOK)
	{
		return;
	}

	//	Get File Name
	//
	if ((dlgOpenFile.GetPathName()).GetLength()>=MAX_PATH)
	{
		MessageBox(TEXT("所选文件路径长度超出指定范围,请选择一个较短的路径名称!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	memset(path, 0, sizeof(path));
	strcpy(path, (dlgOpenFile.GetPathName()).GetBuffer((dlgOpenFile.GetPathName()).GetLength()));

	//	Open File
	//
	pf = fopen(path, "r+");
	if (pf == NULL)
	{
		MessageBox(TEXT("加载数据文件失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

	long filelen = _filelength(_fileno(pf));
	if(filelen==0)
	{
		MessageBox(TEXT("数据文件为空文件!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		fclose(pf);
		return;
	}
	//_FineFirst(pf);
	//	Read Data
	//
	while ((feof(pf)==0)&&(l<FIFO_TMAX))
	{
		strcpy(c, "");
		fscanf(pf, "%s\n", c);
		bt = (DWORD)HEXS(c);
		sprintf(c, "%08x", bt);
		this->m_listtx.InsertItem(this->m_listtx.GetItemCount(), c);
		l++;
	}

	fclose(pf); // Close File

	if (i==l)
	{
		MessageBox(TEXT("数据文件为空,请先对发送列表中的数据进行保存!"), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
	}

	sprintf(c, "%ld", this->m_listtx.GetItemCount());
	this->m_txnum.SetWindowText(c);		
}

void CDialgDlg::OnButtonLoad2() 
{
	char path[MAX_PATH];
	FILE *pf;
	char c[80];
	int i=0, l=0;
	int clen=0;

	//  checking amount of Tx Data
	//
	i = this->m_listtx.GetItemCount();
	if (i==0)
	{
		MessageBox(TEXT("发送数据列表不能为空!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	l = i;

	//  show save file dialog
	//
	CFileDialog dlgSaveFile(FALSE, ".sdt", NULL, 
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						"sdt file(*.sdt)|*.sdt||", NULL);
	if ((dlgSaveFile.DoModal())!=IDOK)
	{
		return;
	}

	//	Get File Name
	//
	if ((dlgSaveFile.GetPathName()).GetLength()>=MAX_PATH)
	{
		MessageBox(TEXT("所选文件路径长度超出指定范围,请选择一个较短的路径名称!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	memset(path, 0, sizeof(path));
	strcpy(path, (dlgSaveFile.GetPathName()).GetBuffer((dlgSaveFile.GetPathName()).GetLength()));
	
	//	Open File
	//
	pf = fopen(path, "w+");
	if (pf == NULL)
	{
		MessageBox(TEXT("创建数据文件失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

	//	Write Data
	//
	for (i=0; i<l; i++)
	{
		memset(c, 0, sizeof(c));
		this->m_listtx.GetItemText(i, 0, c, sizeof(c));////
		fprintf(pf, "%s\n", c);
	}

	fclose(pf); // Close File		
}

void CDialgDlg::OnChangeEDITSendData() 
{
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->m_edsddata.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->m_edsddata.GetSel();

	this->m_edsddata.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if (((tc>='a')&&(tc<='f'))||((tc>='0')&&(tc<='9'))||((tc>='A')&&(tc<='F')))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->m_edsddata.SetWindowText(s);
	this->m_edsddata.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CDialgDlg::OnKillfocusEDITSendData() 
{
	if (this->m_edsddata.LineLength(-1)==0)
	{
		this->m_edsddata.SetWindowText(TEXT("0"));
	}	
}

void CDialgDlg::OnSelchangeTabRev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int chno=0;
	int i=0;
	chno=this->m_tabrev.GetCurSel();
	for(i=0; i<CHNO_RMAX; i++)
	{
		if(i==chno)
		{
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST1+i), SW_SHOW);
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_STATIC_DNUM2+i), TRUE);
		}
		else
		{
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST1+i), SW_HIDE);
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_STATIC_DNUM2+i), FALSE);
		}
	}
	
	*pResult = 0;
}

void CDialgDlg::OnMemuword() 
{
	if(blRxNow)
	{
		this->OnButtonRex();
	}
	if(dialog[0]==1)
	{
		MessageBox("基本设置窗口已打开!", "错误", MB_OK | MB_ICONWARNING);
		return;
	}

	Csetup *setup;
	setup = new Csetup;
	setup->Create(IDD_DIALOG1, this);
	setup->ShowWindow(SW_SHOW);	
	dialog[0]=1;
}

void CDialgDlg::OnMemupulse() 
{
	int i=0; 
	char c[80];
	if(blRxNow)
	{
		/*for(i=0; i<CHNO_TMAX; i++)
		{
			if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
			{
				if(!AEC429D6_TxStart(hDevce, i+1, FALSE))
				{
					sprintf(c, "通道%d停止发送失败!", i+1);
					MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
					return;
				}
			}
			else
			{
				if(!AEC429D6_TxStart(hDevce, i, FALSE))
				{
					sprintf(c, "通道%d停止发送失败!", i);
					MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
					return;
				}
			}
		}*/
		this->OnButtonRex();
	}
	if(dialog[1]==1)
	{
		MessageBox("脉冲设置窗口已打开!", "错误", MB_OK | MB_ICONWARNING);
		return;
	}
	Csetpulse *setpulse;
	setpulse = new Csetpulse;
	setpulse->Create(IDD_DIALOG2, this);
	setpulse->ShowWindow(SW_SHOW);
	dialog[1]=1;
}

void CDialgDlg::OnMemusd() 
{
	if(blRxNow)
	{
		this->OnButtonRex();
	}
	if(dialog[2]==1)
	{
		MessageBox("标号设置窗口已打开!", "错误", MB_OK | MB_ICONWARNING);
		return;
	}
	Clable *lable;
	lable = new Clable;
	lable->Create(IDD_DIALOG3, this);
	lable->ShowWindow(SW_SHOW);
	dialog[2]=1;
}

void CDialgDlg::OnButtonTx() 
{
	int i=0, l=0;
	char c[128];
	WORD wdTxBufLen=0;
	DWORD dwTxBuf[1024];
	WORD wdRealLen=0;

	//  get Tx data
	//
	wdTxBufLen = 0;
	memset(dwTxBuf, 0, sizeof(DWORD)*FIFO_TMAX);
	l = this->m_listtx.GetItemCount();
	if (l==0)
	{
		MessageBox(TEXT("发送数据列表不能为空!"), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (l>FIFO_TMAX)
		l = FIFO_TMAX;

	//  fill Tx Buffer
	//
	i = 0;
	while (i<l)
	{
		this->m_listtx.GetItemText(i, 0, c, sizeof(c));;
		dwTxBuf[wdTxBufLen] = HEXS(c);
		wdTxBufLen++;
		i++;
	}
	
	for(i=0; i<CHNO_TMAX; i++)
	{
		if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i))==BST_CHECKED)
		{
			if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
			{
				if((!blLtouch[i])&&(!blWtouch[i]))
				{
					if((AEC429D6_TxFIFOSTR(hDevce, i+1)&AEC429D6_FIFOEMPTY)==AEC429D6_FIFOEMPTY)
					{
						AEC429D6_TxWrite(hDevce, i+1, wdTxBufLen, dwTxBuf, &wdRealLen);
					}
				}
				else
				{
					if(!AEC429D6_EnableTimerMode(hDevce, i+1, TRUE))
					{
						sprintf(c, "通道%d使能定时发送失败!", i);
						MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
						return;
					}
					if(blTimeTx[i])
					{
						if(!AEC429D6_TxStart(hDevce, i+1, FALSE))
						{
							sprintf(c, "通道%d停止发送失败!", i);
							MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
							return;
						}
					}
					AEC429D6_TxWrite(hDevce, i+1, wdTxBufLen, dwTxBuf, &wdRealLen);
					if(blTimeTx[i])
					{
						if(!AEC429D6_TxStart(hDevce, i+1, TRUE))
						{
							sprintf(c, "通道%d开始发送失败!", i);
							MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
							return;
						}
						blTimeTx[i]=FALSE;
					}
				}
			}
			else
			{
				if((!blLtouch[i])&&(!blWtouch[i]))
				{
					if((AEC429D6_TxFIFOSTR(hDevce, i)&AEC429D6_FIFOEMPTY)==AEC429D6_FIFOEMPTY)
					{
						AEC429D6_TxWrite(hDevce, i, wdTxBufLen, dwTxBuf, &wdRealLen);
					}
				}
				else
				{
					if(!AEC429D6_EnableTimerMode(hDevce, i, TRUE))
					{
						sprintf(c, "通道%d使能定时发送失败!", i);
						MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
						return;
					}
					if(blTimeTx[i])
					{
						if(!AEC429D6_TxStart(hDevce, i, FALSE))
						{
							sprintf(c, "通道%d停止发送失败!", i);
							MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
							return;
						}
					}
					AEC429D6_TxWrite(hDevce, i, wdTxBufLen, dwTxBuf, &wdRealLen);
					if(blTimeTx[i])
					{
						if(!AEC429D6_TxStart(hDevce, i, TRUE))
						{
							sprintf(c, "通道%d开始发送失败!", i);
							MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
							return;
						}
						blTimeTx[i]=FALSE;
					}
				}
			}
		}
	}
}

void CDialgDlg::OnButtonStoptx() 
{
	int i=0;
	char c[80];

	for(i=0; i<CHNO_TMAX; i++)
	{
		if((CHNO_TMAX==2)&&(CHNO_RMAX==4)&&(i==1))
		{
			if(!AEC429D6_TxStart(hDevce, i+1, FALSE))
			{
				sprintf(c, "通道%d停止发送失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				return;
			}
		}
		else
		{
			if(!AEC429D6_TxStart(hDevce, i, FALSE))
			{
				sprintf(c, "通道%d停止发送失败!", i);
				MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				return;
			}
		}
		blTimeTx[i]=TRUE;
	}
}

void CDialgDlg::OnButtonRex() 
{
	int i=0;
	char c[80];
	char path[MAX_PATH];

	if (blRxNow)
	{
		for(i=0;i<CHNO_RMAX;i++)
		{
			if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i))==BST_CHECKED)
			{
				if(!AEC429D6_Rx_Start(hDevce, i, FALSE))
				{
					sprintf(c,"通道%d停止接收使能失败!",i);
					MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				}
			}
		}
		if (hThread!=NULL)
		{
			isNeedThread = FALSE;
			::ResetEvent(hevent);
			::SetEvent(hevent);
			//  wait thread to terminated
			//
			{
				DWORD dwRet;
				do
				{
					dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, 100, QS_ALLINPUT);
					if (dwRet != WAIT_OBJECT_0)
					{
						{
							MSG msg;
							while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}
						}
					}
				} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
			}

			if(blrexmode)
			{
				blwait=TRUE;
				::ResetEvent(hevent);
				::SetEvent(hevent);	
			}

			::CloseHandle(hThread);
			hThread = NULL;
		}

		this->m_btrex.SetWindowText(TEXT("开始接收"));
		blRxNow = FALSE;
		if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE))==BST_CHECKED)
		{
			for(i=0; i<CHNO_RMAX; i++)
			{
				if(file[i]!=NULL)
					fclose(file[i]);
			}
		}
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE), TRUE);
	}
	else
	{
		//  Init Rx ListBox
		//
		for (i=0; i<CHNO_RMAX; i++)
		{
			dwRexcnt[i] = 0;
			::SetWindowText(::GetDlgItem(this->m_hWnd, IDC_STATIC_DNUM2+i), TEXT(" 0"));
		}
		::EnableWindow(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE), FALSE);
		this->m_list1.DeleteAllItems();
		this->m_list2.DeleteAllItems();
		this->m_list3.DeleteAllItems();
		this->m_list4.DeleteAllItems();
		this->m_list5.DeleteAllItems();
		this->m_list6.DeleteAllItems();
		this->m_list7.DeleteAllItems();
		this->m_list8.DeleteAllItems();

		// create thread to receive data
		//
		if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SAVE))==BST_CHECKED)
		{
			for(i=0; i<CHNO_RMAX; i++)
			{
				strcpy(path, AppPath);
				sprintf(c, "\\通道[%d].txt", i);
				strcat(path, c);
				file[i]=fopen(path, "w+");
			}
		}

		for(i=0;i<CHNO_RMAX;i++)
		{
			if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i))==BST_CHECKED)
			{
				if(!AEC429D6_Rx_Start(hDevce, i, TRUE))
				{
					sprintf(c,"通道%d开启接收使能失败!",i);
					MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				}
			}
		}
		isNeedThread = TRUE;
		hThread = ::CreateThread(NULL, 0, ThreadFunc, (LPVOID)ghWnd, 0, &dwThreadId);   	

		if (hThread==NULL)
		{
			MessageBox(TEXT("无法创建接收线程,请重新启动应用程序!"), TEXT("错误"), MB_OK | MB_ICONERROR);
			for(i=0; i<CHNO_RMAX; i++)
			{
				if(file[i]!=NULL)
					fclose(file[i]);
			}
			return;
		}
		this->m_btrex.SetWindowText(TEXT("停止接收"));
		blRxNow = TRUE;
	}
}

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int i=0; 
	char c[80];
	DWORD dwRxLen=0;

	while(isNeedThread)
	{
		for(i=0; i<CHNO_RMAX; i++)
		{	
			if(blrxreset[i])
			{
				if(!AEC429D6_ResetRxFIFO(hDevce,i))
				{
					sprintf(c, "通道[%d]复位缓冲区失败", i);
					MessageBox(NULL,c, "错误", MB_OK | MB_ICONWARNING);
				}
				blrxreset[i]=FALSE;
			}
		}
		if(!blrexmode)
		{
			AEC429D6_SetIntMaskReg(hDevce, FALSE);
			for(i=0;(i<CHNO_RMAX) && (isNeedThread);i++)
			{
				dwRxLen=0;				
				dwRxLen=AEC429D6_RxLen(hDevce, i);
				if(dwRxLen>0)
				{
					dlgItem->RevData(i,dwRxLen);
				}
			}
		}
		else
		{
			if(WaitForSingleObject(hevent,100) == WAIT_OBJECT_0)
			{	
				if(blwait)
				{
					blwait=FALSE;
				}				
				else			
				{	
					for(i=0;(i<CHNO_RMAX) && (isNeedThread);i++)
					{
						dwRxLen=0;				
						dwRxLen=AEC429D6_RxLen(hDevce, i);
						if(dwRxLen>0)
						{
							dlgItem->RevData(i,dwRxLen);
						}
					}
				}
				//::ResetEvent(hevent);
			}
		}
	}
	ExitThread(0);
	return 0;
}

void CDialgDlg::OnMessage(WPARAM subidx, LPARAM data)
{
	int i=0;
	char c[80];
	int chno=0;
	WORD hour=0, minute=0, second=0, millseconds=0;
	DWORD t=0, d=0;

	if(subidx>0xff)
	{
		//  calculate the hour / minute / second / millseconds
		//
		t = dwTime + (data/20);
		hour = (WORD) (t/3600000);
		t = t - hour*3600000;
		minute = (WORD) (t/60000);
		t = t - minute*60000;
		second = (WORD) (t/1000);
		millseconds = (WORD)(t - second*1000);

		//  link string follow the data
		//
		memset(c, 0, sizeof(c));
		sprintf(c, "%02d:%02d:%02d.%03d", hour, minute, second, millseconds);

		subidx=subidx-0x8000;
		chno=subidx&0xff00;
		chno=chno>>8;
		subidx=subidx&0x00ff;
		
		switch(chno)
		{
		case 0:
			this->m_list1.SetItemText(this->m_list1.GetItemCount()-1,subidx, c);
			break;
		case 1:
			this->m_list2.SetItemText(this->m_list2.GetItemCount()-1,subidx, c);
			break;
		case 2:
			this->m_list3.SetItemText(this->m_list3.GetItemCount()-1,subidx, c);
			break;
		case 3:
			this->m_list4.SetItemText(this->m_list4.GetItemCount()-1,subidx, c);
			break;
		case 4:
			this->m_list5.SetItemText(this->m_list5.GetItemCount()-1,subidx, c);
			break;
		case 5:
			this->m_list6.SetItemText(this->m_list6.GetItemCount()-1,subidx, c);
			break;
		case 6:
			this->m_list7.SetItemText(this->m_list7.GetItemCount()-1,subidx, c);
			break;
		case 7:
			this->m_list8.SetItemText(this->m_list8.GetItemCount()-1,subidx, c);
			break;
		}
	}
	else
	{
		sprintf(c, "%08x", data);
		chno=subidx;

		switch(chno)
		{
		case 0:
			this->m_list1.InsertItem(this->m_list1.GetItemCount(), c);
			break;
		case 1:
			this->m_list2.InsertItem(this->m_list2.GetItemCount(),c);
			break;
		case 2:
			this->m_list3.InsertItem(this->m_list3.GetItemCount(), c);
			break;
		case 3:
			this->m_list4.InsertItem(this->m_list4.GetItemCount(), c);
			break;
		case 4:
			this->m_list5.InsertItem(this->m_list5.GetItemCount(),c);
			break;
		case 5:
			this->m_list6.InsertItem(this->m_list6.GetItemCount(), c);
			break;
		case 6:
			this->m_list7.InsertItem(this->m_list7.GetItemCount(), c);
			break;
		case 7:
			this->m_list8.InsertItem(this->m_list8.GetItemCount(), c);
			break;
		}
	}
}

void CDialgDlg::OnButtonAllselect() 
{
	int i=0;
	for(i=0; i<CHNO_TMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i), BST_CHECKED);
	}
}

void CDialgDlg::OnButtonNoneselect() 
{
	int i=0;
	for(i=0; i<CHNO_TMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TX1+i), BST_UNCHECKED);
	}
}

void CDialgDlg::OnCheckTmit() 
{
	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TMIT))==BST_CHECKED)
		AEC429D6_WordConvertEn(hDevce, TRUE);
	else
		AEC429D6_WordConvertEn(hDevce, FALSE);
}

void CDialgDlg::OnMemureset() 
{
	int i=0;
	char c[120];
	if(!AEC429D6_Reset(hDevce))
	{
		MessageBox("板卡复位失败!", "错误", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		MessageBox("板卡复位成功!", "提示", MB_OK | MB_ICONWARNING);
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TMIT), BST_UNCHECKED);

	
		for(i=0; i<CHNO_RMAX; i++)
		{
			Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i), BST_UNCHECKED);
			if(!AEC429D6_Rx_Start(hDevce, i, FALSE))
			{
				sprintf(c, "通道%d停止接收使能失败!\n", i);
				MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
			}
		}	
	}
	
}

void CDialgDlg::OnButtonRxenableall() 
{
	int i=0;
	char c[120];
	for(i=0; i<CHNO_RMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i), BST_CHECKED);
		if(!AEC429D6_Rx_Start(hDevce, i, TRUE))
		{
			sprintf(c, "通道%d开启接收使能失败!\n", i);
			MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
		}
	}
}

void CDialgDlg::OnButtonRxenablenone() 
{
	int i=0;
	char c[120];
	for(i=0; i<CHNO_RMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i), BST_UNCHECKED);
		if(!AEC429D6_Rx_Start(hDevce, i, FALSE))
		{
			sprintf(c, "通道%d停止接收使能失败!\n", i);
			MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
		}
	}
}

void CDialgDlg::OnCheckRxenable0() 
{
	EnRxRec(0);
}

void CDialgDlg::OnCheckRxenable1() 
{
	EnRxRec(1);
}

void CDialgDlg::OnCheckRxenable2() 
{
	EnRxRec(2);
}

void CDialgDlg::OnCheckRxenable3() 
{
	EnRxRec(3);
}

void CDialgDlg::OnCheckRxenable4() 
{
	EnRxRec(4);
}

void CDialgDlg::OnCheckRxenable5() 
{
	EnRxRec(5);
}

void CDialgDlg::OnCheckRxenable6() 
{
	EnRxRec(6);
}

void CDialgDlg::OnCheckRxenable7() 
{
	EnRxRec(7);
}

void CDialgDlg::OnButtonRall() 
{
	// TODO: Add your control notification handler code here
	int i=0;
	char c[80];

	if(isNeedThread)
	{
		for(i=0;i<CHNO_RMAX;i++)
		{
			if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK1+i))==BST_CHECKED)
			{
				blrxreset[i] = TRUE;
			}
		}
	}
	else
	{
		for(i=0;i<CHNO_RMAX;i++)
		{
			if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK1+i))==BST_CHECKED)
			{
				if(!AEC429D6_ResetRxFIFO(hDevce,i))
				{
					sprintf(c, "通道[%d]复位缓冲区失败", i);
					MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
				}	
			}
		}
	}
}

void CDialgDlg::EnRxRec(BYTE chno)
{
	BYTE i = chno;

	if(Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_RXENABLE0+i))==BST_CHECKED)
	{
		if(!AEC429D6_Rx_Start(hDevce, i, TRUE))
		{
			MessageBox("通道0开启接收使能失败!", "错误", MB_OK | MB_ICONWARNING);
		}
	}
	else
	{
		if(!AEC429D6_Rx_Start(hDevce, i, FALSE))
		{
			MessageBox("通道0关闭接收使能失败!", "错误", MB_OK | MB_ICONWARNING);
		}
	}
}

void CDialgDlg::EnRedraw(BYTE chno,BOOL En)
{
	BYTE i = chno;
	BOOL enbl = En;

	switch(i)
	{
	case 0:
		this->m_list1.SetRedraw(enbl);
		break;
	case 1:
		this->m_list2.SetRedraw(enbl);
		break;
	case 2:
		this->m_list3.SetRedraw(enbl);
		break;
	case 3:
		this->m_list4.SetRedraw(enbl);
		break;
	case 4:
		this->m_list5.SetRedraw(enbl);
		break;
	case 5:
		this->m_list6.SetRedraw(enbl);
		break;
	case 6:
		this->m_list7.SetRedraw(enbl);
		break;
	case 7:
		this->m_list8.SetRedraw(enbl);
		break;
	}
}

DWORD dwRexBuf[4096];

void CDialgDlg::RevData(BYTE i,DWORD len)
{
	DWORD dwRxLen=0;
	BYTE chno=i;
	int j=0;
	int msgl=0;
	char c[80];
	WORD wdRexLen=0;
	WORD wdRealLen=0;

	WORD hour=0, minute=0, second=0, millseconds=0;
	DWORD t=0, d=0;

	dwRxLen = len;

	if(bladdtag[chno])
	{
		if(fmod(dwRxLen, 2)==1)
			dwRxLen--;
	}
	if(dwRxLen>1024)
		dwRxLen=1024;
	
	memset(dwRexBuf,0,sizeof(dwRexBuf));
	AEC429D6_RxRead(hDevce, chno, (WORD)dwRxLen, dwRexBuf, &wdRealLen);
	if(dwRxLen!=wdRealLen)
	{
		sprintf(c, "通道[%d]接收数据量与实际接收的数据量不等", chno);
		MessageBox(c, "错误", MB_OK | MB_ICONWARNING);
		::SetWindowText(::GetDlgItem(ghWnd, IDC_BUTTON_REX), "开始接收");
		hThread=NULL;
		blRxNow=FALSE;
		return;
	}
	msgl=0;
	msgl=chno<<8;
	msgl=msgl+0x8000;
	this->EnRedraw(chno,FALSE);
	for(j=0; (j<wdRealLen) && (isNeedThread); j++)
	{
		if(Button_GetCheck(::GetDlgItem(ghWnd, IDC_CHECK_VIEW))==BST_CHECKED)
		{
			if(!bladdtag[chno])
				::SendMessage(ghWnd, CM_INSERTITEM, chno, dwRexBuf[j]);	
			else
			{
				if(j%2==0)
					::SendMessage(ghWnd, CM_INSERTITEM, chno, dwRexBuf[j]);
				else
					::SendMessage(ghWnd, CM_INSERTITEM, msgl+1, dwRexBuf[j]);
			}
		}
		if(Button_GetCheck(::GetDlgItem(ghWnd, IDC_CHECK_SAVE))==BST_CHECKED)
		{
			if(!bladdtag[chno])
			{
				fprintf(file[chno], "%08x\n", dwRexBuf[j]);
			}
			else
			{
				if(j%2==1)
				{
					t = dwTime + (dwRexBuf[j]/20);
					hour = (WORD) (t/3600000);
					t = t - hour*3600000;
					minute = (WORD) (t/60000);
					t = t - minute*60000;
					second = (WORD) (t/1000);
					millseconds = (WORD)(t - second*1000);
					fprintf(file[chno], "  %02d:%02d:%02d.%03d\n", hour, minute, second, millseconds);
				}
				else
				{
					fprintf(file[chno], "%08x", dwRexBuf[j]);
				}			
			}	
		}
		dwRexcnt[chno]++;
	}

	this->EnRedraw(chno,TRUE);
	sprintf(c, " %d", dwRexcnt[chno]);
	::SetWindowText(::GetDlgItem(ghWnd, IDC_STATIC_DNUM2+chno), c);
}
