.PHONY: clean

CC=gcc
CXX=g++
CFLAGS=-D_XOPEN_SOURCE=600 -D_BSD_SOURCE  -pedantic -Wall -W -Wundef -Wendif-labels -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Winline -Wdisabled-optimization -fstrict-aliasing -O0 -pipe -Wno-parentheses -pthread -g

all: campaign

campaign: campaign.cc
	$(CXX) $(CFLAGS) -o campaign campaign.cc

clean:
	rm -f campaign

