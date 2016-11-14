#include "CsvHandler.h"
#include <qdebug.h>
#include <qfile.h>
#include <QStringList>
#include <QTextStream>


CsvHandler::CsvHandler() {
}


CsvHandler::~CsvHandler() {
}

CsvFile CsvHandler::readCsv(QString path) {
	//open file
	QFile file(path);
	CsvFile csv;

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
			if (first == true) {
				continue;
			}
			if (index.at(i) == "") {
				continue;
			}
			else if (index.at(i) == "Autor, Herausgeber oder Institution") {
				line.setAuthor(fields.at(i));
			}
			else if (index.at(i) == "Jahr ermittelt") {
				line.setYear(fields.at(i));
			}
			else if (index.at(i) == "Titel") {
				line.setTitleCitavi(fields.at(i));
			}
			else if (index.at(i) == "Untertitel") {
				line.setSubtitle(fields.at(i));
			}
			else if (index.at(i) == "Ort") {
				line.setCity(fields.at(i));
			}
			else if (index.at(i) == "Zeitschrift/Zeitung") {
				line.setJournalName(fields.at(i));
			}
			else if (index.at(i) == "Band") {
				line.setJournalVolume(fields.at(i));
			}
			else if (index.at(i) == "Nummer") {
				line.setJournalNumber(fields.at(i));
			}
			else if (index.at(i) == "Datum") {
				line.setJournalYear(fields.at(i));
			}
			else if (index.at(i) == "Seiten von–bis") {
				line.setPages(fields.at(i));
			} 
			else if (index.at(i) == "Laufnummer") {
				line.setCitaviId(fields.at(i));
			}
			else if (index.at(i) == "Schlagwörter") {
				line.setTags(fields.at(i));
			}
		}

		//push line into csv vector
		if (first == false) {
			csv.addRow(line);
		}
		first = false;
	}
	return csv;
}
