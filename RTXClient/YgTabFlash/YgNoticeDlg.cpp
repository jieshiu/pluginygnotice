// YgNoticeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YgTabFlash.h"
#include "YgNoticeDlg.h"
#include "MsgWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYgNoticeDlg dialog


CYgNoticeDlg::CYgNoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYgNoticeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYgNoticeDlg)
	m_Notice = _T("");
	//}}AFX_DATA_INIT
	m_pDlg=NULL;
	m_ptrRoot=NULL;	
	m_bAdmin=FALSE;
	m_lNoticeNotReadCount=0;
	m_csLocalAccount=_T("");
	m_csAccountPath=_T("");
	m_csReceiver=_T("");	
	
}


void CYgNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYgNoticeDlg)
	DDX_Control(pDX, IDC_BTNTALK, m_talk);
	DDX_Control(pDX, IDC_BUTTON1, m_sendnotice);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_Notice);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_OALINK1, m_OALink1);
	DDX_Control(pDX, IDC_OALINK2, m_OALink2);
}


BEGIN_MESSAGE_MAP(CYgNoticeDlg, CDialog)
	//{{AFX_MSG_MAP(CYgNoticeDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BTNTALK, OnBtnTalk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYgNoticeDlg message handlers
void CYgNoticeDlg::Init(IRTXCRootPtr ptrRoot)
{
	m_ptrRoot = ptrRoot;	
	HRESULT hr;

	m_csLocalAccount = (LPCTSTR)m_ptrRoot->Account; 
	//得到用户个人文件夹目录		
	hr = m_ptrRoot->get_FileListPath((BSTR *)&m_csAccountPath);
	if(SUCCEEDED(hr))
	{
		_trace(_T("YgTabFlash:CYgNoticeDlg:Init,AccountPath[%s]"),m_csAccountPath);
		CString cstmp;
		cstmp.Format(_T("%sAccounts\\%s\\ygnoticelog.txt"),m_csAccountPath,m_csLocalAccount);
		_trace(_T("YgTabFlash:CYgNoticeDlg:Init,cstmp[%s]"),cstmp);


		m_statusLog.Init(cstmp);   
		m_statusLog.PrintTime(FALSE);
		m_statusLog.PrintAppName(FALSE);
	}
	
}

void CYgNoticeDlg::OnViewTips(CString key) 
{
	_trace(_T("YgTabFlash:CYgNoticeDlg::OnViewTips"));	
	/*if(m_pMsgWindow == NULL)
	{
		m_pMsgWindow=new CMsgWnd;
		CMsgWnd& msgWindow=*m_pMsgWindow;
		msgWindow.SetPromptCaption(_T("RTX"));
		msgWindow.SetPromptMessage(key);
		msgWindow.CreateMsgWindow();
		msgWindow.ShowWindow(SW_SHOW);
		msgWindow.UpdateWindow();
	}
	else
	{
		CMsgWnd& msgWindow=*m_pMsgWindow;
		msgWindow.SetPromptCaption(_T("RTX"));
		msgWindow.SetPromptMessage(key);
		msgWindow.ShowWindow(SW_SHOW);
		msgWindow.UpdateWindow();
		msgWindow.StartTimer();		
	}*/

	CMsgWnd* m_pMsgWindow=new CMsgWnd;
	CMsgWnd& msgWindow=*m_pMsgWindow;
	msgWindow.SetPromptCaption(_T("RTX"));
	msgWindow.SetPromptMessage(key);
	msgWindow.CreateMsgWindow();
	msgWindow.ShowWindow(SW_SHOW);
	msgWindow.UpdateWindow();	
}

