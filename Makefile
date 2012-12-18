BINDIR = bin
COPY = cp
CXX = mingw32-g++
CXXFLAGS = -g3 -Iinclude -Ideps/libal5poly/include -Wall
DEPSDIR = deps
INCDIR = include
LIBS = -Ldeps/libal5poly/bin/ -llibal5poly -lallegro-5.0.7-monolith-md
MKDIR = mkdir -p
OBJDIR = obj
PREFIX =
REMOVE = rm -fR
SRCDIR = src

GAME = ${BINDIR}/game.exe

.PHONY: all clean game libal5poly run

all: game

clean:
	${REMOVE} ${BINDIR} ${OBJDIR}

dirs: ${BINDIR} ${OBJDIR}

game: libal5poly ${GAME}

libal5poly: ${DEPSDIR}/libal5poly/bin/libal5poly.1.dll

run: game
	${GAME}

${DEPSDIR}/libal5poly:
	git clone git://github.com/bamccaig/libal5poly.git deps/libal5poly

${DEPSDIR}/libal5poly/bin/libal5poly.1.dll: ${DEPSDIR}/libal5poly
	cd $< && ${MAKE} -f Makefile.mingw

${BINDIR}:
	${MKDIR} $@

${BINDIR}/libal5poly.1.dll:
	ln -s ../deps/libal5poly/bin/libal5poly.1.dll $@

${OBJDIR}:
	${MKDIR} $@

${GAME}: ${OBJDIR}/main.o ${BINDIR} ${BINDIR}/libal5poly.1.dll
	${CXX} -o $@ $< ${LIBS}

${OBJDIR}/main.o: ${SRCDIR}/main.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<
