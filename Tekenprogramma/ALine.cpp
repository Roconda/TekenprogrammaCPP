#include "stdafx.h"
#include "ALine.h"


ALine::ALine(void)
{
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

	if(previousPoint.x != -1) {
		pDC->MoveTo(previousPoint);
		pDC->LineTo(startPoint);
	}

	pDC->MoveTo(startPoint);
	pDC->LineTo(endPoint);
}
