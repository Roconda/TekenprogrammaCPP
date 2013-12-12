
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Tekenprogramma.h"
#include "ChildView.h"
#include "AShape.h"
#include "ACircle.h"
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
	
	// TODO: Add your message handler code here
	//MessageBox(L"Rectangle", L"Draw", 0);
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	startPoint = point;
	
	ACircle *as = new ACircle();
	as->setStartPoint(point);
	shapes.push_back(as);
	shapes.shrink_to_fit();

	// WTF is dit
	//CWnd::OnLButtonDown(nFlags, point);
}

// Geeft de laatste shape pointer terug.
AShape* CChildView::getLastShape() {
	for(int i= shapes.size()-1; i>0; i--){
		if(shapes[i] != nullptr) return shapes[i];
	}

	// TODO: een nette oplossing vinden
	AShape* uselessShape = new ACircle;
	return uselessShape;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	   if(startPoint.x != -1)
   {
      CDC  *pDC = GetDC();
	  //notxor pen maakt zwart wit
		// pas waarde aan
		if(endPoint.x != -1) {
			getLastShape()->setEndPoint(point);
			getLastShape()->draw(GetDC());
		}
      
      // Kies zwarte pen van de 'stock' (bestaande pen)
      pDC->SelectStockObject(SS_BLACKRECT);
      
      // Je kunt ook zelf een pen maken:
      //  CPen pen;
      //  pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
      //  pDC->SelectObject(&pen);

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

	// WTF is dit
	//CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//endPoint = point;

	CDC* pDC = GetDC();


	//bier->setEndPoint(&endPoint);

	//getLastShape()->draw(GetDC());


	//bier->getStartPoint();
	//bier->getEndPoint();


	point;
   ReleaseDC(pDC);
   startPoint.x = -1;
   endPoint.x = -1;

	// WTF IS DIT
	//CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnEditUndo()
{
	CDC* pDC = GetDC();

	getLastShape()->undraw(pDC);

	delete getLastShape();

	shapes.pop_back();
	shapes.shrink_to_fit();

	ReleaseDC(pDC);
}
