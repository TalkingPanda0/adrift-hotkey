CC=gcc
CFLAGS=-lX11
OUT=splitter
FILES=xhklib.c hotkey_splitter.c
all: build

config.h:
	cp config.def.h $@


build: clean config.h
	$(CC) $(FILES) -o $(OUT) $(CFLAGS)
clean:
	    rm -rf $(OUT)
