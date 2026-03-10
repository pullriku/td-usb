CC := gcc
CFLAGS ?= -Wall

UNAME_S := $(shell uname -s)
RTLIB :=
ifeq ($(UNAME_S),Linux)
	RTLIB := -lrt
endif

USB_CFLAGS := $(shell command -v libusb-config >/dev/null 2>&1 && libusb-config --cflags)
USB_LIBS := $(shell command -v libusb-config >/dev/null 2>&1 && libusb-config --libs)
ifeq ($(strip $(USB_LIBS)),)
	USB_LIBS := -lusb
endif

td-usb: td-usb.c device_types.c ./linux/tdhid-libusb.c ./linux/tdtimer-posix.c tddevice.c ./devices/*.c
	$(CC) $(CFLAGS) $(USB_CFLAGS) td-usb.c device_types.c tddevice.c ./linux/tdhid-libusb.c ./linux/tdtimer-posix.c ./devices/*.c -o td-usb $(USB_LIBS) $(RTLIB) -lm

clean:
	rm -f td-usb
	rm -f *.o
