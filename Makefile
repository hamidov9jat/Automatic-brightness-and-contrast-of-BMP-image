ARGS		=3
EXECUTABLE 	=autoadjust
CC 			=gcc
CFLAGS 		=-Wall -Werror -std=c99 -g
LDFLAGS 	=-lm -lpthread -pthread -lcunit
SOURCES 	=main.c bmp.c helper_functions.c
HEADERS 	=bmp.h helper_functions.h
OBJECTS 	=$(SOURCES:.c=.o)

all: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE) $(LDFLAGS)

%.o : %.c build_headers
	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAGS)

build_headers: $(HEADERS)

clean:
	-rm $(EXECUTABLE) $(OBJECTS) client server