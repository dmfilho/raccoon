CXX = g++
CC = gcc

CXX_FLAGS = -std=c++11 -O3
CC_FLAGS = -O3

DBG_CXX_FLAGS = -std=c++11 -O0 -g
DBG_CC_FLAGS = -O0 -g

OBJECTS = CMALCr.o \
          Clause.o \
          ClauseSet.o \
          ConceptRealization.o \
          ConnectionList.o \
          ILiteralRealization.o \
          Instance.o \
          Literal.o \
          Ontology.o \
          Path.o \
          RoleRealization.o \
          UniversalRealization.o \
          Options.o \
          Owl2.o \
          owl2_parser.o \
          main.o

REL_DIR = build/release/
DBG_DIR = build/debug/
SRC_DIR = src/

REL_OBJ = $(addprefix $(REL_DIR),$(OBJECTS))
DBG_OBJ = $(addprefix $(DBG_DIR),$(OBJECTS))

REL_MKDIR = @mkdir -p $(REL_DIR)
DBG_MKDIR = @mkdir -p $(DBG_DIR)

.PHONY : all

all: raccoon raccoon_dbg

raccoon: $(REL_OBJ)
	$(CXX) $(CXX_FLAGS) -o $@ $(REL_OBJ)

$(REL_DIR)%.o : $(SRC_DIR)back/%.cpp
	$(REL_MKDIR)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(REL_DIR)%.o : $(SRC_DIR)ir/%.cpp
	$(REL_MKDIR)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(REL_DIR)%.o : $(SRC_DIR)misc/%.cpp
	$(REL_MKDIR)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(REL_DIR)%.o : $(SRC_DIR)parsers/owl2/%.cpp
	$(REL_MKDIR)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(REL_DIR)%.o : $(SRC_DIR)parsers/owl2/%.c
	$(REL_MKDIR)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(REL_DIR)%.o : $(SRC_DIR)%.cpp
	$(REL_MKDIR)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

raccoon_dbg: $(DBG_OBJ)
	$(CXX) $(DBG_CXX_FLAGS) -o $@ $(DBG_OBJ)

$(DBG_DIR)%.o : $(SRC_DIR)back/%.cpp
	$(DBG_MKDIR)
	$(CXX) $(DBG_CXX_FLAGS) -c -o $@ $<

$(DBG_DIR)%.o : $(SRC_DIR)ir/%.cpp
	$(DBG_MKDIR)
	$(CXX) $(DBG_CXX_FLAGS) -c -o $@ $<

$(DBG_DIR)%.o : $(SRC_DIR)misc/%.cpp
	$(DBG_MKDIR)
	$(CXX) $(DBG_CXX_FLAGS) -c -o $@ $<

$(DBG_DIR)%.o : $(SRC_DIR)parsers/owl2/%.cpp
	$(DBG_MKDIR)
	$(CXX) $(DBG_CXX_FLAGS) -c -o $@ $<

$(DBG_DIR)%.o : $(SRC_DIR)parsers/owl2/%.c
	$(DBG_MKDIR)
	$(CC) $(DBG_CC_FLAGS) -c -o $@ $<

$(DBG_DIR)%.o : $(SRC_DIR)%.cpp
	$(DBG_MKDIR)
	$(CXX) $(DBG_CXX_FLAGS) -c -o $@ $<

clean:
	rm -rf build
	rm -rf raccoon
	rm -rf raccoon_dbg