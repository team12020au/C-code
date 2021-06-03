/*
 * 	Json.cpp;
 *	Version 1;
 *  Created on: 27. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#include "Json.h"
#include "Csv.h"

Json::Json() {
	// TODO Auto-generated constructor stub
}

Json::~Json() {
	// TODO Auto-generated destructor stub
}

int Json::jsonRead(Document& doc, char str[]) {

	/* Reading String into Document
	 * and checking for errors */
	if (doc.ParseInsitu(str).HasParseError()) {
		return -1;
	}

	if (!doc.HasMember("protocolVersion")) {
		return -2;
	}

	if (!doc.HasMember("sentBy")) {
		return -3;
	}

	if (!doc.HasMember("msgType")) {
		return -4;
	}

	if (!doc.HasMember("statusCode")) {
		return -5;
	}

	if (!doc.HasMember("batteri")) {
		return -6;
	}

	if (!doc.HasMember("job")) {
		return -7;
	}

	if (!doc.HasMember("value")) {
		return -8;
	}

	if (!doc.HasMember("load")) {
		return -9;
	}

	if (!doc.HasMember("duration")) {
		return -10;
	}

	return 0;
}

void Json::JsonSend(Document& doc, StringBuffer& data) {

	int i = 0;
	vector<string> vTime;
	vector<string> vVoltage;
	vector<string> vCurrent;
	vector<string> vSoc;
	vector<string> vPower;

	Csv c;

	c.readCsv(i, vTime, vVoltage, vCurrent, vSoc, vPower);

	Writer<StringBuffer> writer(data);

	writer.StartObject();
	writer.Key("protocolVersion");
	writer.Double(1.1);
	writer.Key("sentBy");
	writer.String(doc["sentBy"].GetString());
	writer.Key("msgType");
	writer.String(doc["msgType"].GetString());
	writer.Key("commandList");
	writer.StartArray();
	writer.String("Batteritest");
	writer.EndArray();
	writer.Key("statusCode");
	writer.String(doc["statusCode"].GetString());
	writer.Key("parameterObj");
	writer.StartObject();
	writer.Key("batteri");
	writer.String(doc["batteri"].GetString());
	writer.Key("job");
	writer.String(doc["job"].GetString());
	writer.Key("value");
	writer.String(doc["value"].GetString());
	writer.Key("load");
	writer.String(doc["load"].GetString());
	writer.Key("duration");
	writer.String(doc["duration"].GetString());
	writer.EndObject();
	writer.Key("dataObj");
	writer.StartObject();
	writer.Key("tid");
	writer.StartArray();
	for (int n = 0; n < i - 1; n++) {
		writer.Double(atof(vTime.at(n).c_str()));
	}
	writer.EndArray();
	writer.Key("volt");
	writer.StartArray();
	for (int n = 0; n < i - 1; n++) {
		writer.Double(atof(vVoltage.at(n).c_str()));
	}
	writer.EndArray();
	writer.Key("current");
	writer.StartArray();
	for (int n = 0; n < i - 1; n++) {
		writer.Double(atof(vCurrent.at(n).c_str()));
	}
	writer.EndArray();
	writer.Key("soc");
	writer.StartArray();
	for (int n = 0; n < i - 1; n++) {
		writer.Double(atof(vSoc.at(n).c_str()));
	}
	writer.EndArray();
	writer.Key("power");
	writer.StartArray();
	for (int n = 0; n < i - 1; n++) {
		writer.Double(atof(vPower.at(n).c_str()));
	}
	writer.EndArray();
	writer.EndObject();
	writer.EndObject();
}