void CYgNoticeDlg::SetRTXRight()
{
	HRESULT hr;
	/*
	CComPtr<IAppRoot> ptrAppRoot=NULL;
	REFIID iid1 = IID_IAppRoot;
	ExternalQueryInterface(&iid1,  (LPVOID*)&ptrAppRoot);

	if(ptrAppRoot != NULL)
	{
		CComPtr<IRTXCCRight> ptrRight=NULL;
		//IRTXCCRight ptrRight=NULL;			
		hr = ptrAppRoot->GetAppObject(_variant_t("RTXPlugin.CLientRightMgr"),(IDispatch **)&ptrRight);
		long bCanNotSendBroadcast=1;
		if(SUCCEEDED(hr))
		{			
			_variant_t lVal;
			ptrRight->GetGivenRightInfo(_bstr_t("RIGHT_INNER_SEND_BROADCAST_MSG_ONLY_CURRENT_DEPT"),&lVal);
			bCanNotSendBroadcast=lVal;
			if(bCanNotSendBroadcast == 0)
			{
				m_bCanNotSendBroadcast=FALSE;
			}
			else
			{
				m_bCanNotSendBroadcast=TRUE;
			}

		}		
	}*/
	_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-m_ptrRoot:[%x]"),m_ptrRoot);
	if(m_ptrRoot == NULL)
	{
		return;
	}
	CComQIPtr<IRTXCCRight> pRightModule = m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_RIGHT];
	if(pRightModule != NULL)
	{		
		_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-pRightModule:[%x]"),pRightModule);
		CString role;
		BSTR bstrText; 
		hr=pRightModule->GetClientRoleList(&bstrText);
		if(SUCCEEDED(hr))
		{
			_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-GetClientRoleList Suc!"));
			role=bstrText;					
			int ret=role.Find(_T("管理员"));		
			if(ret != -1)
			{
				_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-role ret:[%d]!"),ret);
				m_bAdmin=TRUE;
			}
			else
			{
				_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-role ret == -1"));
				m_bAdmin=FALSE;
			}			
		}		
		else
		{
			_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-GetClientRoleList Fail!"));
		}
	}
	else
	{
		_trace(_T("YgTabFlash:CYgNoticeDlg::SetRTXRight-pRightModule =NULL!"));
	}


	if(m_bAdmin)
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	}
}

BOOL CYgNoticeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	//GetDlgItem(IDC_BUTTON1)->SetWindowText (_T("发送"));
	CRect rt;
	double m_width=rt.Width()/4;
	m_list.GetClientRect(rt);
	m_list.InsertColumn(0,_T("接收人"),LVCFMT_LEFT,rt.Width()/5);
	m_list.InsertColumn(1,_T("时间"),LVCFMT_LEFT,rt.Width()/5);
	m_list.InsertColumn(2,_T("级别"),LVCFMT_LEFT,rt.Width()/5);
	m_list.InsertColumn(3,_T("公告内容"),LVCFMT_LEFT,rt.Width()/5);
	m_list.InsertColumn(4,_T("状态"),LVCFMT_LEFT,rt.Width()/5);

	/*m_bttWnd.Create(this);
	m_bttWnd.SetWidth(200);
	m_bttWnd.SetBkColor(RGB(213,253,224)); //RGB(210,210,255) violet
	m_bttWnd.SetFrameColor(RGB(0,106,53));

	m_bttWnd.AddTool(&m_talk, _T("Test"));*/

	m_OALink1.SetURL(_T("http://www.baidu.com"));
	m_OALink1.SetUnderline(TRUE);
	m_OALink1.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	m_OALink2.SetURL(_T("http://www.163.com"));
	m_OALink2.SetUnderline(TRUE);
	m_OALink2.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CYgNoticeDlg::OnReceiveNotice(LPCTSTR strReceiver,LPCTSTR strNotice,LPCTSTR strLevel)
{
	m_lNoticeNotReadCount++;
	OnViewTips(_T("收到一条公告"));
	CTime ReceiveTime = CTime::GetCurrentTime();	
	CString csReceiveTime=ReceiveTime.Format(_T("%Y-%m-%d %H:%M:%S"));	
	m_list.InsertItem(0,strReceiver);
	m_list.SetItemText(0,1,csReceiveTime);
	m_list.SetItemText(0,2,strLevel);
	m_list.SetItemText(0,3,strNotice);
	m_list.SetItemText(0,4,_T("未读"));
	m_statusLog.StatusOut(_T("公告|%s|%s|%s|%s"),csReceiveTime,strReceiver,strNotice,strLevel);
	
}

void CYgNoticeDlg::OnSetReceiver(LPCTSTR strReceiver)
{
	m_csReceiver=strReceiver;
	GetDlgItem(IDC_EDIT3)->SetWindowText(strReceiver);
}

