#pragma once

#include <QString>
#include "tool.h"

class CsvRow
{
public:
	CsvRow();
	~CsvRow();

	Tool getTool();
	void setTool(Tool value);

    QString getSubClass() const;
    void setSubClass(const QString &value);

    int getParent() const;
    void setParent(int value);

private:
    Tool tool;
    int parent;
    QString subClass;
};

