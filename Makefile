
#CFLAGS=-std=c++11


src = main.cpp db.cpp board.cpp creature.cpp sqlite3.c
obj = main.o db.o board.o creature.o sqlite3.o

CXXFLAGS = -std=c++11
LDFLAGS = -lpthread -ldl

myprog: $(obj)
	$(LINK.cc) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
