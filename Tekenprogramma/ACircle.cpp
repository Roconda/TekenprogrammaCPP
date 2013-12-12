#include "stdafx.h"
#include "ACircle.h"


ACircle::ACircle(void)
{
}

void ACircle::undraw(CDC *pDC) {
	pDC->SetROP2(R2_XORPEN);
	pDC->Ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void ACircle::draw(CDC *pDC) {


	if(previousPoint.x != -1) {
		//pen.CreatePen(R2_NOTXORPEN, 1, RGB(255,0,0));
		pDC->SetROP2(R2_XORPEN);
		//pDC->SelectObject(&pen);

		pDC->Ellipse(startPoint.x, startPoint.y, previousPoint.x, previousPoint.y);
	}

	pDC->Ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	//pDC->Ellipse(20,50,60,90);
}

ACircle::~ACircle(void)
{
//	CDC* pdc = GetDC();
}
