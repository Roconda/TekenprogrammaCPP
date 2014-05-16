#include "stdafx.h"
#include<string>
#include "AShape.h"

AShape::AShape() {
	startPoint = NULL;
	previousPoint = NULL;
	endPoint = *(new CPoint(-1, -1));
	isSet = false;
}

void AShape::undraw(CDC *pDC) {
}

void AShape::draw(CDC *pDC){
	pDC->SetROP2(R2_NOTXORPEN);
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

std::string AShape::getSerialized() {
	using namespace std;

	return 
		"{"
		+to_string(shapeType)+","+
		to_string(startPoint.x)+","+
		to_string(startPoint.y)+","+
		to_string(endPoint.x)+","+
		to_string(endPoint.y)+
		"}";
}