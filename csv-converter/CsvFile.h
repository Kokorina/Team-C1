#pragma once

#include <QString>
#include <qstringlist.h>
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
	void writeTfIdfFile(QString path);
	void writeLogLikelihoodFile(QString path);

	void filterEmptyContexts();
	void randomize();
	void makeClassBoWs();
	void makeTotalBoW();
	void makeSets(int n);
	void makeBaseBoW();
	void addFeatures();

private:
    QString path;
    vector<CsvRow> rows;
    QString header;
	map<int, ToolParentClass> parents;
	multimap<int, map<QString, int>> classBoWs;
	map<QString, int> totalBoW;
	map<QString, int> baseBoW;
};

