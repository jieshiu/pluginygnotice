// YgNoticeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YgTabFlash.h"
#include "YgNoticeDlg.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CYgNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYgNoticeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYgNoticeDlg, CDialog)
	//{{AFX_MSG_MAP(CYgNoticeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYgNoticeDlg message handlers
