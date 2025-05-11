EXE		= particles
CPP		= g++
SFML_INC = -I/usr/include/SFML
SFML_LIB = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS	= -O3 -Wall $(SFML_INC)
LIBS	= $(SFML_LIB)

ALL = $(EXE)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	-$(RM) *.o $(EXE)

all: clean $(EXE)