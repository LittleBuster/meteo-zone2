#include "../../pi/configs.h"
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
	puts("Starting \"Configs\" test...");
	puts("-------------------------");

	if (!configs_load("../../pi/meteo.conf")) {
		puts("[FAIL] Error reading configs file.");
		exit_fail();	
	}

	struct checker_cfg *cc = configs_get_checker();
	struct server_cfg *sc = configs_get_server();
	struct device_cfg *dc = configs_get_device();
	struct sensors_cfg *ss = configs_get_sensors();

	if (cc->interval != 5) {
		puts("[FAIL] Fail reading interval configs.");
		exit_fail();
	}
	puts("[OK] Reading interval configs.");
	
	if (strcmp(sc->ip, "127.0.0.1")) {
		puts("[FAIL] Fail reading IP address.");
		exit_fail();
	}
	puts("[OK] Reading IP address.");

	if (sc->port != 5000) {
		puts("[FAIL] Fail reading Port.");
		exit_fail();
	}
	puts("[OK] Reading Port.");

	if (dc->id != 10000001) {
		puts("[FAIL] Fail reading device id.");
		exit_fail();
	}
	puts("[OK] Reading device id.");

	if (strcmp(dc->key, "")) {
		puts("[FAIL] Fail reading device key.");
		exit_fail();
	}
	puts("[OK] Reading device key.");

	if (ss->dht_in != 4) {
		puts("[FAIL] Fail reading inside sensor port.");
		exit_fail();
	}
	puts("[OK] Reading inside sensor port.");

	if (ss->dht_out != 7) {
		puts("[FAIL] Fail reading outside sensor port.");
		exit_fail();
	}
	puts("[OK] Reading outside sensor port.");

	puts("-------------------------");
	puts("[PASSED] Test finished!");
	puts("====================================");
	return 0;
}