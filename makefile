OBJ = input.o plugboard.o rotor.o reflector.o helper.o main.o
EXE = enigma
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

input.o : input.h helper.h

plugboard.o : plugboard.h helper.h rotor.h input.h

rotor.o : rotor.h helper.h

reflector.o : reflector.h helper.h

helper.o : helper.h errors.h

main.o : rotor.h reflector.h plugboard.h input.h errors.h

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