void CYgNoticeDlg::OnReceiveTalk(LPCTSTR strTalk)
{
	CTime ReceiveTime = CTime::GetCurrentTime();	
	CString csReceiveTime=ReceiveTime.Format(_T("%Y-%m-%d %H:%M:%S"));	
	CString strSender=_T("小W");
	if (m_pDlg != NULL)
	{
		m_pDlg->OnReceiveTalk(strTalk,csReceiveTime);
	}
	m_statusLog.StatusOut(_T("聊天|%s|%s|%s"),csReceiveTime,strSender,strTalk);
}

void CYgNoticeDlg::SendTalk(LPCTSTR strTalk,LPCTSTR csTime)
{
	if (m_ptrRoot) 
	{
		IRTXCModulePtr pPluginModule = NULL;
		pPluginModule = m_ptrRoot->GetModule(RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE);
		if (pPluginModule) 
		{
			IDispatch* pModuleSite;
			
			pPluginModule->get_ModuleSite(&pModuleSite);
			IRTXCModuleSitePtr pMyModuleSite = pModuleSite;
			
			_bstr_t Username = m_ptrRoot->Account;
			CString Content=strTalk;
			CString csType=_T("TALK");
			CString csSendTime=csTime;
			CString csReceiver=_T("小W");
		
			IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();  //通过m_ptrRoot创建RTXCData对象
			ptrData->SetString(_bstr_t("Sender"), Username);  //向prtData添加一个String类型的参数,Key为Sender,内容为Username
			ptrData->SetString(_bstr_t("Receiver"), _bstr_t(csReceiver));
			ptrData->SetString(_bstr_t("SendTime"), _bstr_t(csSendTime));
			ptrData->SetString(_bstr_t("Type"), _bstr_t(csType));
			ptrData->SetString(_bstr_t("Content"), _bstr_t(Content));  // 向prtData添加一个String类型的参数.Key为Contencent
			
			// 接收者为应用的GUID,示例应用的GUID为{16F8F6DB-EB21-4520-8371-421DD76A9148}
			pMyModuleSite->SendData(_bstr_t("{16F8F6DB-EB21-4520-8371-421DD76A9149}"), ptrData, 
				RTXC_SEND_DATA_FLAG_DEFAULT);
			m_statusLog.StatusOut(_T("聊天发送|%s|%s|%s"),csSendTime,m_csLocalAccount,strTalk);
		}
	}
}

void CYgNoticeDlg::OnButton1() 
{
	if(!m_bAdmin)
	{
		::MessageBox(NULL, _T("你没有权限进行该操作！"),_T("公告设置"), MB_OK);
		return;
	}
	if(m_csReceiver.IsEmpty())
	{
		::MessageBox(NULL, _T("接受者不能为空！"),_T("公告设置"), MB_OK);
		return;
	}
	
	CString Content=_T("");
	GetDlgItem(IDC_EDIT2)->GetWindowText (Content);	//从界面获取内容
	if(Content.IsEmpty())
	{
		::MessageBox(NULL, _T("公告内容不能为空！"),_T("公告设置"), MB_OK);
		return;
	}
	if (m_ptrRoot) 
	{
		IRTXCModulePtr pPluginModule = NULL;
		pPluginModule = m_ptrRoot->GetModule(RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE);
		if (pPluginModule) 
		{
			IDispatch* pModuleSite;
			
			pPluginModule->get_ModuleSite(&pModuleSite);
			IRTXCModuleSitePtr pMyModuleSite = pModuleSite;

			CTime ReceiveTime = CTime::GetCurrentTime();	
			CString csSendTime=ReceiveTime.Format(_T("%Y-%m-%d %H:%M:%S"));	
			
			_bstr_t Username = m_ptrRoot->Account;
		
			CString csType=_T("NOTICE");			
		
			IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();  //通过m_ptrRoot创建RTXCData对象
			ptrData->SetString(_bstr_t("Sender"), Username);  //向prtData添加一个String类型的参数,Key为Sender,内容为Username
			ptrData->SetString(_bstr_t("Receiver"), _bstr_t(m_csReceiver));
			ptrData->SetString(_bstr_t("SendTime"), _bstr_t(csSendTime));
			ptrData->SetString(_bstr_t("Type"), _bstr_t(csType));
			ptrData->SetString(_bstr_t("Content"), _bstr_t(Content));  // 向prtData添加一个String类型的参数.Key为Contencent
			
			// 接收者为应用的GUID,示例应用的GUID为{16F8F6DB-EB21-4520-8371-421DD76A9148}
			pMyModuleSite->SendData(_bstr_t("{16F8F6DB-EB21-4520-8371-421DD76A9149}"), ptrData, 
				RTXC_SEND_DATA_FLAG_DEFAULT);
			m_statusLog.StatusOut(_T("公告发送|%s|%s|%s|%s"),csSendTime,m_csReceiver,Content,_T(""));
			GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT2)->SetFocus();
		}
	}

	
}

