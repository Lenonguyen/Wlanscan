OBJ = main.o wlanscan.o screen.o #comm.o
APPNAME = wlanscan.a

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $< -std=c99

clean : 
	rm $(OBJ) $(APPNAME)
archive:
	tar cf wlan.tar *.c *.h makefile
