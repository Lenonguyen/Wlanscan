#include "wlanscan.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this function reads scan.txt file line by line, scan.txt is formatted in this way:
// cell # - Address: 6 bytes of MAC address
//	Channel:#
//	Frequency:# GHz (Channel #)
//	Quality=#/# Signal level=# dBm
//	ESSID:"xxx"
void read_wlan(void){
	FILE *fp;
	char line[200], essid[100];	// a line of text from scan.txt
	int c, ch, slevel;	// c is a line counter, ch is channel number

	fp = fopen(SCANFILE, "r");	// open the file in read-only mode
	if(fp == NULL){
		printf("Cannot open file scan.txt \n", SCANFILE);
		return;
	}
	while(fgets(line, 200, fp)!=NULL) {	// read file line by line
		removeSpace(line);
//		printf("%s\n", line);
		if(strncmp(line, "Cell", 4)==0){	// if we are at the first line of a cell
#ifdef DEBUG
			printf("New cell\t");
#endif
			c = 0;	// line counter reset
		}
		else{		// we are reading info of a cell
			c++;	// line counter increments
			if(c==1){
				ch = readChannel(line);	// if it's 2nd line, read channel no.
				printf("Channel %d\t", ch);
			}
			if(c==3){
				slevel = readSignal(line);	// if it's 4th line, read signal level
				printf("Signal power: %d dBm\t", slevel);
			}
			if(c==4){
				readESSID(essid, line);	// if it's last line, read ESSID
				printf("ESSID: %s\n", essid);
			}
		}
	}
}

// this function removes all the white spaces at the beginning of a string and 
// replaces the old one with new one. The input string might be "	Cell 01 - xxxxx",
// the output string is "Cell 01 -xxxxx
void removeSpace(char s[]){
	int i, len=strlen(s);
	for(i=0; i<len; i++){
		if(s[i] != ' ' || s[i] == '\t' || s[i] == '\n') continue;
		else break;
	}	// if a non-space char is found, i holds the location of that char
	strcpy(s, &s[i]);	// simply copy the non-space string to
}

// this function reads channel value from the 2nd line of a Cell, the line is 
// organized as "Channel:##", the last 1 or 2 symbols indicates the channel value
int readChannel(char s[]){
	int i, len=strlen(s);
	for(i=0; i<len; i++){	// search for the first digit symbol
		if(s[i]>='0' && s[i]<='9') break;	// stop when we found a digit symbol
	}
	return atoi(&s[i]);	// atoi converts ascii to integer
}

// this function reads AP's RSSI (received signal strength indicator) as dBm value
// the input is the line containing "Quality=xx/xx Signal level=-yy dBm". There are
// 3 integer numbers in this string. sscanf() can be used to do the job. Or you can
// locate 2nd '=' sign and read the following value. We use the 2nd method.
int readSignal(char s[]){
	int i,c, len = strlen(s);
	char temp[10]={'\0'};	// temperal string to hold "-yy" 

	for(i=0, c=0; i<len; i++){	// find 2nd '=' sign
		if(s[i] == '='){
			if(++c == 2) break;
		}
	}
	strncpy(temp, &s[i+1], 3);
	return atoi(temp);
}

// this function reads ESSID from a line. The line is formatted as "ESSID:"rabe_vasa""
// we simply need to locate the first '""' symbol and copy the rest of line to id[].
// And replace the last '"' symbol by null character
void readESSID(char id[], char line[]){
	int i, len = strlen(line);
	for(i=0; i<len; i++){
		if(line[i]=='"') break;
	}
	strcpy(id, &line[i+1]);	// copy the ssid
	for(i=0; i<strlen(id); i++){
		if(id[i]=='"'){
			id[i] = '\0';	// replace the double quote by null
			break;
		}
	}
}
