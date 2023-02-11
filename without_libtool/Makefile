# Makefile

# Tesing libraries without libtool (like the cave-men did)
# 'princ' is descendant of 'king'
# so the dependencies are the following:

# main     -> libprinc.a                 -> libking.a                  static linking
# main_so  -> libprinc.so                -> libking.so                 dynamic linking
# main_soa -> libprinc_so.a(libprinc.so) -> libking_so.a(libking.so)   AIX-specific dynamic

# notes:
# * make executes program 'c++' by default, you can change it to somethin else
#   (though I only tested with g++)
# * in this sample we don't allow undefined symbols (`-z defs`, `-bernotok`)
# * no version-numbers in this minimal sample
# * no export-files in this minimal sample (except for the "addition" later)
# * on AIX,
#   the content of an archive can be examined with command   `ar -X32_64 tv foobar.a`
#   the symbols of a shared object can be examined with      `dump -X32_64 -Tv foobar.so`
#   the dependencies of a shared object can be examined with `dump -X32_64 -H foobar.so`
# * on Linux,
#   the content of an archive can be examined with command   `ar tv foobar.a`
#   the symbols of a shared object can be examined with      `nm -D foobar.so`
#   the dependencies of a shared object can be examined with `readelf -d foobar.so`

# addition: creating *.so from *.a
# those will libprinc_a.so libking_a.so,
# they are supposed to be equivalent with libprinc.so and libdking.so
# mind you, -fPIC at compilation in still necessary to build a shared object
# on Linux, options --whole-archive, --no-whole-archive will do
# on AIX, we create export-files
# dependencies:
#   main_a_so -> libprinc_a.so -> libking_a.so

AR  := /usr/bin/ar
NM  := /usr/bin/nm
CXX := c++ # it is the default

ALL := main main_so main_a_so

PLATFORM := $(shell uname)
ifeq  ($(PLATFORM),AIX)
    PLTC    := -maix64
    PLTL    := -maix64 -Wl,-brtl -Wl,-bernotok
    PLTL    += -Wl,-blibpath:/usr/lib:${PWD}:$(shell dirname $$(gcc -pthread -maix64 -print-file-name=libgcc_s.a))
    ARFLAGS := -X64

    ALL     += main_soa
else
    PLTC    := -m64
    PLTL    := -m64 -Wl,-z,defs 
    PLTL    += -Wl,-rpath,${PWD} -Wl,-rpath,$(shell realpath $$(dirname $$(gcc -pthread -m64 -print-file-name=libgcc_s.so)))
    ARFLAGS :=

    LD_WHON := -Wl,--whole-archive
    LD_WHOFF:= -Wl,--no-whole-archive
endif

all: ${ALL}

clean:
	rm -rf ${ALL} *.o *.a *.so 2>/dev/null || true

CXXFLAGS := -pthread -g ${PLTC} -Wall -W -fPIC
LDFLAGS  := -pthread -g ${PLTL}

king.o princ.o main.o: king.h
princ.o main.o: princ.h

%.o:	%.cc
	${CXX} -o $@ ${CXXFLAGS} ${CPPFLAGS} -c $<

libking.a: king.o
	${AR} ${ARFLAGS} rcs $@ $^

libprinc.a: princ.o
	${AR} ${ARFLAGS} rcs $@ $^

libking.so: king.o
	${CXX} -shared -o $@ ${LDFLAGS} $^

libprinc.so: princ.o libking.so
	${CXX} -shared -o $@ ${LDFLAGS} $^

libking_so.a: libking.so
	${AR} ${ARFLAGS} rcs $@ $^

libprinc_so.a: libprinc.so
	${AR} ${ARFLAGS} rcs $@ $^

main: main.o libprinc.a libking.a
	${CXX} -o $@ ${LDFLAGS} $^

main_so: main.o libprinc.so libking.so
	 ${CXX} -o $@ ${LDFLAGS} $^

main_soa: main.o libprinc_so.a libking_so.a
	${CXX} -o $@ ${LDFLAGS} $^

ifeq  ($(PLATFORM),AIX)

%.exp: %.a
	${NM} -X32_64 -Ppg -- "$*.a" |\
	awk '{ if ((($$2 == "T") || ($$2 == "D") || ($$2 == "B")) && (substr($$1,1,1) != ".")) \
	     { print $$1 } }' |\
	sort -u >$*.exp

libking_a.so: libking.a libking.exp
	${CXX} -shared -o $@ ${LDFLAGS} -Wl,-bE:libking.exp libking.a

libprinc_a.so: libprinc.a libking_a.so libprinc.exp
	${CXX} -shared -o $@ ${LDFLAGS} libprinc.a -Wl,-bE:libprinc.exp libking_a.so

else

libking_a.so: libking.a
	${CXX} -shared -o $@ ${LDFLAGS} ${LD_WHON} libking.a ${LD_WHOFF}

libprinc_a.so: libprinc.a libking_a.so
	${CXX} -shared -o $@ ${LDFLAGS} ${LD_WHON} libprinc.a ${LD_WHOFF} libking_a.so

endif

main_a_so: main.o libprinc_a.so libking_a.so
	${CXX} -o $@ ${LDFLAGS} $^
