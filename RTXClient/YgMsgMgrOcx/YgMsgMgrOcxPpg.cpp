// YgMsgMgrOcxPpg.cpp : Implementation of the CYgMsgMgrOcxPropPage property page class.

#include "stdafx.h"
#include "YgMsgMgrOcx.h"
#include "YgMsgMgrOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CYgMsgMgrOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CYgMsgMgrOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CYgMsgMgrOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CYgMsgMgrOcxPropPage, "YGMSGMGROCX.YgMsgMgrOcxPropPage.1",
	0xcca34df5, 0x50c4, 0x4cb6, 0x9b, 0xfd, 0xa3, 0x1d, 0xc2, 0x31, 0x58, 0x2e)


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxPropPage::CYgMsgMgrOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CYgMsgMgrOcxPropPage

BOOL CYgMsgMgrOcxPropPage::CYgMsgMgrOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_YGMSGMGROCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxPropPage::CYgMsgMgrOcxPropPage - Constructor

CYgMsgMgrOcxPropPage::CYgMsgMgrOcxPropPage() :
	COlePropertyPage(IDD, IDS_YGMSGMGROCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CYgMsgMgrOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxPropPage::DoDataExchange - Moves data between page and properties

void CYgMsgMgrOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CYgMsgMgrOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxPropPage message handlers
