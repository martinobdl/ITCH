EXE = executeTests
OBJECTS = Order_test.o ../c++/utility.o
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
	-Wundef \
	-g \
	-pthread
LDFLAGS += -lgtest_main -lgtest -lpthread -o

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $@

Order_test.o: ../c++/Order.hpp ../c++/Message.hpp ../c++/utility.hpp
../c++/utility.o: ../c++/utility.hpp

.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
