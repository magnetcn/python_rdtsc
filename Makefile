SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c, %.o, $(SRC))
OUT:=rdtsc.so

all: $(OUT)

CFLAGS:=$(shell python3.5-config --cflags)
LDFLAGS:= -shared $(shell python3.5-config --ldflags) -Wl,-rpath=./ 

%.o:%.c
	gcc -c $^ $(CFLAGS) -o $@

$(OUT):$(OBJ)
	gcc -o $@ $(LDFLAGS) $^

clean:
	-@rm -f $(OUT)
	-@rm -f *.o

