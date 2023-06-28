LIB := libidx.a
PREFIX := /usr/local


DEPS = $(wildcard build/*.d)

.PHONY: all install uninstall clean \
	lib install-lib uninstall-lib clean-lib \
	docs install-docs uninstall-docs clean-docs



all: lib docs

CC := gcc
CFLAGS := -Wall -Werror -O2 -MP -MD -Iinclude
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,build/%.o,$(SRCS))

lib: build build/$(LIB)
build:
	mkdir build
build/$(LIB): $(OBJS)
	ar rcs $@ $(OBJS)
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

docs: docs/man
docs/man*:
	cmangen


install: install-lib install-docs

HEADERS := $(wildcard include/*.h)

install-lib: $(PREFIX)/lib/$(lib)
$(PREFIX)/lib/$(LIB): build/$(LIB) install-headers
	install -m 644 $< $@
$(PREFIX)/include/%.h: include/%.h
	install -m 644 $< $@

MANSECS := $(wildcard docs/man/*/)
MANFILES := $(wildcard docs/man/*/*)
PMANSECS := $(patsubst docs/%,$(PREFIX)/%,$(MANSECS))
PMANFILES := $(patsubst docs/%,$(PREFIX)/%,$(MANFILES))

install-docs: $(PMANSECS) $(PMANFILES)
$(PREFIX)/man/%/: docs/man/%/
	install -d $@
$(PREFIX)/man/%: docs/man/%
	install -m 644 $< $@


uninstall: uninstall-lib uninstall-docs

uninstall-lib:
	rm -f $(PREFIX)/lib/$(LIB) $(PREFIX)/$(HEADERS)

uninstall-docs:
	rm -f $(PMANFILES)


clean: clean-lib clean-docs

clean-lib:
	rm -rf build

clean-docs:
	rm -rf docs
