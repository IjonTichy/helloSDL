CC = g++
LD = g++

CFLAGS =
LFLAGS =
LIBS   = -lSDL

OPT_LEVEL = 2
DBG_LEVEL = 3

SRCDIR   = src
BUILDDIR = build

CFILES = $(wildcard ${SRCDIR}/*.c)
HFILES = $(wildcard ${SRCDIR}/*.h)
OFILES = $(patsubst ${SRCDIR}/%.c, ${BUILDDIR}/%.o, ${CFILES})

EXE_NAME = helloSDL

.PHONY: default

default: all

all: ${OFILES}
	@[ ${OFILES} ] || (echo "ERROR: Nothing to link" 1>&2; exit 1)
	${LD} ${LFLAGS} ${OFILES} ${LIBS} -o ${EXE_NAME} 

clean:
	@rm -f ${BUILDDIR}/*.o

${BUILDDIR}/%.o: ${SRCDIR}/%.c ${HFILES}
	@mkdir -p ${BUILDDIR}
	${CC} ${CFLAGS} -O${OPT_LEVEL} -g${DBG_LEVEL} -c $< -o $@
