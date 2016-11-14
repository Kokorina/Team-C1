#include "CsvFile.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <qdebug.h>
#include "tool.h"
#include "toolparentclass.h"
#include "toolsubclass.h"

CsvFile::CsvFile() {
}

CsvFile::~CsvFile() {
}

CsvFile::CsvFile(QString loc) {
	path = loc;
}

void CsvFile::addRow(CsvRow row) {
	rows.push_back(row);
}

QString CsvFile::getPath() const
{
	return path;
}

void CsvFile::setPath(const QString &value)
{
	path = value;
}
QString CsvFile::getHeader() const
{
    return header;
}

void CsvFile::setHeader(const QString &value)
{
    header = value;
}

CsvFile CsvFile::readCsv(QString path) {
	//open file
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << file.errorString();
	}

	QTextStream text(&file);
	QStringList rows;

	while (!text.atEnd())
		rows << text.readLine();

	file.close();

	//determine order of elements
	map<int, QString> index;
	QStringList::const_iterator row;
	bool first = true;

	for (row = rows.constBegin(); row != rows.constEnd(); ++row) {
		//future improvement: allow typing a different character in the GUI
		QString separator = "\t";
		QStringList fields = row->split(separator);
		CsvRow line;

		if (first == true) {
			//create the index
			for (int i = 0; i < fields.size(); ++i) {
				index[i] = fields.at(i);
			}
		}

		//read the field data and add it to the csv object.
		//iterate over fields
		for (int i = 0; i < fields.size(); ++i) {
            if (first == true && index.at(i) == "") {
                //tool-name
			}
            else if (index.at(i) == "Nummer") {
                //(1A) einlesen und aufteilen
			}
		}

		//push line into csv vector
		if (first == false) {
			this->addRow(line);
		}
		first = false;
	}
	return *this;
}
