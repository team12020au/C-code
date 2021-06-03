/*
 * 	Csv.cpp;
 *	Version 1;
 *  Created on: 27. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#include "Csv.h"

Csv::Csv() {
	// TODO Auto-generated constructor stub
}

Csv::~Csv() {
	// TODO Auto-generated destructor stub
}

void Csv::createCsv(Document& doc) {

	fstream csv;
	csv.open("/home/jenslawl/Shared/matlab.csv", fstream::out);

	if (csv.is_open()) {

	csv << "batteri;job;value;load;duration\n";
	csv << doc["batteri"].GetString() << ";" << doc["job"].GetString() << ";"
			<< doc["value"].GetString() << ";" << doc["load"].GetString() << ";"
			<< doc["duration"].GetString();
	csv.close();
}
	else{
		syslog(LOG_NOTICE,"Failed to create CSV!");
	}
}


void Csv::readCsv(int& i,vector<string>& vTime, vector<string>& vVoltage,
		vector<string>& vCurrent, vector<string>& vSoc, vector<string>& vPower) {

	string first;
	string time, voltage, current, soc, power;
	ifstream csvRead;

	csvRead.open(
			"/home/jenslawl/Shared/test_results.csv",
			ifstream::in);

	if (csvRead.is_open()) {

		/* Ignore first line */
		getline(csvRead, first);

		while (!csvRead.eof()) {

			getline(csvRead, time, ',');
			vTime.push_back(time);
			getline(csvRead, voltage, ',');
			vVoltage.push_back(voltage);
			getline(csvRead, current, ',');
			vCurrent.push_back(current);
			getline(csvRead, soc, ',');
			vSoc.push_back(soc);
			getline(csvRead, power, '\n');
			vPower.push_back(power);
			i++;
		}
		csvRead.close();
	}

	else {
		syslog(LOG_NOTICE,"Failed to read CSV!");
	}

}
