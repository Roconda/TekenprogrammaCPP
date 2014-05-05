#include "stdafx.h"
#include "AWriter.h"

AWriter::AWriter(void)
{
}


AWriter::~AWriter(void)
{
}

AWriter& AWriter::getInstance() {
	static AWriter _instance;

	return _instance;
};
