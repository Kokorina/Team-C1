#include "csvRow.h"


CsvRow::CsvRow()
{
}


CsvRow::~CsvRow()
{
}




QString CsvRow::getAuthor() const
{
	return author;
}

void CsvRow::setAuthor(const QString &value)
{
	author = value;
}

QString CsvRow::getTitlePw() const
{
	return titlePw;
}

void CsvRow::setTitlePw(const QString &value)
{
	titlePw = value;
}

QString CsvRow::getTitleCitavi() const
{
	return titleCitavi;
}

void CsvRow::setTitleCitavi(const QString &value)
{
	titleCitavi = value;
}

QString CsvRow::getSubtitle() const
{
	return subtitle;
}

void CsvRow::setSubtitle(const QString &value)
{
	subtitle = value;
}

QString CsvRow::getCity() const
{
	return city;
}

void CsvRow::setCity(const QString &value)
{
	city = value;
}

QString CsvRow::getYear() const
{
	return year;
}

void CsvRow::setYear(const QString &value)
{
	year = value;
}

QString CsvRow::getPages() const
{
	return pages;
}

void CsvRow::setPages(const QString &value)
{
	pages = value;
}

QString CsvRow::getJournalName() const
{
	return journalName;
}

void CsvRow::setJournalName(const QString &value)
{
	journalName = value;
}

QString CsvRow::getJournalVolume() const
{
	return journalVolume;
}

void CsvRow::setJournalVolume(const QString &value)
{
	journalVolume = value;
}

QString CsvRow::getJournalNumber() const
{
	return journalNumber;
}

void CsvRow::setJournalNumber(const QString &value)
{
	journalNumber = value;
}

QString CsvRow::getJournalYear() const
{
	return journalYear;
}

void CsvRow::setJournalYear(const QString &value)
{
	journalYear = value;
}

QString CsvRow::getTags() const
{
	return tags;
}

void CsvRow::setTags(const QString &value)
{
	tags = value;
}

QString CsvRow::getCitaviId() const
{
	return citaviId;
}

void CsvRow::setCitaviId(const QString &value)
{
	citaviId = value;
}