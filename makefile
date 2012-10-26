# Project specific variables
BUILD_PATH=build
BUILD_NAME=daemon

# Building variables
CC=gcc
CFLAGS=-Wall -lsqlite3 

# This will be called when running "make"
all: clean
	mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) radio_daemon.c timer.c -o $(BUILD_PATH)/$(BUILD_NAME) -L/usr/lib/i386-linux-gnu/

# This will be called when running "make clean"
clean:
	rm -f $(BUILD_PATH)/* 