#ifndef TOOLPARENTCLASS_H
#define TOOLPARENTCLASS_H

#include <QString>
#include <vector>
#include "toolsubclass.h"

using namespace std;

class ToolParentClass
{
public:
    ToolParentClass();

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    vector<ToolSubClass> getSubclasses() const;
    void setSubclasses(const vector<ToolSubClass> &value);

private:
    int id;
    QString name;
    vector<ToolSubClass> subclasses;


};

#endif // TOOLPARENTCLASS_H
