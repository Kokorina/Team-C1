#include "csvRow.h"


CsvRow::CsvRow()
{
}


CsvRow::~CsvRow()
{
}

Tool CsvRow::getTool() {
	return tool;
}

void CsvRow::setTool(Tool value) {
	tool = value;
}

QString CsvRow::getSubClass() const
{
    return subClass;
}

void CsvRow::setSubClass(const QString &value)
{
    subClass = value;
}
int CsvRow::getParent() const
{
    return parent;
}

void CsvRow::setParent(int value)
{
    parent = value;
}


