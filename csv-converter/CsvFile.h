#pragma once

#include <QString>
#include <vector>
#include <map>
#include "csvRow.h"
#include "toolparentclass.h"

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
	void writeLabelFile(QString pathLabels);
	void writeVectorFile(QString path);

	void randomize();
	void makeClassBoWs();
	void makeTotalBoW();
	void makeSets(int n);

private:
    QString path;
    vector<CsvRow> rows;
    QString header;
	map<int, ToolParentClass> parents;
	multimap<int, map<QString, int>> classBoWs;
	map<QString, int> totalBoW;
};

