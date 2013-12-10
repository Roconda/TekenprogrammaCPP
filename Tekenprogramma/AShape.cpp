#include "stdafx.h"
#include "AShape.h"

AShape::AShape() {
	startPoint = NULL;
	previousPoint = NULL;
	endPoint = *(new CPoint(-1, -1));
}

void AShape::undraw(CDC *pDC) {
}

void AShape::draw(CDC *pDC){
}

void AShape::setStartPoint(CPoint &point)
{
	startPoint = point;
}

void AShape::setEndPoint(CPoint &point) {
	// Remember its previous point so we can erase it on draw
	previousPoint = endPoint;
	endPoint = point;
}

CPoint* AShape::getStartPoint() {
	return &startPoint;
}

CPoint* AShape::getEndPoint() {
	return &endPoint;
}

AShape::~AShape() {

}