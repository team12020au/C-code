/*
 * 	Csv.h;
 *	Version 1;
 *  Created on: 27. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#ifndef CSV_H_
#define CSV_H_

#include "rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <syslog.h>

using namespace rapidjson;
using namespace std;

class Csv {
public:
	Csv();
	virtual ~Csv();
	void createCsv(Document& doc);
	void readCsv(int& i,vector<string>& vTime, vector<string>& vVoltage, vector<string>& vCurrent,
			vector<string>& vSoc, vector<string>& vPower);
};

#endif /* CSV_H_ */
