BIN=raccoon
CPP=g++
INCLUDE_DIRS=/usr/include/axe
INCLUDE_FLAGS=$(patsubst %,-I%,$(INCLUDE_DIRS))
CPP_FLAGS=-Wall -std=c++11 $(INCLUDE_FLAGS)
OBJ=main.o ast/Node.o back/Path.o back/Reasoner.o back/fm1/fm1.o exceptions/DifferentTypeExpected.o exceptions/MethodNotImplemented.o exceptions/NoConnectionsAvailable.o front/Parser.o front/alc/alc.o rep/Clause.o rep/Concept.o rep/ElementManager.o rep/KB.o rep/Literal.o rep/Quantifier.o rep/Role.o rep/res/Realization.o
SRC_DIR=src/
RELEASE_DIR=bin/release/
RELEASE_OBJ=$(patsubst %.o,$(RELEASE_DIR)%.o,$(OBJ))
RELEASE_BIN=$(RELEASE_DIR)$(BIN)
DEBUG_DIR=bin/debug/
DEBUG_OBJ=$(patsubst %.o,$(DEBUG_DIR)%.o,$(OBJ))
DEBUG_BIN=$(DEBUG_DIR)$(BIN)

all : $(RELEASE_BIN) $(DEBUG_BIN)

release : $(RELEASE_BIN)

$(RELEASE_BIN) : $(RELEASE_OBJ)
	$(CPP) $(CPP_FLAGS) -o $(RELEASE_BIN) $(RELEASE_OBJ)

debug : $(DEBUG_BIN)

$(DEBUG_BIN) : $(DEBUG_OBJ)
	mkdir -p $(dir $(DEBUG_BIN))
	$(CPP) $(CPP_FLAGS) -o $(DEBUG_BIN) $(DEBUG_OBJ)

$(RELEASE_DIR)%.o : $(SRC_DIR)%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -c -o $@ $< 

$(DEBUG_DIR)%.o : $(SRC_DIR)%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

clean :
	rm -rf bin
