#include "stdafx.h"
#include "ARectangle.h"


ARectangle::ARectangle(void)
{
}


ARectangle::~ARectangle(void)
{
}


void ARectangle::draw(CDC* pDC) {
	if(previousPoint.x != -1) {
		//pen.CreatePen(R2_NOTXORPEN, 1, RGB(255,0,0));
		pDC->SetROP2(R2_XORPEN);
		//pDC->SelectObject(&pen);

		pDC->Rectangle(startPoint.x, startPoint.y, previousPoint.x, previousPoint.y);
	}

	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void ARectangle::undraw(CDC* pDC) {
	pDC->SetROP2(R2_XORPEN);
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}