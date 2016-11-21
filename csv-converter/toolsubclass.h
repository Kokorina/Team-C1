#ifndef TOOLSUBCLASS_H
#define TOOLSUBCLASS_H

#include <QString>
#include <vector>
#include "tool.h"

using namespace std;

class ToolSubClass
{
public:
    ToolSubClass();
    ToolSubClass(QString id, QString name);

    QString getId() const;
    void setId(QString value);

    QString getName() const;
    void setName(const QString &value);

    vector<Tool> getTools() const;
    void setTools(const vector<Tool> &value);

private:
    QString id;
    QString name;

    vector<Tool> tools;
};

#endif // TOOLSUBCLASS_H
