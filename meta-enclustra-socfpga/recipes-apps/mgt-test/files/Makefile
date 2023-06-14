CFLAGS ?= -Wall -O0 -g3
CXX ?= g++
EXEC = mgt-test

OBJECTS = \
	$(addsuffix .o, $(basename $(wildcard *.c)))

INC_DIR = \
	-I.

all: $(EXEC)

%.o : %.c
	$(CXX) -o $@ -c $< $(INC_DIR) $(CFLAGS)

$(EXEC): $(OBJECTS)
	echo Building executable file: $@...
	${CXX} $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(INC_DIR) $(LIBS)

clean:
	$(if $(wildcard $(EXEC)), rm "$(EXEC)")
	$(foreach obj, $(OBJECTS), $(if $(wildcard obj), rm "obj"))
