dk: kilo.c delfi.c
	$(CC) kilo.c delfi.c -o dk -Wall -Wextra -pedantic -std=c99

PREFIX ?= /usr
BINDIR  = $(PREFIX)/bin

.PHONY: install

install: dk
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 dk $(DESTDIR)$(BINDIR)/dk
