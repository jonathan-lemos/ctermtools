# Copyright (c) 2018 Jonathan Lemos
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

FILES=ctermtools
PREFIX=/usr
LIBRARY=libctermtools.so
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c89 -O2
OBJECTS=$(foreach file,$(FILES),$(file).o)
HEADERS=$(foreach file,$(FILES),$(file).h)

$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o $(LIBRARY)

test: test.o
	$(CC) $(CFLAGS) $(OBJECTS) test.o -o test -lctermtools

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $<

.PHONY: docs
docs:
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBRARY) test test.o
	rm -Rf docs

.PHONY: install
install: $(LIBRARY)
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp $(LIBRARY) $(DESTDIR)$(PREFIX)/lib/$(LIBRARY)
	cp $(foreach header,$(HEADERS),../$(header)) $(DESTDIR)$(PREFIX)/include

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/$(LIBRARY)
	rm -f $(foreach header,$(HEADERS),$(DESTDIR)$(PREFIX)/include/$(header))
