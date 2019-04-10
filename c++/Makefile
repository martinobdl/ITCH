EXE = BookConstructor
OBJECTS =   Order.o \
            Message.o \
            utility.o \
            main.o \
            BookConstructor.o \
            OrderBook.o \
            OrderPool.o \
            Reader.o \
            Writer.o
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

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: BookConstructor.hpp OrderBook.hpp OrderPool.hpp Order.hpp utility.hpp Message.hpp Writer.hpp Reader.hpp
BookConstructor.o: OrderBook.hpp OrderPool.hpp Order.hpp utility.hpp Message.hpp Writer.hpp Reader.hpp
OrderBook.o: OrderBook.hpp utility.hpp
OrderPool.o: OrderPool.hpp Order.hpp utility.hpp
Order.o: Order.hpp Message.hpp utility.hpp
Message.o: Message.hpp utility.hpp
utility.o: utility.hpp
Reader.o: Reader.hpp Message.hpp utility.hpp
Writer.o: Writer.hpp

.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
