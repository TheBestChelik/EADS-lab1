WFLAGS = -Wall -Wextra -Wpedantic
OBJDIR = obj

test_sequence.out: $(OBJDIR)/main.o $(OBJDIR)/Sequence.o
	g++ $(WFLAGS) -g $(OBJDIR)/main.o $(OBJDIR)/Sequence.o -o test_sequence.out

$(OBJDIR)/main.o: main.cpp Sequence.hpp
	g++ $(WFLAGS) -g -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/Sequence.o: Sequence.cpp Sequence.hpp
	g++ $(WFLAGS) -g -c Sequence.cpp -o $(OBJDIR)/Sequence.o

clean:
	rm -rf $(OBJDIR)/*.o test_sequence
