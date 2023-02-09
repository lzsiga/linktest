# Makefile

# Tesing libraries without libtool (like the cave-men did)
# 'princ' is descendant of 'king'
# so the dependencies are the following:

# main     -> libprinc.a                 -> libking.a                  static linking
# main_so  -> libprinc.so                -> libking.so                 dynamic linking
# main_soa -> libprinc_so.a(libprinc.so) -> libking_so.a(libking.so)   AIX-specific dynamic

# note: no version-numbers in this minimal sample

ALL := main main_so

PLATFORM := $(shell uname)
ifeq  ($(PLATFORM),AIX)
    PLTC    := -maix64
    PLTL    := -maix64 -Wl,-brtl -Wl,-blibpath:/usr/lib:${PWD}:$(shell dirname $$(gcc -pthread -maix64 -print-file-name=libgcc_s.a))
    ARFLAGS := -X64

    ALL     += main_soa
else
    PLTC := -m64
    PLTL := -m64 -Wl,-rpath,${PWD} -Wl,-rpath,$(shell realpath $$(dirname $$(gcc -pthread -m64 -print-file-name=libgcc_s.so)))
    ARFLAGS :=
endif

all: ${ALL}

clean:
	rm -rf ${ALL} *.o *.a *.so 2>/dev/null || true

CXXFLAGS := -pthread -g ${PLTC} -Wall -W -fPIC
LDFLAGS  := -pthread -g ${PLTL}

king.o: king.cc king.h
	${CXX} -o $@ ${CXXFLAGS} ${CPPFLAGS} -c $(filter %.cc,$^})

princ.o: princ.cc princ.h king.h
	${CXX} -o $@ ${CXXFLAGS} ${CPPFLAGS} -c $(filter %.cc,$^})

libking.a: king.o
	ar ${ARFLAGS} rcs $@ $^

libprinc.a: princ.o
	ar ${ARFLAGS} rcs $@ $^

libking.so: king.o
	${CXX} -shared -o $@ ${LDFLAGS} $^

libprinc.so: princ.o libking.so
	${CXX} -shared -o $@ ${LDFLAGS} $^

libking_so.a: libking.so
	ar ${ARFLAGS} rcs $@ $^

libprinc_so.a: libprinc.so
	ar ${ARFLAGS} rcs $@ $^

main: main.o libprinc.a libking.a
	${CXX} -o $@ ${LDFLAGS} $^

main_so: main.o libprinc.so libking.so
	 ${CXX} -o $@ ${LDFLAGS} $^

main_soa: main.o libprinc_so.a libking_so.a
	${CXX} -o $@ ${LDFLAGS} $^
