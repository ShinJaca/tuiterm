CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall -Wno-unknown-pragmas
NCURSES=-lncurses -ltinfo
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(NCURSES) -pipe
LD=g++
LDFLAGS=$(NCURSES)
SRCDIR=src
DISTDIR=dist
TARGET=$(DISTDIR)/jvim
OBJS= main.o jvim.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	@rm -rf *.o

main.o: 
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/main.cpp -o main.o

jvim.o: 
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/jvim.cpp  -o jvim.o