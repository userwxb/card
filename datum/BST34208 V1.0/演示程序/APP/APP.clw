; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "APP.h"

ClassCount=5
Class1=CAPPApp
Class2=CAPPDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_DIALOG_CARDID
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CCardId
Resource4=IDD_APP_DIALOG
Resource5=IDD_DIALOG_LOGO
Class5=CLogo
Resource6=IDR_MENU1

[CLS:CAPPApp]
Type=0
HeaderFile=APP.h
ImplementationFile=APP.cpp
Filter=N

[CLS:CAPPDlg]
Type=0
HeaderFile=APPDlg.h
ImplementationFile=APPDlg.cpp
Filter=D
LastObject=CAPPDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=APPDlg.h
ImplementationFile=APPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC_DEVINFO,static,1342308352

[DLG:IDD_APP_DIALOG]
Type=1
Class=CAPPDlg
ControlCount=5
Control1=IDC_LIST_DO,SysListView32,1350631937
Control2=IDC_BTN_OUTPUT,button,1342242816
Control3=IDC_LIST_DI,SysListView32,1350631937
Control4=IDC_BTN_INPUT,button,1342242816
Control5=IDC_BTN_INPUT_STOP,button,1342242816

[DLG:IDD_DIALOG_CARDID]
Type=1
Class=CCardId
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_CARDID,edit,1350639745
Control5=IDC_STATIC,static,1342308352

[CLS:CCardId]
Type=0
HeaderFile=CardId.h
ImplementationFile=CardId.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_CARDID
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=CAPPDlg
Command1=IDM_TYPE_DOA1
Command2=IDM_TYPE_DOA2
Command3=IDM_TYPE_DOB1
Command4=IDM_TYPE_DOB2
Command5=IDM_TYPE_DIA
Command6=IDM_TYPE_DIB
Command7=IDM_VERSION
CommandCount=7

[DLG:IDD_DIALOG_LOGO]
Type=1
Class=CLogo
ControlCount=1
Control1=IDC_STATIC,static,1342177294

[CLS:CLogo]
Type=0
HeaderFile=Logo.h
ImplementationFile=Logo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLogo

