CXX = g++
LIBS = -lm
CFLAGS = -g -O0 -Wall -Werror -pedantic -ansi
LDFLAGS =
CPPFLAGS = -I../bzflag/include

FILES = \
	BuildZone.cxx \
	FloorZone.cxx \
	Generator.cxx \
	GridGenerator.cxx \
	GridMap.cxx \
	Material.cxx \
	Mesh.cxx \
	bzwgen.cxx

OBJECTS = ${FILES:.cxx=.o}

.PHONY: all clean blather
.SUFFIXES: .cxx .o

all: blather bzwgen

.cxx.o: common.h
	${CXX} ${CFLAGS} ${CPPFLAGS} -c $<

blather:
	@echo ""
	@echo "Using the following settings:"
	@echo "  CXX=\"$(CXX)\""
	@echo "  LIBS=\"$(LIBS)\""
	@echo "  CFLAGS=\"$(CFLAGS)\""
	@echo "  LDFLAGS=\"$(LDFLAGS)\""
	@echo "  CPPFLAGS=\"$(CPPFLAGS)\""
	@echo ""

clean:
	@echo "Cleaning up..."
	rm -f bzwgen ${OBJECTS}
	@echo "Done."

bzwgen: ${OBJECTS}
	@echo ""
	@echo "Building bzwgen..."
	@echo ""
	${CXX} -o $@ ${OBJECTS} ${CFLAGS} ${LDFLAGS} ${LIBS}
	@echo "Done!"

