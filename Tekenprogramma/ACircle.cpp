#include "stdafx.h"
#include "ACircle.h"


ACircle::ACircle(void)
{
	shapeType = 0;
}

void ACircle::undraw(CDC *pDC) {
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->Ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void ACircle::draw(CDC *pDC) {
	AShape::draw(pDC);

	if(previousPoint.x != -1) pDC->Ellipse(startPoint.x, startPoint.y, previousPoint.x, previousPoint.y);

	pDC->Ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

ACircle::~ACircle(void)
{
}

bool ACircle::isOn(CPoint point) const {
	CRect ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	if(ellipse.PtInRect(point)) return true;

	return false;
}
