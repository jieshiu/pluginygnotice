// YgTabFlashPpg.cpp : Implementation of the CYgTabFlashPropPage property page class.

#include "stdafx.h"
#include "YgTabFlash.h"
#include "YgTabFlashPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CYgTabFlashPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CYgTabFlashPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CYgTabFlashPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CYgTabFlashPropPage, "YGTABFLASH.YgTabFlashPropPage.1",
	0x18b92dea, 0x7ef6, 0x4a52, 0xa4, 0xdf, 0x3e, 0x6e, 0x5e, 0x43, 0x96, 0x8)


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashPropPage::CYgTabFlashPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CYgTabFlashPropPage

BOOL CYgTabFlashPropPage::CYgTabFlashPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_YGTABFLASH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashPropPage::CYgTabFlashPropPage - Constructor

CYgTabFlashPropPage::CYgTabFlashPropPage() :
	COlePropertyPage(IDD, IDS_YGTABFLASH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CYgTabFlashPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashPropPage::DoDataExchange - Moves data between page and properties

void CYgTabFlashPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CYgTabFlashPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CYgTabFlashPropPage message handlers
