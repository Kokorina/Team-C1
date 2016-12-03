#include "CsvFile.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <qdebug.h>
#include <algorithm>
#include <random>
#include <chrono>
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
	text.setCodec("UTF-8");
	QStringList rows;

	while (!text.atEnd())
		rows << text.readLine();

	file.close();

	//set the toolParentClass objects
	parents.insert(pair<int, ToolParentClass>(1, ToolParentClass(1, "Werkzeug")));
	parents.insert(pair<int, ToolParentClass>(2, ToolParentClass(2, "Maschinen")));
	parents.insert(pair<int, ToolParentClass>(3, ToolParentClass(3, "Messgeräte")));
	parents.insert(pair<int, ToolParentClass>(4, ToolParentClass(4, "Hardware")));
	parents.insert(pair<int, ToolParentClass>(5, ToolParentClass(5, "Software")));
	parents.insert(pair<int, ToolParentClass>(6, ToolParentClass(6, "Netzwerktechnik")));
	parents.insert(pair<int, ToolParentClass>(7, ToolParentClass(7, "Fahrzeuge")));
	parents.insert(pair<int, ToolParentClass>(8, ToolParentClass(8, "Medien")));

	//determine order of elements
	map<int, QString> index;
	QStringList::const_iterator row;
	bool first = true;
	QString separator = "\t";

	for (row = rows.constBegin(); row != rows.constEnd(); ++row) {
		//future improvement: allow typing a different character in the GUI
		
		QStringList fields = row->split(separator);
		CsvRow line;

		if (first == true) {
			//create the index
			for (int i = 0; i < fields.size(); ++i) {
				index[i] = fields.at(i);
			}
			first = false;
			continue;
		}

		//read the field data and add it to the csv object.
		//iterate over fields
		for (int i = 0; i < fields.size(); ++i) {
            if (i == 0 && index.at(i) == "") {
                //tool-name
				if (fields.at(i) == "----------------------------------------") {
					//Abbruchbedingung: ab hier kommen unklassifizierte Daten
					return *this;
				} else if (fields.at(i) == "") {
					break;
				}
				Tool tempTool;
				tempTool.setName(fields.at(i));
                line.setTool(tempTool);
			}
            else if (index.at(i) == "Kontext (SteA-Text)") {
                //ParentTool identifizieren
                map<int, ToolParentClass>::iterator findParent;

                findParent = parents.find(line.getParent());
                if (findParent != parents.end()) {
                    ToolParentClass parentTool = findParent->second;
                    map<QString, ToolSubClass> subclasses = parentTool.getSubclasses();
                    map<QString, ToolSubClass>::iterator search;

                    //Index der Subclass in ParentClass suchen
                    search = subclasses.find(line.getSubClass());
                    if (search != subclasses.end())  {
                        search = subclasses.find(line.getSubClass());
                    }

                    //das Tool in der SubClass referenzieren
                    if (line.getTool().getName() != "") {
                        vector<Tool> tools = subclasses.at(search->first).getTools();

                        for (unsigned j = 0; j<tools.size(); j++) {
                            Tool tempTool=tools.at(j);
                            if (tempTool.getName() == line.getTool().getName()) {
                                tempTool.setKontext(fields.at(i));
                                tools.at(j) = tempTool;
								line.setTool(tempTool);
                                break;
                            }
                        }
                        subclasses.at(search->first).setTools(tools);
                        findParent->second.setSubclasses(subclasses);
                    }
                }

                //Tool tempTool=line.getTool();
                //tempTool.setKontext(fields.at(i));
                //line.setTool(tempTool);
            }
            else if (index.at(i) == "Kategorie") {
				if (fields.at(i) == "") {
					break;
				}

                //"(1A) Subclassname" einlesen und aufteilen
                int parent = fields.at(i).mid(1,1).toInt();
                QString subclassId = fields.at(i).mid(2,1);
				QString subclassName = fields.at(i).right(fields.at(i).length() - 5);
				map<int, ToolParentClass>::iterator findParent;
                line.setParent(parent);
                line.setSubClass(subclassId);

				//ParentTool identifizieren
				findParent = parents.find(parent);
				if (findParent != parents.end()) {
					ToolParentClass parentTool = findParent->second;
					map<QString, ToolSubClass> subclasses = parentTool.getSubclasses();
					map<QString, ToolSubClass>::iterator search;
					bool exists = false;

					//Index der Subclass in ParentClass suchen
					search = subclasses.find(subclassId);
					if (search != subclasses.end())  {
						//success!
						exists = true;
					}
					//wenn SubClass noch nicht existiert: hinzufügen
					else {
                        ToolSubClass subclass(subclassId, subclassName);
						subclasses.insert(pair<QString, ToolSubClass>(subclassId, subclass));
						findParent->second.setSubclasses(subclasses);
					}
					if (exists == false) {
						search = subclasses.find(subclassId);
					}

					//das Tool in der SubClass referenzieren
					if (line.getTool().getName() != "") {
						vector<Tool> tools = subclasses.at(search->first).getTools();
						tools.push_back(line.getTool());
						subclasses.at(search->first).setTools(tools);
						findParent->second.setSubclasses(subclasses);
					}
				}
			}
		}

		//push line into csv vector
		if (first == false && line.getTool().getName() != "") {
			this->addRow(line);
		}
		first = false;
	}
	return *this;
}

void CsvFile::makeSets(int n) {
	// Daten mischen

	//um (z.B. zu Testzwecken) immer die gleiche Randomisierung zu bekommen: seed-Parameter aus re entfernen
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto re = default_random_engine(seed);
	shuffle(begin(this->rows), end(this->rows), re);
	
	// n Sets aus Trainings- und Testdaten erstellen 
	for (int i = 1; i < n; ++i) {
		vector<Tool> testData;
		vector<Tool> trainingData;

		int setStart = this->rows.size() / n * (i - 1);
		int setEnd = (this->rows.size() / n * i) - 1;

		for (int j = 0; j < this->rows.size(); ++j) {
			if (j >= setStart && j <= setEnd) {
				testData.push_back(this->rows.at(j).getTool());
			}
			else {
				trainingData.push_back(this->rows.at(j).getTool());
			}
		}

		//hier müssen die Vektoren entweder weiterverarbeitet oder in einer Datenstruktur abgelegt werden

		//diese Instruktion steht nur hier, damit man einen breakpoint setzen und die Vektoren ansehen kann
		int z = 0;
	}
}
