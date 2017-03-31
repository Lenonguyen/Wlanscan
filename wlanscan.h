typedef struct{
	int channel;
	char essid[100];
	double frequency;
	double signalLevel;
}WLANINFO;

#define SCANFILE "scan.txt"
#define DEBUG

void read_wlan(void);
void removeSpace(char []);
int readChannel(char []);
int readSignal(char []);
void readESSID(char [], char []);
