# force gcc compiler, may fail, uncomment following 2 lines:
# TCC=gcc
# BCC=gcc
CC=gcc
CFLAGS = -Wall
LDFLAGS = -pthread

SOURCES = \
    framework/configuration.c \
    framework/request.c \
    framework/response.c \
    framework/tcpclient.c \
    framework/udpclient.c \
    framework/serviceagent.c \
    framework/packet.c \
    test.c

HEADERS = \
    framework/request.h \
    framework/response.h \
    framework/configuration.h \
    framework/tcpclient.h \
    framework/udpclient.h \
    framework/configuration.h \
    framework/serviceagent.h \
    framework/packet.h

# removed headers for now to prevent multiple output files error
# test: $(SOURCES) $(HEADERS)
test: $(SOURCES)