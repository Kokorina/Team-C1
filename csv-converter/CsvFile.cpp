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
				}
				else if (fields.at(i) == "") {
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

						for (unsigned j = 0; j < tools.size(); j++) {
							Tool tempTool = tools.at(j);
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
				int parent = fields.at(i).mid(1, 1).toInt();
				QString subclassId = fields.at(i).mid(2, 1);
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


void CsvFile::writeToFile(QString path) {
	//open file
	QString pathData = path.insert(path.indexOf(".tsv"), "-data");
	QFile file(pathData);

	//create a second file for the labels
	QString pathLabels = path.insert(path.indexOf(".tsv"), "-labels");
	writeLabelFile(pathLabels);

	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << file.errorString();
	}

	QTextStream out(&file);
	out.setGenerateByteOrderMark(true);
	out.setCodec("UTF-8");

	vector<CsvRow>::iterator row;
	for (row = this->rows.begin(); row < this->rows.end(); ++row) {
		if (row->getTool().getKontext() == "NA") {
			continue;
		}
		out << row->getTool().getName() << " " << row->getTool().getKontext() << endl;
	}
	file.close();
}


void CsvFile::writeVectorFile(QString path) {
	//open file
	QString pathData = path.insert(path.indexOf(".tsv"), "-tfIdf");
	QFile file(pathData);

	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << file.errorString();
	}

	QTextStream out(&file);
	out.setGenerateByteOrderMark(true);
	out.setCodec("UTF-8");

	vector<CsvRow>::iterator row;

	for (row = this->rows.begin(); row < this->rows.end(); ++row) {
		Tool&t = row->getTool();

		//write the file
		out << row->getParent() << " ";
		int i = 1;
		for (pair<const QString, double>& tool : t.getTfIdf()) {

			if (tool.second > 0) {
				out << i << ":" << tool.second << " ";
			}
			++i;
		}

		out << endl;
	}

	file.close();
}

void CsvFile::writeLabelFile(QString pathLabels) {
	//open file
	QFile file(pathLabels);

	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << file.errorString();
	}

	QTextStream out(&file);
	out.setGenerateByteOrderMark(true);
	out.setCodec("UTF-8");

	vector<CsvRow>::iterator row;
	for (row = this->rows.begin(); row < this->rows.end(); ++row) {
		if (row->getTool().getKontext() == "NA") {
			continue;
		}
		out << row->getParent() << endl;
	}
	file.close();
}

void CsvFile::filterEmptyContexts() {
	vector<CsvRow>& data = this->rows;
	//int c = 0;

	for (int i = 0; i < data.size(); ++i) {
		if (data.at(i).getTool().getKontext() == "NA") {
			data.erase(data.begin() + i);
			--i;
			//++c;
		}
	}
}

void CsvFile::randomize() {
	// Daten mischen
	//um (z.B. zu Testzwecken) immer die gleiche Randomisierung zu bekommen: seed-Parameter aus re entfernen
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto re = default_random_engine(seed);
	shuffle(begin(this->rows), end(this->rows), re);
}


void CsvFile::makeClassBoWs() {
	multimap<int, map<QString, int>> BoWs;
	multimap<int, map<QString, int>>::iterator searchBoWs;
	map<QString, int>::iterator searchWords, it;
	vector<CsvRow> data = this->rows;

	map<QString, int> wordCount = this->baseBoW;

	for (int i = 0; i < data.size(); ++i) {
		int classId = data.at(i).getParent();

		//parent finden und die WordList rausholen
		searchBoWs = BoWs.find(classId);

		//dafür sorgen, dass search BoWs auf jeden Fall einen Wert hat 
		if (searchBoWs == BoWs.end()) {
			BoWs.insert(pair<int, map<QString, int>>(classId, wordCount));
			searchBoWs = BoWs.find(classId);
		}

		map<QString, int>& value = searchBoWs->second;

		//Kontexte tokenisieren
		QString context = data.at(i).getTool().getKontext();
		QStringList wordList = context.split(QRegExp("\\W+"));

		//Worte in der wordCount in WordList erfassen und zählen
		QStringList::iterator it;
		for (it = wordList.begin(); it != wordList.end(); ++it) {
			searchWords = value.find((*it));

			if (searchWords != searchBoWs->second.end()) {
				value.at(searchWords->first) += 1;
			}
			else {
				value.insert(pair<QString, int>((*it), 1));
			}
		}

		//WordList der ParentClass zuweisen
		//searchBoWs->second = wordCount;
	}

	//ACHTUNG! Ergebnisse sind nicht normalisiert, unsinnige Zeichen wie ")" o.ä. sind auch drin. Ergebnisse definitv nicht perfekt.
	this->classBoWs = BoWs;
}

