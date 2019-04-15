EXE = executeTests
OBJECTS = 	main_gtest.o \
			OrderPool_test.o \
			Message_test.o \
			Order_test.o \
			OrderBook_test.o \
			../c++/utility.o
			#Reader_test.o \

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

LDFLAGS += -lgtest_main \
			 -lgtest \
			 -lpthread \
			 -pthread \
			 -lgmock

all: $(EXE)
	+$(MAKE) -C ../c++

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

main_gtest.o: Order_test.o
Order_test.o: ../c++/Order.hpp ../c++/Message.hpp ../c++/utility.hpp
Message_test.o: ../c++/Message.hpp ../c++/utility.hpp
OrderPool_test.o: ../c++/Order.hpp ../c++/OrderPool.hpp ../c++/utility.hpp
OrderBook_test.o:  ../c++/OrderBook.hpp
#Reader_test.o: ../c++/Reader.hpp ../c++/Message.hpp ../c++/utility.hpp ../c++/Writer.hpp
../c++/utility.o: ../c++/utility.hpp

.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
