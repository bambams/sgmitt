BINDIR = bin
COPY = cp
CXX = g++
CXXFLAGS = -g3 -Iinclude -Ideps/libal5poly/include -Wall `pkg-config --cflags allegro-5 allegro_image-5 allegro_primitives-5`
DEPSDIR = deps
INCDIR = include
LIBS = -Ldeps/libal5poly/lib/ -lal5poly `pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5`
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
	cd $< && ${MAKE} clean
	cd $< && ${MAKE}

clean:
	${REMOVE} ${BINDIR} ${OBJDIR}

deepclean:
	-cd ${DEPSDIR}/libal5poly && ${MAKE} clean
	${MAKE} clean

dirs: ${BINDIR} ${OBJDIR}

game: libal5poly ${GAME}

libal5poly: ${DEPSDIR}/libal5poly/lib/libal5poly.so

run: game
	LD_LIBRARY_PATH=deps/libal5poly/lib ${GAME}

veryclean: clean
	rm -fR ${DEPSDIR}/libal5poly

${DEPSDIR}/libal5poly:
	git clone git://github.com/bamccaig/libal5poly.git deps/libal5poly
	cd $@ && git remote set-url --push origin git@github.com:bamccaig/libal5poly.git

${DEPSDIR}/libal5poly/lib/libal5poly.so: ${DEPSDIR}/libal5poly
	cd $< && ${MAKE}

${BINDIR}:
	${MKDIR} $@

${OBJDIR}:
	${MKDIR} $@

${GAME}: ${OBJECTS} ${BINDIR}
	${CXX} -o $@ ${OBJECTS} ${LIBS}

${OBJDIR}/H4xDummy.o: ${SRCDIR}/H4xDummy.cpp ${INCDIR}/H4xDummy.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/JumpHandler.o: ${SRCDIR}/JumpHandler.cpp ${INCDIR}/JumpHandler.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/RunHandler.o: ${SRCDIR}/RunHandler.cpp ${INCDIR}/RunHandler.hpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/main.o: ${SRCDIR}/main.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<
