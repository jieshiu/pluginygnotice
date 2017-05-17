#if !defined(AFX_YGMSGMGROCXPPG_H__DBD050C2_B150_491D_8FD6_F4E7D1D48E69__INCLUDED_)
#define AFX_YGMSGMGROCXPPG_H__DBD050C2_B150_491D_8FD6_F4E7D1D48E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// YgMsgMgrOcxPpg.h : Declaration of the CYgMsgMgrOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CYgMsgMgrOcxPropPage : See YgMsgMgrOcxPpg.cpp.cpp for implementation.

class CYgMsgMgrOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CYgMsgMgrOcxPropPage)
	DECLARE_OLECREATE_EX(CYgMsgMgrOcxPropPage)

// Constructor
public:
	CYgMsgMgrOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CYgMsgMgrOcxPropPage)
	enum { IDD = IDD_PROPPAGE_YGMSGMGROCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CYgMsgMgrOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGMSGMGROCXPPG_H__DBD050C2_B150_491D_8FD6_F4E7D1D48E69__INCLUDED)
