#include "stdafx.h"
#include "ARectangle.h"


ARectangle::ARectangle(void)
{
	shapeType = 1;
}


ARectangle::~ARectangle(void)
{
}


void ARectangle::draw(CDC* pDC) {
	AShape::draw(pDC);

	if(previousPoint.x != -1) pDC->Rectangle(startPoint.x, startPoint.y, previousPoint.x, previousPoint.y);

	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void ARectangle::undraw(CDC* pDC) {
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

bool ARectangle::isOn(CPoint point) const {
	CRect square(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	if(square.PtInRect(point)) return true;

	return false;
}