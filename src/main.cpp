/*
 * 	Main.cpp;
 *	Version 1;
 *  Created on: 27. maj 2021;
 *      Author: Thomas Rindom;
 *  CopyRight: Free;
 */

#include "Json.h"
#include "Mosq.h"
#include "Csv.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Download'd libraries */
/* https://github.com/ndevilla/iniparser */
#include "iniparser/iniparser.h"
/* https://rapidjson.org/md_doc_tutorial.html */
#include "rapidjson/document.h"

/* Namespaces */
using namespace std;
using namespace rapidjson;

/* */
char buff[512];
bool msgFlag = false;
bool stop = false;

/* Dictionary for initfile */
dictionary * ini;

/* Ctrl c */
void inthand(int signum) {
	stop = true;
}

int main(int argc, const char * argv[]) {

	signal(SIGINT, inthand);

	/* Load and Check Inifile! */
	if (argc == 2) {
		if (!(ini = iniparser_load(argv[1]))) {
			fprintf(stderr, "Invalid path to initfile!");
			exit(EXIT_FAILURE);
		}

	} else {
		fprintf(stderr, "Please provide path to initfile as argument\n");
		exit(EXIT_FAILURE);
	}

	/* Setup for syslog */
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog("Prøvestand", LOG_PID, LOG_LOCAL1);
	/* tail -f /var/log/messages */

	/* Start up msg to log */
	syslog(LOG_NOTICE, "Program started by User %d", getuid());

	/* Object of Classes*/
	Csv c;
	Json js;

	/* Json */
	Document incoming;
	StringBuffer dataOut;
	int jsonError;

	/* Mosquitto */
	int rc = 0, rp = 0, id = 0;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new(NULL, true, &id);

	mosquitto_username_pw_set(mosq,
			iniparser_getstring(ini, "mosq:username", NULL),
			iniparser_getstring(ini, "mosq:password", NULL));

	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);

	rc = mosquitto_connect(mosq, iniparser_getstring(ini, "mosq:broker", NULL),
			atoi(iniparser_getstring(ini, "mosq:port", NULL)), 10);

	if (rc) {
		syslog(LOG_NOTICE, "Could not connect to Broker, return code: %d", rc);
		exit(EXIT_FAILURE);
	}

	/* start listening on Sub */
	mosquitto_loop_start(mosq);

	while (!stop) {

		/* Reset */
		memset(buff, 0, sizeof(buff));
		dataOut.Clear();

		/* Wait for Incoming MSG */
		while (msgFlag == false && stop == false) {
		}

		msgFlag = false;

		/* Check and parse to document */
		if ((jsonError = js.jsonRead(incoming, buff)) != 0) {

			syslog(LOG_NOTICE, "Something is not right, error id %d \n",
					jsonError);
			continue;
		}

		/* Print if we get a msg */
		syslog(LOG_NOTICE, "Got msg from %s", incoming["sentBy"].GetString());
		cout << "Got msg" << endl;

		/* Create Csv for Matlab*/
		c.createCsv(incoming);

		/* Manual Wait for Simulation */
		printf("Press Enter when Simulation is done !\n");
		getchar();

		/* Read Csv from Matlab*/
		js.JsonSend(incoming, dataOut);

		/* Print what we send */
		cout << dataOut.GetString() << endl;

		rp = mosquitto_publish(mosq, NULL,
				iniparser_getstring(ini, "mosq:publish", NULL),
				strlen(dataOut.GetString()), dataOut.GetString(), 0, false);
		if (rp) {
			syslog(LOG_NOTICE, "Could not send msg, return code: %d", rp);
			continue;
		}

		/* Print if msg was sent */
		syslog(LOG_NOTICE, "Msg sent to %s", incoming["sentBy"].GetString());
		cout << "Msg sent \n" << endl;
	}

	/* Stop loop */
	mosquitto_loop_stop(mosq, true);

	/* Clean up */
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	iniparser_freedict(ini);

	/* Close syslog */
	syslog(LOG_NOTICE, "Program Closed! ");
	closelog();

	cout << "Program Closed!" << endl;

	return 0;
}
