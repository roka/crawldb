P=crawldb
OPENSSL = `pkg-config --cflags --libs openssl`
CFLAGS = -g -Wall -O3 -I./include $(OPENSSL)
LDLIBS=
CC=gcc
OBJECTS := $(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))
TESTOBJ := $(patsubst test/%.c,testobj/%.o,$(wildcard test/*.c))

all: $(P)

debug: CFLAGS += -DDEBUG
debug: $(P)

test:	CFLAGS += `pkg-config --cflags glib-2.0` -DTEST -DDEBUG
test: LDLIBS += `pkg-config --libs glib-2.0`
test: $(TESTOBJ) $(OBJECTS)
	$(CC) $(LDLIBS) $(CFLAGS) -o test_suite $(TESTOBJ) $(OBJECTS)
	./test_suite

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -c $< -o $@ $(CFLAGS)

testobj/%.o: test/%.c
	@mkdir -p testobj
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f obj/*.o crawldb
	rm -f testobj/*.o

