EXE = BookConstructor
EXE_TEST = executeTests

SCR_DIR = src
TEST_DIR = gtests
BIN_DIR = bin
INC_DIR = include

CXXFLAGS += -Wall -std=c++11 \
   -Werror \
   -Wextra \
   -Wconversion \
   -Wno-deprecated \
   -Winit-self \
   -Wsign-conversion \
   -Wredundant-decls \
   -Wvla -Wshadow -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual \
   -Winit-self \
   -Wpointer-arith \
   -Wcast-qual \
   -Wcast-align \
   -Wdouble-promotion \
   -Wold-style-cast -Wno-error=old-style-cast \
   -Wsign-promo \
   -Wswitch-enum \
   -Wswitch-default \
   -Wundef

LDFLAGS += 	-lgtest_main \
			-lgtest \
			-lpthread \
			-pthread \
			-lgmock

SOURCES=$(wildcard $(SCR_DIR)/*.cpp)
OBJECTS=$(SOURCES:$(SCR_DIR)/%.cpp=$(BIN_DIR)/%.o)

SOURCES_T=$(wildcard $(TEST_DIR)/*.cpp)
OBJECTS_T=$(SOURCES_T:$(TEST_DIR)/%.cpp=$(BIN_DIR)/%.o) $(filter-out $(BIN_DIR)/main.o, $(OBJECTS))

# --------------------------------------------------------------

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# --------------------------------------------------------------

test: $(EXE_TEST)

$(EXE_TEST): $(OBJECTS_T)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# --------------------------------------------------------------

$(BIN_DIR)/%.o : $(SCR_DIR)/%.cpp
	$(CXX) -MD $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR)/%.o : $(TEST_DIR)/%.cpp
	$(CXX) -MD $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# --------------------------------------------------------------

clean:
	$(RM) $(BIN_DIR)/*.o

distclean: clean
	$(RM) $(EXE)

print-%  : ; @echo $* = $($*)
