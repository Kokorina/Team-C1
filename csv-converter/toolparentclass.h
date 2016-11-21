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

private:
    int id;
    QString name;
    map<QString, ToolSubClass> subclasses;
};

#endif // TOOLPARENTCLASS_H
