
// ChildView.h : interface of the CChildView class
//


#pragma once
#include <vector>
#include "AShape.h"
#include "ACircle.h"

// CChildView window
using namespace std;

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
private:
	vector<ACircle*> shapes;

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	AShape* getLastShape();
	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
};

