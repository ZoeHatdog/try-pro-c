CC = proc
CFLAGS = -I./src/include
LDFLAGS = -L$(ORACLE_HOME)/lib -lclntsh

SRC = src/main.pc src/db/connection.pc src/db/queries.pc
OBJ = $(SRC:.pc=.o)

TARGET = app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.pc
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean