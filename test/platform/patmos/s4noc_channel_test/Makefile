# Makefile for building a simple Hello World program for the Patmos platform
APP = main

include $(CURDIR)/../../../../make/patmos/patmos.mk
# Paths
SRC_DIR = $(CURDIR)
BUILD_DIR = $(CURDIR)/build

# Source files
SOURCES += $(SRC_DIR)/$(APP).c 

CFLAGS += -DLF_LOG_LEVEL_ALL=LF_LOG_LEVEL_INFO

# Output binary
OUTPUT = $(BUILD_DIR)/$(APP).elf
all : $(OUTPUT)

# Build rule
$(OUTPUT): $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
