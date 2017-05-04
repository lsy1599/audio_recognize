#common makefile header

DIR_INC = ../../lib/include
DIR_BIN = ../../bin
DIR_LIB = ../../lib

TARGET	= asr_record_demo
BIN_TARGET = $(TARGET)

CROSS_COMPILE = 
CFLAGS = -g -Wall -I$(DIR_INC) -I../../lib


LDFLAGS := -L$(DIR_LIB)/

LDFLAGS += -lmsc -lrt -ldl -lpthread -lasound -Wl,-rpath=../lib

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(BIN_TARGET) : $(OBJECTS)
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o $(DIR_BIN)/$@ $(LDFLAGS)

%.o : %.c
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@
clean:
	@rm -f *.o $(BIN_TARGET)

.PHONY:clean

#common makefile foot

