#ifndef TOOLSUBCLASS_H
#define TOOLSUBCLASS_H

#include <QString>

class ToolSubClass
{
public:
    ToolSubClass();

    char getId() const;
    void setId(char value);

    QString getName() const;
    void setName(const QString &value);

private:
    char id;
    QString name;
};

#endif // TOOLSUBCLASS_H
