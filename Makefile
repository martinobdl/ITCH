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
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR)/%.o : $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# $(EXE_TEST): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@


# $(BIN_DIR)/main.o: $(INC_DIR)/ITCH/BookConstructor.hpp $(INC_DIR)/ITCH/OrderBook.hpp $(INC_DIR)/ITCH/OrderPool.hpp $(INC_DIR)/ITCH/Order.hpp $(INC_DIR)/ITCH/utility.hpp $(INC_DIR)/ITCH/Message.hpp $(INC_DIR)/ITCH/Writer.hpp $(INC_DIR)/ITCH/Reader.hpp
# $(BIN_DIR)/BookConstructor.o: $(INC_DIR)/ITCH/OrderBook.hpp $(INC_DIR)/ITCH/OrderPool.hpp $(INC_DIR)/ITCH/Order.hpp $(INC_DIR)/ITCH/utility.hpp $(INC_DIR)/ITCH/Message.hpp $(INC_DIR)/ITCH/Writer.hpp $(INC_DIR)/ITCH/Reader.hpp
# $(BIN_DIR)/OrderBook.o: $(INC_DIR)/ITCH/OrderBook.hpp $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/OrderPool.o: $(INC_DIR)/ITCH/OrderPool.hpp $(INC_DIR)/ITCH/Order.hpp $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/Order.o: $(INC_DIR)/ITCH/Order.hpp $(INC_DIR)/ITCH/Message.hpp $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/Message.o: $(INC_DIR)/ITCH/Message.hpp $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/utility.o: $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/Reader.o: $(INC_DIR)/ITCH/Writer.hpp $(INC_DIR)/ITCH/Reader.hpp $(INC_DIR)/ITCH/Message.hpp $(INC_DIR)/ITCH/utility.hpp
# $(BIN_DIR)/Writer.o: $(INC_DIR)/ITCH/Writer.hpp


clean:
	$(RM) $(BIN_DIR)/*.o

distclean: clean
	$(RM) $(EXE)

print-%  : ; @echo $* = $($*)
