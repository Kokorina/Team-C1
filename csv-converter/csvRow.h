#pragma once

#include <qstring.h>
#include "tool.h"

class CsvRow
{
public:
	CsvRow();
	~CsvRow();

	Tool getTool();
	void setTool(Tool value);

private:
	Tool tool;
};

