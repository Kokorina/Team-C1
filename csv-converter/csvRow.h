#pragma once

#include <qstring.h>

class CsvRow
{
public:
	CsvRow();
	~CsvRow();

	QString getAuthor() const;
	void setAuthor(const QString &value);

	QString getTitlePw() const;
	void setTitlePw(const QString &value);

	QString getTitleCitavi() const;
	void setTitleCitavi(const QString &value);

	QString getSubtitle() const;
	void setSubtitle(const QString &value);

	QString getCity() const;
	void setCity(const QString &value);

	QString getYear() const;
	void setYear(const QString &value);

	QString getPages() const;
	void setPages(const QString &value);

	QString getJournalName() const;
	void setJournalName(const QString &value);

	QString getJournalVolume() const;
	void setJournalVolume(const QString &value);

	QString getJournalNumber() const;
	void setJournalNumber(const QString &value);

	QString getJournalYear() const;
	void setJournalYear(const QString &value);

	QString getTags() const;
	void setTags(const QString &value);

	QString getCitaviId() const;
	void setCitaviId(const QString &value);

private:
	QString author;
	QString titlePw;
	QString titleCitavi;
	QString subtitle;
	QString city;
	QString year;
	QString pages;
	QString journalName;
	QString journalVolume;
	QString journalNumber;
	QString journalYear;
	QString tags;
	QString citaviId;
};

