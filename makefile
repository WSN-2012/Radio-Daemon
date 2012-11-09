# Project specific variables
BUILD_PATH=build
BUILD_NAME=daemontest

# Building variables
CC=gcc
CFLAGS=-Wall  

# This will be called when running "make"
all: clean
	mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) daemon.c sdb.c devtag-allinone.c lock.c printAsciiHex.c serial.c util.c datacollection.c freq_changer.c uhx1_commander.c -o $(BUILD_PATH)/$(BUILD_NAME) -lsqlite3 -L/usr/lib/i386-linux-gnu/

# This will be called when running "make clean"
clean:
	rm -f $(BUILD_PATH)/* 