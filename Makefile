CFLAGS=-c -g -Wextra -Werror -lc
CC=gcc

all: recv_signal signal_handler send_signal signal_alarm signal_segfault signal_sigaction reciever server

recv_signal: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

send_signal: send_signal.o
	$(CC) -o send_signal send_signal.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_segfault: signal_segfault.o
	$(CC) -o signal_segfault signal_segfault.o

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_sigaction: signal_sigaction.o
	$(CC) -o signal_sigaction signal_sigaction.o

server: server.o
	$(CC) -o server server.o

reciever: reciever.o
	$(CC) -o reciever reciever.o

clean:
	rm -f *.o recv_signal send_signal signal_alarm signal_segfault signal_handler reciever server

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<


       