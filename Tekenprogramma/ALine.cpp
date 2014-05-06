#include "stdafx.h"
#include "ALine.h"


ALine::ALine(void)
{
	shapeType = 2;
}


ALine::~ALine(void)
{
}

void ALine::undraw(CDC *pDC) {
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->MoveTo(startPoint);
	pDC->LineTo(endPoint);
}

void ALine::draw(CDC *pDC){
	AShape::draw(pDC);

	if(previousPoint.x != -1) {
		pDC->MoveTo(startPoint);
		pDC->LineTo(previousPoint);
	}

	pDC->MoveTo(startPoint);
	pDC->LineTo(endPoint);
}
