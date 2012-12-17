BINDIR = bin
COPY = cp
CXX = mingw32-g++
CXXFLAGS = -g3 -Iinclude -Ideps/libal5poly/include -Wall
INCDIR = include
LIBS = -Ldeps/libal5poly/bin/ -llibal5poly -lallegro-5.0.7-monolith-md
MKDIR = mkdir -p
OBJDIR = obj
PREFIX =
REMOVE = rm -fR
SRCDIR = src

GAME = ${BINDIR}/game.exe

.PHONY: all clean game run

all: game

clean:
	${REMOVE} ${BINDIR} ${OBJDIR}

dirs: ${BINDIR} ${OBJDIR}

game: ${GAME}

run: game
	${GAME}

${BINDIR}:
	${MKDIR} $@

${OBJDIR}:
	${MKDIR} $@

${GAME}: ${OBJDIR}/main.o ${BINDIR}
	${CXX} -o $@ $< ${LIBS}

${OBJDIR}/main.o: ${SRCDIR}/main.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<
