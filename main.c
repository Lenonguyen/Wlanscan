#include <stdio.h>
#include "wlanscan.h"
#include <stdlib.h>
#include <unistd.h>
#define COMMAND "sudo iwlist wlan0 scan | egrep \"Channel|Quality|Address|ESSID\" >scan.txt"
int main(void){
	while(1){
		system(COMMAND);
		// read data from scan.txt, send it to server php file
		read_wlan();
		printf("Data is to be processed\n");
		sleep(5);

	}
}
