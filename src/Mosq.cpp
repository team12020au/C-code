/*
 * 	Mosq.cpp;
 *	Version 1;
 *  Created on: 22. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#include "Mosq.h"

extern dictionary * ini;
extern char buff[512];
extern bool msgFlag;

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("Got Connecting\nID: %d\n", *(int *) obj);
	syslog(LOG_NOTICE,"Got Connecting\nID: %d\n", *(int *) obj);
	if (rc) {
		syslog(LOG_NOTICE, "Error with result code: %d", rc);
		exit(EXIT_FAILURE);
	}
	mosquitto_subscribe(mosq, NULL, iniparser_getstring(ini, "mosq:subscribe", NULL), 0);
}

void on_message(struct mosquitto *mosq, void *obj,
		const struct mosquitto_message *msg) {
	printf("New message with topic %s: %s\n", msg->topic,
			(char *) msg->payload);
	msgFlag = true;
	sprintf(buff, "%s", (char *) msg->payload);

	void mosquitto_message_free(struct mosquitto_message **msg);

}
