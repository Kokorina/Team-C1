#ifndef TOOLPARENTCLASS_H
#define TOOLPARENTCLASS_H

#include <QString>
#include <map>
#include "toolsubclass.h"

using namespace std;

class ToolParentClass
{
public:
    ToolParentClass();
    ToolParentClass(int id, QString name);

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

	map<QString, ToolSubClass> getSubclasses() const;
	void setSubclasses(const map<QString, ToolSubClass> &value);

	int getTotalWords();
	void calculateTotalWords(); //im Mainwindow o.ä. irgendwo abrufen!

	//methoden für BoW (get, make)

private:
    int id;
    QString name;
    map<QString, ToolSubClass> subclasses;
	int totalWords;
	map<QString, int> BoW;
};

#endif // TOOLPARENTCLASS_H
