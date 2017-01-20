#include "tool.h"
#include <QStringList>
#include <cmath>

Tool::Tool()
{

}
QString Tool::getName() const
{
    return name;
}

void Tool::setName(const QString &value)
{
    name = value;
}
QString Tool::getKontext() const
{
    return kontext;
}

void Tool::setKontext(const QString &value)
{
    kontext = value;
}

map <QString, double> Tool::getTfIdf() {
	return tfIdf;
}

void Tool::setTfIdf(map<QString, double> value) {
	tfIdf = value;
}

map<QString, double> Tool::calculateTfIdf(map<QString, int> baseBow,  multimap<int, map<QString, int>>& classBoWs, int parentClass) {
	multimap<int, map<QString, int>>::iterator searchParent, itParents;

	//Basis-Map erzeugen
	for (auto it = baseBow.begin(); it != baseBow.end(); ++it) {
		tfIdf[it->first] = (double)it->second;
	}

	//Klasse finden
	searchParent = classBoWs.find(parentClass);
	if (searchParent != classBoWs.end()) {
		map<QString, int>& parentClassBoW = searchParent->second;
		
		//Kontexte tokenisieren
		QString context = this->getKontext();
		QStringList wordList = context.split(QRegExp("\\W+"));

		//Worte in der wordList suchen und ihr Vorkommen in der Klasse z�hlen
		QStringList::iterator it;
		for (it = wordList.begin(); it != wordList.end(); ++it) {
			int wordFrequencyInClass = 0;
			int classesWithWord = 0;
			map<QString, int>::iterator searchWords = parentClassBoW.find((*it));

			//aus ClassBoW die H�ufigkeit in der Klasse holen
			if (searchWords != parentClassBoW.end()) {
				wordFrequencyInClass = searchWords->second;
			}

			//durch die Klassen loopen und z�hlen, in wie vielen das Wort vorkommt
			map<QString, int>::iterator searchInClass;
			for (itParents = classBoWs.begin(); itParents != classBoWs.end(); ++itParents) {
				searchInClass = itParents->second.find((*it));

				if (searchInClass != itParents->second.end()) {
					classesWithWord += 1;
				}
			}

			//tf-idf berechnen
			tfIdf[searchWords->first] = (wordFrequencyInClass/wordList.size()) / log(8 / classesWithWord + 1);
		}
		return tfIdf;
	}
	return tfIdf;
}


