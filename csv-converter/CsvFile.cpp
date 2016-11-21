#include "CsvFile.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <qdebug.h>
#include "tool.h"
#include "toolparentclass.h"
#include "toolsubclass.h"
#include "mainwindow.h"

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
            Tool tool;
            if (i == 0 && index.at(i) == "") {
                //tool-name
                tool.setName(fields.at(i));
			}
            else if (index.at(i) == "Kategorie") {
                //(1A) einlesen und aufteilen
                int parent = fields.at(i).mid(1,1).toInt();
                QString subclassId = fields.at(i).mid(2,1);
                QString subclassName = fields.at(i).right(5);

                for ( int j=0; j<MainWindow::parents.size(); j++) {
                    if (parents.at(j).getId()==parent) {
                        ToolParentClass parentTool = parents.at(j);
                        bool exists=false;
                        for (int k=0; k<parentTool.getSubclasses().size(); k++) {
                            if (parentTool.getSubclasses().at(k).getId()==subclassId) {
                                exists=true;
                            }
                        }
                        if (!exists) {
                            ToolSubClass subclass(subclassId, subclassName);
                            parentTool.getSubclasses().push_back(subclass);
                            // ÜBERPRÜFEN
                        }
                        for (int k=0; k<parentTool.getSubclasses().size(); k++) {
                            if (parentTool.getSubclasses().at(k).getId()==subclassId) {
                                parentTool.getSubclasses().at(k).getTools();
                            }
                        }
                    }
                }
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
