#CROSS_COMPILE =
CROSS_COMPILE = /usr/bin/arm-linux-gnueabihf-

#STATIC=y

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

LDFLAGS =

ifeq ($(STATIC),y)
LDFLAGS += -static
else
LDFLAGS += -Wl,-pie
endif

CFLAGS =
CFLAGS += -fPIC

INC = -I ./tinyalsa/include

LIBS = ./tinyalsa/src/libtinyalsa.a
LIBS += -lc

C_SOURCES =  rda_snd_cfg.c

OBJECTS = $(C_SOURCES:.c=.o)
vpath %.c $(sort $(dir $(C_SOURCES)))

%.o: %.c
	$(CC) $(INC) -c $(CFLAGS) $< -o $@

all: tinyalsa/src/libtinyalsa.a $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(LDFLAGS) -o rda_snd_cfg

tinyalsa/src/libtinyalsa.a:
	make -C tinyalsa/src CROSS_COMPILE=$(CROSS_COMPILE)

.PHONY: clean
clean:
	make -C tinyalsa/src clean
	rm -f $(OBJECTS) rda_snd_cfg
