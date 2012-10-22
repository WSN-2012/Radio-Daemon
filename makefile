# Project specific variables
BUILD_PATH=build
BUILD_NAME=daemon

# Building variables
CC=gcc
CFLAGS=-Wall

# This will be called when running "make"
all: clean
	mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) d.c -o $(BUILD_PATH)/$(BUILD_NAME)



# This will be called when running "make clean"
clean:
	rm -f $(BUILD_PATH)/* 