// 获取对话框
CTalkDlg* CYgNoticeDlg::GetTalkDialog()
{
	CTalkDlg *pDlg;

	// 如果对话框没有被创建（index == NULL），就新建一个对话框
	if (m_pDlg == NULL)
	{
		pDlg = new CTalkDlg(this);

		pDlg->Create(IDD_DLGTALK, this);

		m_pDlg=pDlg;

		return pDlg;
	}
	else
	{
		return m_pDlg;
	}
}

void CYgNoticeDlg::OnBtnTalk() 
{
	// TODO: Add your control notification handler code here
	// 获取对话框
	CTalkDlg *pDlg = GetTalkDialog();
	pDlg->SetLocalAccount(m_csLocalAccount);
	pDlg->ShowWindow(TRUE);
}

void CYgNoticeDlg::SendNoticeReadEven()
{
	//////////////////////////////////////////////////////////////////////////
	//利用rtxEventCenter激发事件演示
	//创建一个rtxcdata 并填充内容
	IRTXCDataPtr ptrData = m_ptrRoot->CreateRTXCData();	
	ptrData->SetString(_T("NotifyContent"), _T("Yg test"));
	ptrData->SetLong(_T("LONG_PARAM1"), m_lNoticeNotReadCount);
	_trace(_T("YgTabFlash:CYgTabFlashCtrl::OnLButtonDown"));
	//利用事件中心激发事件
	VARIANT varRet;
	IRTXCEventCenterPtr ptrEventCtr ;
	m_ptrRoot->get_RTXCEventCenter(&ptrEventCtr);
	varRet = ptrEventCtr->FireModuleEvent(YGTEST_EVENT, m_ptrRoot->Module[RTX_MODULE_IDENTIFIER_PLUGINYGNOTICE],ptrData);	
    ////////////////////////////////////////////////////////////////////////// 
}

void CYgNoticeDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    int i=m_list.GetSelectionMark();    
	m_Notice=m_list.GetItemText(i,3);
	CString strtmp=m_list.GetItemText(i,4);
	if(strtmp == _T("未读"))
	{
		m_lNoticeNotReadCount--;
		m_list.SetItemText(i,4,_T("已读"));
		SendNoticeReadEven();
	}
	UpdateData(false);
	*pResult = 0;
	
}

void CYgNoticeDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	_trace(_T("YgTabFlash:CYgNoticeDlg::OnButton2！"));
	//HRESULT hr;	
	try
	{
		/*if(m_pMsgWindow != NULL)
		{
			if(m_pMsgWindow->DestroyWindow())
			{
				delete m_pMsgWindow;
				m_pMsgWindow=NULL;
			}

		}*/
	}
	catch (...) 
	{
		/// 错误处理~~
		_trace(_T("YgTabFlash:CYgNoticeDlg::OnButton2:happn error！"));
	}

	
}

void CYgNoticeDlg::OnClose() 
{
	_trace(_T("YgTabFlash:CYgNoticeDlg::OnClose!"));
	
	CDialog::OnClose();
}

void CYgNoticeDlg::OnDestroy() 
{	
	CDialog::OnDestroy();
	_trace(_T("YgTabFlash:CYgNoticeDlg::OnDestroy!"));
}

void CYgNoticeDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}
