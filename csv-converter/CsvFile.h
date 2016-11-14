#pragma once

#include <QString>
#include <vector>
#include "csvRow.h"

using namespace std;

class CsvFile
{
public:
	CsvFile();
	CsvFile(QString loc);
	~CsvFile();

	QString getPath() const;
	void setPath(const QString &value);

    QString getHeader() const;
    void setHeader(const QString &value);

	void addRow(CsvRow row);

	CsvFile readCsv(QString path);
	void writeToFile(QString path);

private:
    QString path;
    vector<CsvRow> rows;
    QString header;
};

