/*
 * 	Mosq.h;
 *	Version 1;
 *  Created on: 22. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#ifndef MOSQ_H_
#define MOSQ_H_

#include "mosquitto/mosquitto.h"
#include "iniparser/iniparser.h"
#include <syslog.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj,
		const struct mosquitto_message *msg);

#endif /* MOSQ_H_ */
