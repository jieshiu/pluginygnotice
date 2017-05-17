; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CYgNoticeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "YgTabFlash.h"
CDK=Y

ClassCount=4
Class1=CYgTabFlashCtrl
Class2=CYgTabFlashPropPage

ResourceCount=4
Resource1=IDD_ABOUTBOX_YGTABFLASH
LastPage=0
Resource2=IDD_FORMVIEW
Class3=CYgNoticeDlg
Resource3=IDD_PROPPAGE_YGTABFLASH
Class4=CTalkDlg
Resource4=IDD_DLGTALK

[CLS:CYgTabFlashCtrl]
Type=0
HeaderFile=YgTabFlashCtl.h
ImplementationFile=YgTabFlashCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CYgTabFlashCtrl

[CLS:CYgTabFlashPropPage]
Type=0
HeaderFile=YgTabFlashPpg.h
ImplementationFile=YgTabFlashPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_YGTABFLASH]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_YGTABFLASH]
Type=1
Class=CYgTabFlashPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_FORMVIEW]
Type=1
Class=CYgNoticeDlg
ControlCount=12
Control1=IDC_STATIC1,static,1073872896
Control2=IDC_EDIT2,edit,1082196096
Control3=IDC_BUTTON1,button,1073807360
Control4=IDC_BTNTALK,button,1342242816
Control5=IDC_LIST1,SysListView32,1350631425
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1216413824
Control9=IDC_STATIC2,static,1073872896
Control10=IDC_BUTTON2,button,1073807360
Control11=IDC_OALINK1,static,1342308352
Control12=IDC_OALINK2,static,1342308352

[CLS:CYgNoticeDlg]
Type=0
HeaderFile=YgNoticeDlg.h
ImplementationFile=YgNoticeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CYgNoticeDlg
VirtualFilter=dWC

[DLG:IDD_DLGTALK]
Type=1
Class=CTalkDlg
ControlCount=6
Control1=IDC_BTNSEND,button,1342242816
Control2=IDC_BTNCLOSE,button,1342242816
Control3=IDC_BTNRECODE,button,1342242816
Control4=IDC_STATIC_NAME,static,1342308352
Control5=IDC_RICHEDIT1,RICHEDIT,1353779396
Control6=IDC_RICHEDIT2,RICHEDIT,1353777348

[CLS:CTalkDlg]
Type=0
HeaderFile=TalkDlg.h
ImplementationFile=TalkDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RICHEDIT2
VirtualFilter=dWC

