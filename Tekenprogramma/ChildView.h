
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
	vector<AShape*> shapes;

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	AShape* getLastShape();
	void redrawShapes(boolean draw);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void ToggleDeleteMode();
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnFileSavetofile();
	afx_msg void OnFileOpenfile();
};

