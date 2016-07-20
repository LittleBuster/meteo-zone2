#include "../../server/configs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void exit_fail()
{
	puts("-----------------------------");
	puts("[ERROR] Test crashed!");
	exit(-1);
}

int main(void)
{
	puts("Starting \"Server Configs\" test...");
	puts("-------------------------");

	if (!configs_load("../../server/meteosrv.conf")) {
		puts("[FAIL] Error reading configs file.");
		exit_fail();	
	}

	struct server_cfg *sc = configs_get_server();
	struct database_cfg *dbc = configs_get_database();

	if (sc->port != 5000) {
		puts("[FAIL] Fail reading server port.");
		exit_fail();
	}
	puts("[OK] Reading server port.");

	if (sc->max_users != 1000) {
		puts("[FAIL] Fail reading max users.");
		exit_fail();
	}
	puts("[OK] Reading server max_users.");

	/*
	 * Database configs
	 */
	if (strcmp(dbc->ip, "127.0.0.1")) {
		puts("[FAIL] Fail reading database ip.");
		exit_fail();
	}
	puts("[OK] Reading database ip.");

	if (strcmp(dbc->user, "test")) {
		puts("[FAIL] Fail reading database user.");
		exit_fail();
	}
	puts("[OK] Reading database user.");

	if (strcmp(dbc->passwd, "123")) {
		puts("[FAIL] Fail reading database password.");
		exit_fail();
	}
	puts("[OK] Reading database password.");

	if (strcmp(dbc->base, "meteo")) {
		puts("[FAIL] Fail reading database base.");
		exit_fail();
	}
	puts("[OK] Reading database base.");

	puts("-------------------------");
	puts("[PASSED] Test finished!");
	puts("====================================");
	return 0;
}