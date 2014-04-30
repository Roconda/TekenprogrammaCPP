
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Tekenprogramma.h"
#include "ChildView.h"
#include "AShape.h"
#include "ACircle.h"
#include "ALine.h"
#include "ARectangle.h"
#include "Settings.h"
#include <vector>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPoint startPoint;
CPoint endPoint;

// CChildView
CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC* pDC = GetDC();

	for(int i=0; i<shapes.size(); i++) shapes[i]->undraw(pDC);

	ReleaseDC(pDC);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	startPoint = point;
	
	AShape* as;

	if(Settings::shapeSelected == 0) as = new ACircle();
	else if(Settings::shapeSelected == 1) as = new ARectangle();
	else if(Settings::shapeSelected == 2) as = new ALine();
	else as = new ACircle();

	as->setStartPoint(point);
	shapes.push_back(as);
}

// Geeft de laatste shape pointer terug.
AShape* CChildView::getLastShape() {
	if(shapes.size() > 0)return shapes[shapes.size()-1];
	else return NULL;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if(startPoint.x != -1)
   {
      CDC  *pDC = GetDC();
	  //notxor pen maakt zwart wit
		// pas waarde aan
		if(endPoint.x != -1 && getLastShape() != NULL) {
			getLastShape()->setEndPoint(point);
			getLastShape()->draw(GetDC());
		}
      
      // Kies zwarte pen van de 'stock' (bestaande pen)
      pDC->SelectStockObject(SS_BLACKRECT);
      
      // Je kunt ook zelf een pen maken:
      CPen pen;
      pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
      pDC->SelectObject(&pen);

      // Teken met NOT XOR
      //pDC->SetROP2(R2_NOTXORPEN);
    
      // Trek vorige rechthoek over. 2 x XOR geeft oorspronkelijke waarde
      //if(endPoint.x != -1)
      //   pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

      // Teken huidige rechthoek met XOR: wit wordt zwart, zwart wordt wit
      //pDC->Rectangle(startPoint.x, startPoint.y, point.x, point.y);

      ReleaseDC(pDC);
      endPoint = point;
   }

}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDC* pDC = GetDC();

   ReleaseDC(pDC);

   // Reset start and endpoints for upcoming shapes.
   startPoint.x = -1;
   endPoint.x = -1;
}


void CChildView::OnEditUndo()
{
	CDC* pDC = GetDC();

	if(getLastShape()!= NULL && getLastShape() != nullptr){
		getLastShape()->undraw(pDC);

		delete getLastShape();

		shapes.pop_back();
	}

	ReleaseDC(pDC);
}
