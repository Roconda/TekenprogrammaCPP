
// Tekenprogramma.h : main header file for the Tekenprogramma application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTekenprogrammaApp:
// See Tekenprogramma.cpp for the implementation of this class
//

class CTekenprogrammaApp : public CWinApp
{
public:
	CTekenprogrammaApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnShapesRectangle();
	afx_msg void OnShapesCircle();
};

extern CTekenprogrammaApp theApp;
