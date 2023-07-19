CPPFLAGS ?= -pthread -std=c++2a -Wall -Wextra -O0 -g3
CFLAGS ?= -Wall -O0 -g3

CXX ?= g++
EXEC = main

OBJECTS = \
	$(addsuffix .o, $(basename $(wildcard *.c))) \
	$(addsuffix .o, $(basename $(wildcard *.cpp)))

INC_DIR = \
	-I.

all: $(EXEC)

%.o : %.c
	$(CXX) -o $@ -c $< $(INC_DIR) $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(INC_DIR) $(CPPFLAGS)

$(EXEC): $(OBJECTS)
	echo Building executable file: $@...
	${CXX} $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(INC_DIR) $(LIBS)

mgt-test: mgt-test.o
	${CXX} $(CFLAGS) $(LDFLAGS) -o $@ mgt-test.o $(INC_DIR) $(LIBS)

clean:
	$(if $(wildcard $(EXEC)), rm "$(EXEC)")
	$(foreach obj, $(OBJECTS), $(if $(wildcard obj), rm "obj"))
