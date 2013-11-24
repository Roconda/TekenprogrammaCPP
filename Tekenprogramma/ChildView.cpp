
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
using std::cerr;
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
	as->setStartPoint(&point);
	shapes.push_back(as);


	//shapes->push_back(circle);
	//shapes->push_back(circle);
	//shapes->insert(circle);

	// WTF is dit
	//CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//point.x
	//_RPT0(0, "" + 3L);
	//std::string s = std::to_string(3);
	


	   if(startPoint.x != -1)
   {
      CDC  *pDC = GetDC();
      
      // Kies zwarte pen van de 'stock' (bestaande pen)
      pDC->SelectStockObject(SS_BLACKRECT);
      
      // Je kunt ook zelf een pen maken:
      //  CPen pen;
      //  pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
      //  pDC->SelectObject(&pen);

      // Teken met NOT XOR
      pDC->SetROP2(R2_NOTXORPEN);
    
      // Trek vorige rechthoek over. 2 x XOR geeft oorspronkelijke waarde
      if(endPoint.x != -1)
         pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

      // Teken huidige rechthoek met XOR: wit wordt zwart, zwart wordt wit
      pDC->Rectangle(startPoint.x, startPoint.y, point.x, point.y);
      ReleaseDC(pDC);
      endPoint = point;
   }

	// WTF is dit
	//CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	endPoint = point;

	CDC* pDC = GetDC();

	ACircle *bier = shapes[shapes.size()-1];
	bier->setEndPoint(&endPoint);


   ReleaseDC(pDC);
   startPoint.x = -1;
   endPoint.x = -1;

	// WTF IS DIT
	//CWnd::OnLButtonUp(nFlags, point);
}
