CXX = g++
CXXFLAGS=
PREFIX?= /usr
BINDIR?= $(PREFIX)/bin

all: linfo

linfo: linfo.o
	$(CXX) $(CXXFLAGS) -O2 -o $@ linfo.o

linfo.o: linfo.cpp
	$(CXX) $(CXXFLAGS) -c linfo.cpp

install:
	install -Dm755 linfo $(DESTDIR)$(BINDIR)/linfo

uninstall:
	rm -f /usr/bin/linfo

clean:
	rm -f linfo linfo.o