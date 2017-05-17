#if !defined(AFX_YGTABFLASHPPG_H__DA37EB1C_E4A7_4B6D_B46B_49277D898C4E__INCLUDED_)
#define AFX_YGTABFLASHPPG_H__DA37EB1C_E4A7_4B6D_B46B_49277D898C4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// YgTabFlashPpg.h : Declaration of the CYgTabFlashPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CYgTabFlashPropPage : See YgTabFlashPpg.cpp.cpp for implementation.

class CYgTabFlashPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CYgTabFlashPropPage)
	DECLARE_OLECREATE_EX(CYgTabFlashPropPage)

// Constructor
public:
	CYgTabFlashPropPage();

// Dialog Data
	//{{AFX_DATA(CYgTabFlashPropPage)
	enum { IDD = IDD_PROPPAGE_YGTABFLASH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CYgTabFlashPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YGTABFLASHPPG_H__DA37EB1C_E4A7_4B6D_B46B_49277D898C4E__INCLUDED)
