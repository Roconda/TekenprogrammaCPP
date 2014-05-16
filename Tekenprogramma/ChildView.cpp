
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
#include <stdlib.h>

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
	ON_COMMAND(ID_FILE_SAVETOFILE, &CChildView::OnFileSavetofile)
	ON_COMMAND(ID_FILE_OPENFILE, &CChildView::OnFileOpenfile)
	ON_COMMAND(IDR_TOOLBAR1, &CChildView::OnEditUndo)
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

	redrawShapes(false);
}

void CChildView::redrawShapes(boolean draw) {
	CDC* pDC = GetDC();

	for(unsigned int i=0; i<shapes.size(); i++) if(draw) { shapes[i]->draw(pDC); }else{ shapes[i]->undraw(pDC); };

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
	   SetCapture();
	   CRect windowRect;
	   GetWindowRect(&windowRect);
	   ScreenToClient(&windowRect);
	   CDC  *pDC = GetDC();

	   if(getLastShape() != NULL && !windowRect.PtInRect(point)) {
		   getLastShape()->isSet = true;
		   ReleaseCapture();
	   }

	   if(endPoint.x != -1 && getLastShape() != NULL && !getLastShape()->isSet) {
					getLastShape()->setEndPoint(point);
					getLastShape()->draw(pDC);
		}
      
		  // Kies zwarte pen van de 'stock' (bestaande pen)
		  pDC->SelectStockObject(SS_BLACKRECT);
      
		  // Je kunt ook zelf een pen maken:
		  CPen pen;
		  pen.CreatePen(PS_DOT, 1, RGB(255,0,0));
		  pDC->SelectObject(&pen);
	   //}

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
		shapes.shrink_to_fit();
	}

	ReleaseDC(pDC);
}


void CChildView::OnFileSavetofile()
{
	TCHAR szFilters[]= _T("Tekeningen (*.painting)|*.painting||");
	CFileDialog cfd = CFileDialog(false, _T("painting"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, NULL, 0, true);
	CFile file;

	if(cfd.DoModal() == IDOK){
		string txt = "\xef\xbb\xbf"; // BOM

		for(unsigned int i=0; i<shapes.size(); i++) txt.append(shapes[i]->getSerialized());

		if(file.Open(cfd.GetPathName(), CFile::modeCreate | CFile::modeReadWrite) ) {
			file.Write(txt.c_str(), txt.size());
			file.Flush();
		}
	}
}


void CChildView::OnFileOpenfile()
{
	TCHAR szFilters[]= _T("Tekeningen (*.painting)|*.painting||");

	CFileDialog cfd = CFileDialog(true, _T("painting"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, NULL, 0, true);
	CFile file;
	string content = "";

	if(cfd.DoModal() == IDOK) {
		// Remove old shapes
		for(unsigned int i=0; i<shapes.size(); i++) delete shapes[i];
		shapes.clear();

		// Clear screen
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_WHITE);
		pDC->Rectangle(0,0,99999,99999);
		ReleaseDC(pDC);

		if(file.Open(cfd.GetPathName(), CFile::modeRead | CFile::modeNoTruncate)) {
			char* buffer = new char[file.GetLength()]();
			file.Seek(3, CFile::begin); // ignore BOM
			file.Read(buffer, file.GetLength());
			content = buffer;
			delete buffer;

			CDC* pDC = GetDC();

			vector<AShape*> tmpShapes;
			short state = 0;
			short substate = 0;
			CPoint* tmpCPoint = nullptr;
			string tmpPoint = "";
			for(unsigned int i=0; i<content.size(); i++) {
				char c = content[i];

				if(c == '{') { state = 1; substate = 0; continue; } // entering shape creation
				if(c == '}') {
					tmpCPoint->y = atoi(tmpPoint.c_str());
					tmpPoint = "";
					tmpShapes.at(0)->setEndPoint(*tmpCPoint);
					tmpShapes.at(0)->draw(pDC);
					tmpCPoint = nullptr; //reset

					state = 0;
					shapes.push_back(tmpShapes.at(0));
					tmpShapes.clear();
				};

				if(state == 1) {
					if(substate == 0) {
						switch(c){
							case '0':
								tmpShapes.push_back(new ACircle());
								break;
							case '1':
								tmpShapes.push_back(new ARectangle());
								break;
							case '2':
								tmpShapes.push_back(new ALine());
								break;
							default:
								tmpShapes.push_back(new ACircle());
						}
						i++;
						substate++;
						continue;
					}else if(substate == 1){
						// CPoint X
						if(c == ',') {
							tmpCPoint = new CPoint(0,0);
							tmpCPoint->x = atoi(tmpPoint.c_str());
							tmpPoint = "";
							substate++;
							continue;
						}else tmpPoint += c;
					}else if(substate == 2){
						// CPoint Y
						if(c == ',') {
							tmpCPoint->y = atoi(tmpPoint.c_str());
							tmpPoint = "";
							tmpShapes.at(0)->setStartPoint(*tmpCPoint);
							tmpCPoint = nullptr; //reset
							substate++;
							continue;
						}else tmpPoint += c;
					} else if(substate == 3){
						// CPoint X
						if(c == ',') {
							tmpCPoint = new CPoint(0,0);
							tmpCPoint->x = atoi(tmpPoint.c_str());
							tmpPoint = "";
							substate++;
							continue;
						}else tmpPoint += c;
					}else if(substate == 4){
						// CPoint Y
						tmpPoint += c;
					}
				}
			}
			ReleaseDC(pDC);
		}
	}
}
