CFLAGS = -I./include -Wall -Wno-pointer-sign
CFLAGS += -Os
BIN = ../liblz4.a
SOURCE = lz4.c lz4hc.c
OBJECTS = $(patsubst %.c, %.o, $(SOURCE))
ifeq ($(LIBUSB),1)
	CC = gcc
	CFLAGS += -DHAVE_LIBUSB
	LDFLAGS += -lusb-1.0
else
	CC = xcrun -sdk macosx gcc
	CFLAGS += -arch x86_64 -arch arm64
	LDFLAGS += -framework IOKit -framework CoreFoundation
endif

.PHONY: all clean $(BIN)

all: $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	@echo " AR     liblz4.a"
	@ar rcs $(BIN) $(OBJECTS)

%.o: %.c
	@$(CC) -c -I../include $(CFLAGS) $<
	@echo " CC     $<"

clean:
	@echo " CLEAN  $(BIN)"
	@rm -f $(BIN)
	@rm -f $(OBJECTS)
