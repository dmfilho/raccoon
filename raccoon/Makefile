CXX = g++
CC = gcc

CXX_FLAGS = -m64 -std=c++11 -O3
CC_FLAGS = -m64 -O3

DBG_CXX_FLAGS = -m64 -std=c++11 -O0 -g -D _DEBUG
DBG_CC_FLAGS = -m64 -O0 -g -D _DEBUG

CXX_FLAGS32 = -m32 -std=c++11 -O3
CC_FLAGS32 = -m32 -O3

DBG_CXX_FLAGS32 = -m32 -std=c++11 -O0 -g -D _DEBUG
DBG_CC_FLAGS32 = -m32 -O0 -g -D _DEBUG

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
REL_DIR32 = build/release32/
DBG_DIR32 = build/debug32/
SRC_DIR = src/

REL_OBJ = $(addprefix $(REL_DIR),$(OBJECTS))
DBG_OBJ = $(addprefix $(DBG_DIR),$(OBJECTS))

REL_OBJ32 = $(addprefix $(REL_DIR32),$(OBJECTS))
DBG_OBJ32 = $(addprefix $(DBG_DIR32),$(OBJECTS))

REL_MKDIR = @mkdir -p $(REL_DIR)
DBG_MKDIR = @mkdir -p $(DBG_DIR)

REL_MKDIR32 = @mkdir -p $(REL_DIR32)
DBG_MKDIR32 = @mkdir -p $(DBG_DIR32)

all: amd64 i386

amd64: bin/raccoon bin/raccoon_dbg

i386: bin/raccoon32 bin/raccoon_dbg32

# LINUX 64-bits
bin/raccoon: bin $(REL_OBJ)
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

bin/raccoon_dbg: bin $(DBG_OBJ)
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

# LINUX 32-bits
bin/raccoon32: bin $(REL_OBJ32)
	$(CXX) $(CXX_FLAGS32) -o $@ $(REL_OBJ32)

$(REL_DIR32)%.o : $(SRC_DIR)back/%.cpp
	$(REL_MKDIR32)
	$(CXX) $(CXX_FLAGS32) -c -o $@ $<

$(REL_DIR32)%.o : $(SRC_DIR)ir/%.cpp
	$(REL_MKDIR32)
	$(CXX) $(CXX_FLAGS32) -c -o $@ $<

$(REL_DIR32)%.o : $(SRC_DIR)misc/%.cpp
	$(REL_MKDI32R)
	$(CXX) $(CXX_FLAGS32) -c -o $@ $<

$(REL_DIR32)%.o : $(SRC_DIR)parsers/owl2/%.cpp
	$(REL_MKDIR32)
	$(CXX) $(CXX_FLAGS32) -c -o $@ $<

$(REL_DIR32)%.o : $(SRC_DIR)parsers/owl2/%.c
	$(REL_MKDIR32)
	$(CC) $(CC_FLAGS32) -c -o $@ $<

$(REL_DIR32)%.o : $(SRC_DIR)%.cpp
	$(REL_MKDIR32)
	$(CXX) $(CXX_FLAGS32) -c -o $@ $<

bin/raccoon_dbg32: bin $(DBG_OBJ32)
	$(CXX) $(DBG_CXX_FLAGS32) -o $@ $(DBG_OBJ32)

$(DBG_DIR32)%.o : $(SRC_DIR)back/%.cpp
	$(DBG_MKDIR32)
	$(CXX) $(DBG_CXX_FLAGS32) -c -o $@ $<

$(DBG_DIR32)%.o : $(SRC_DIR)ir/%.cpp
	$(DBG_MKDIR32)
	$(CXX) $(DBG_CXX_FLAGS32) -c -o $@ $<

$(DBG_DIR32)%.o : $(SRC_DIR)misc/%.cpp
	$(DBG_MKDIR32)
	$(CXX) $(DBG_CXX_FLAGS32) -c -o $@ $<

$(DBG_DIR32)%.o : $(SRC_DIR)parsers/owl2/%.cpp
	$(DBG_MKDIR32)
	$(CXX) $(DBG_CXX_FLAGS32) -c -o $@ $<

$(DBG_DIR32)%.o : $(SRC_DIR)parsers/owl2/%.c
	$(DBG_MKDIR32)
	$(CC) $(DBG_CC_FLAGS32) -c -o $@ $<

$(DBG_DIR32)%.o : $(SRC_DIR)%.cpp
	$(DBG_MKDIR32)
	$(CXX) $(DBG_CXX_FLAGS32) -c -o $@ $<

bin:
	mkdir -p bin

clean:
	rm -rf build
	rm -rf bin
