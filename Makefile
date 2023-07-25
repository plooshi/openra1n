CFLAGS = -I./include -Wall -Wno-pointer-sign
CFLAGS += -Os
BIN = libopenra1n.a
SOURCE = openra1n.c
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

.PHONY: all clean payloads $(BIN) lz4

all: payloads lz4 $(OBJECTS) $(BIN)

payloads:
	@mkdir -p include/payloads
	@for file in payloads/*; do \
		echo " XXD    $$file"; \
		xxd -i $$file > include/$$file.h; \
	done

$(BIN): payloads lz4 $(OBJECTS)
	@echo " AR     $(BIN)"
	@ar rcs $(BIN) $(OBJECTS)

%.o: %.c
	@$(CC) -c -I./include $(CFLAGS) $<
	@echo " CC     $<"

lz4:
	$(MAKE) -C lz4

clean:
	@echo " CLEAN  $(BIN)"
	@rm -f $(BIN)
	@rm -f $(OBJECTS)
	@echo " CLEAN  include/payloads"
	@rm -rf include/payloads
	$(MAKE) -C lz4 clean

openra1n: $(BIN)
	@$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude main.c -L. -Llz4 -lopenra1n -llz4 -o openra1n
	@echo " LD     openra1n"
