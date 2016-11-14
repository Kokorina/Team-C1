#pragma once

using namespace std;

#include <qstring.h>
#include "CsvFile.h"


class CsvHandler {
public:
	CsvHandler();
	~CsvHandler();

	CsvFile readCsv(QString path);
};

