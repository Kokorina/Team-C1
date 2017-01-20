#ifndef TOOL_H
#define TOOL_H

#include <map>
#include <QString>

using namespace std;

class Tool
{
public:
    Tool();

    QString getName() const;
    void setName(const QString &value);

    QString getKontext() const;
    void setKontext(const QString &value);

	map<QString, double> calculateTfIdf(map<QString, int> baseBow, multimap<int, map<QString, int>>& classBoWs, int parentClass);
	void setTfIdf(map<QString, double> value);
	map<QString, double> getTfIdf();

private:
    QString name;
    QString kontext;
	map<QString, double> tfIdf;
};

#endif // TOOL_H
