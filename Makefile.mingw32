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

GAME = ${BINDIR}/sgmitt.exe
OBJECTS = ${OBJDIR}/H4xDummy.o \
		  ${OBJDIR}/JumpHandler.o \
		  ${OBJDIR}/RunHandler.o \
		  ${OBJDIR}/main.o

.PHONY: all build-deps clean deepclean game libal5poly run veryclean

all: game

build-deps: ${DEPSDIR}/libal5poly
	cd $< && ${MAKE} -f Makefile.mingw32 clean
	cd $< && ${MAKE} -f Makefile.mingw32

clean:
	${REMOVE} ${BINDIR} ${OBJDIR}

deepclean:
	-cd ${DEPSDIR}/libal5poly && ${MAKE} -f Makefile.mingw32 clean
	${MAKE} clean

dirs: ${BINDIR} ${OBJDIR}

game: libal5poly ${GAME}

libal5poly: ${DEPSDIR}/libal5poly/bin/libal5poly.1.dll

run: game
	${GAME}

veryclean: clean
	rm -fR ${DEPSDIR}/libal5poly

${DEPSDIR}/libal5poly:
	git clone git://github.com/bamccaig/libal5poly.git deps/libal5poly
	cd $@ && git remote set-url --push origin git@github.com:bamccaig/libal5poly.git

${DEPSDIR}/libal5poly/bin/libal5poly.1.dll: ${DEPSDIR}/libal5poly
	cd $< && ${MAKE} -f Makefile.mingw32

${BINDIR}:
	${MKDIR} $@

${BINDIR}/libal5poly.1.dll:
	ln -s ../deps/libal5poly/bin/libal5poly.1.dll $@

${OBJDIR}:
	${MKDIR} $@

${GAME}: ${OBJECTS} ${BINDIR} ${BINDIR}/libal5poly.1.dll
	${CXX} -o $@ ${OBJECTS} ${LIBS}

${OBJDIR}/H4xDummy.o: ${SRCDIR}/H4xDummy.cpp ${INCDIR}/H4xDummy.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/JumpHandler.o: ${SRCDIR}/JumpHandler.cpp ${INCDIR}/JumpHandler.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/RunHandler.o: ${SRCDIR}/RunHandler.cpp ${INCDIR}/RunHandler.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/main.o: ${SRCDIR}/main.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<
