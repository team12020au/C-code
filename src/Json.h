/*
 * 	Json.h;
 *	Version 1;
 *  Created on: 27. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */
#ifndef JSON_H_
#define JSON_H_

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <iostream>
#include <string>
#include <vector>
#include <syslog.h>

using namespace rapidjson;
using namespace std;


class Json {
public:
	Json();
	virtual ~Json();
	virtual int jsonRead(Document& doc, char str[]);
	virtual void JsonSend(Document& doc, StringBuffer&);
};

#endif /* JSON_H_ */