void CsvFile::makeTotalBoW() {
	map<QString, int> wordCount;
	map<QString, int>::iterator searchBoWs;
	map<QString, int>::iterator searchWords;

	vector<CsvRow> data = this->rows;

	for (int i = 0; i < data.size(); ++i) {

		//Kontexte tokenisieren
		QString context = data.at(i).getTool().getKontext();
		QStringList wordList = context.split(QRegExp("\\W+"));

		//Worte in der wordCount in WordList erfassen und zählen
		QStringList::iterator it;
		for (it = wordList.begin(); it != wordList.end(); ++it) {
			searchWords = wordCount.find((*it));

			if (searchWords != wordCount.end()) {
				wordCount.at(searchWords->first) += 1;
			}
			else {
				wordCount.insert(pair<QString, int>((*it), 1));
			}
		}
	}

	//ACHTUNG! Ergebnisse sind nicht normalisiert, unsinnige Zeichen wie ")" o.ä. sind auch drin. Ergebnisse definitv nicht perfekt.
	this->totalBoW = wordCount;
	makeBaseBoW();
}

void CsvFile::makeBaseBoW() {
	map<QString, int>::iterator it;
	map<QString, int> baseBoW = totalBoW;

	for (it = baseBoW.begin(); it != baseBoW.end(); ++it) {
		it->second = 0;
	}

	this->baseBoW = baseBoW;
}

void CsvFile::makeSets(int n) {
	//Daten ohne Kontext filtern
	//ACHTUNG! Wenn Klassifizierung in gesonderter Methode stattfindet, gehört dieser Code dahin!
	/* vector<CsvRow> data = this->rows;

	 for (int i = 0; i < data.size(); ++i) {
	 if (data.at(i).getTool().getKontext() == "NA") {
	 data.erase(data.begin() + i);
	 --i;
	 }
	 }*/

	vector<CsvRow> data = this->rows;

	this->makeClassBoWs();

	// n Sets aus Trainings- und Testdaten erstellen 
	for (int i = 1; i < n; ++i) {
		vector<Tool> testData;
		vector<Tool> trainingData;

		int setStart = data.size() / n * (i - 1);
		int setEnd = (data.size() / n * i) - 1;

		for (int j = 0; j < data.size(); ++j) {
			if (j >= setStart && j <= setEnd) {
				testData.push_back(data.at(j).getTool());
			}
			else {
				trainingData.push_back(data.at(j).getTool());
			}
		}

		//hier müssen die Vektoren entweder weiterverarbeitet oder in einer Datenstruktur abgelegt werden

		//diese Instruktion steht nur hier, damit man einen breakpoint setzen und die Vektoren ansehen kann
		int z = 0;
	}
}

//Problem: Tf-Idf wird nicht zurückgespeichert.
void CsvFile::addFeatures() {

	multimap<int, map<QString, int>>::iterator it;
	map<int, int> totalWords;
	
	for (it = classBoWs.begin(); it != classBoWs.end(); ++it) {
		map<QString, int>& BoW = it->second;
		int total = accumulate(begin(BoW), std::end(BoW), 0, [](const int previous, const std::pair<QString, int>& p) { return previous + p.second; });
		totalWords.insert(pair<int, int> {it->first, total});
	}

	for (int i = 0; i < this->rows.size(); ++i) {
		Tool& t = rows[i].getTool();
		t.calculateTfIdf(baseBoW, classBoWs, totalWords, rows[i].getParent());
		rows[i].setTool(t);
	}
}