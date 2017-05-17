// YgMsgMgrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YgMsgMgrOcx.h"
#include "YgMsgMgrDlg.h"
#include "YgMsgMgrOcxCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrDlg dialog


CYgMsgMgrDlg::CYgMsgMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYgMsgMgrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYgMsgMgrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pYgMsgCtrl = NULL;
}


void CYgMsgMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYgMsgMgrDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYgMsgMgrDlg, CDialog)
	//{{AFX_MSG_MAP(CYgMsgMgrDlg)
	ON_WM_CREATE()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrDlg message handlers

void CYgMsgMgrDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CYgMsgMgrDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int CYgMsgMgrDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pYgMsgCtrl = (CYgMsgMgrOcxCtrl*)GetParent();
	return 0;
}

void CYgMsgMgrDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(0);//导出亮

	//::MessageBox(NULL, m_pYgMsgCtrl->m_strAccountPath,_T("ActiveX响应"), MB_OK);
}

void CYgMsgMgrDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(2); //邮寄亮
}

void CYgMsgMgrDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(3); //邮寄灰
}

void CYgMsgMgrDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(4); //删除亮
}

void CYgMsgMgrDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(5); //删除灰
}

void CYgMsgMgrDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(7); //会话灰
}

void CYgMsgMgrDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(8); //刷新亮
}

void CYgMsgMgrDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(9);//刷新灰
}

void CYgMsgMgrDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(1); //导出灰
}

void CYgMsgMgrDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	m_pYgMsgCtrl->FireDemoEvent(6); //会话亮
}

BOOL CYgMsgMgrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rt;
	double m_width=rt.Width()/3;
	m_list.GetClientRect(rt);
	m_list.InsertColumn(0,_T("接收人"),LVCFMT_LEFT,rt.Width()/3);
	m_list.InsertColumn(1,_T("时间"),LVCFMT_LEFT,rt.Width()/3);
	m_list.InsertColumn(2,_T("信息条数"),LVCFMT_LEFT,rt.Width()/3);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
