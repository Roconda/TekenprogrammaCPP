#include "stdafx.h"
#include "AShape.h"

AShape::AShape() {
	startPoint = NULL;
	endPoint = NULL;
	cdc = NULL;
}

void AShape::draw(){
}

void AShape::setStartPoint(CPoint *point)
{
		startPoint = point;
}

/*
void AShape::setStartPoint(CPoint point) {
	startPoint = point;
}
/*
void AShape::setEndPoint(CPoint *point) {
	//endPoint = *point;
}

void AShape::setCDC(CDC *cdcP) {
	//cdc = *cdcP;
}
*/

AShape::~AShape() {
	delete startPoint;
	delete endPoint;
	delete cdc;
}