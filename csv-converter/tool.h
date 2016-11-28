#ifndef TOOL_H
#define TOOL_H

#include <QString>

class Tool
{
public:
    Tool();

    QString getName() const;
    void setName(const QString &value);

    QString getKontext() const;
    void setKontext(const QString &value);

private:
    QString name;
    QString kontext;
};

#endif // TOOL_H
