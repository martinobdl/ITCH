EXE = ITCH_50_parser
OBJECTS = ITCH_50_parser.o
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

ITCH_50_parser.o:

.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
