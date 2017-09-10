# forced gcc compiler, may fail, uncomment following 2 lines:
# TCC=gcc
# BCC=gcc
CC=gcc
CFLAGS = -Wall
LDFLAGS = -pthread

TEST_SOURCES = \
  framework/configuration.c \
  framework/request.c \
  framework/response.c \
  framework/tcpclient.c \
  framework/udpclient.c \
  framework/serviceagent.c \
  framework/packet.c \
  test.c

TEST_HEADERS = \
  framework/request.h \
  framework/response.h \
  framework/configuration.h \
  framework/tcpclient.h \
  framework/udpclient.h \
  framework/configuration.h \
  framework/serviceagent.h \
  framework/packet.h

# @TODO: use objects
test: $(TEST_SOURCES)

tcpserver: framework/tcpserver.o
	$(CC) -o tcpserver framework/tcpserver.o $(CFLAGS) $(LDFLAGS)

udpserver: framework/udpserver.o
	$(CC) -o udpserver framework/udpserver.o $(CFLAGS) $(LDFLAGS)

clean:
	rm -f test tcpserver udpserver framework/*pserver.o

run_test: test tcpserver udpserver
	./tcpserver 127.0.0.1 9879 > tcp_1.log &
	./tcpserver 127.0.0.1 9889 > tcp_2.log &
	./tcpserver 127.0.0.1 9899 > tcp_3.log &
	./udpserver 127.0.0.1 9979 > udp_1.log &
	./udpserver 127.0.0.1 9989 > udp_2.log &
	./udpserver 127.0.0.1 9999 > udp_3.log &
	./test y y y y
	killall tcpserver
	killall udpserver
