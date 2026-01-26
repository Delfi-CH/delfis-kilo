dk: src/kilo.c src/delfi.c
	$(CC) src/kilo.c src/delfi.c -o dk -Wall -Wextra -pedantic -std=c99

PREFIX ?= /usr
BINDIR  = $(PREFIX)/bin

.PHONY: install

install: dk
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 dk $(DESTDIR)$(BINDIR)/dk

preprocess: src/kilo.c src/delfi.c
	$(CC) -E src/kilo.c -o src/kilo.i -Wall -Wextra -pedantic -std=c99
	$(CC) -E src/delfi.c -o src/delfi.i -Wall -Wextra -pedantic -std=c99


2asm: src/kilo.c src/delfi.c
	$(CC) -S src/kilo.c -o src/kilo.s -Wall -Wextra -pedantic -std=c99
	$(CC) -S src/delfi.c -o src/delfi.s -Wall -Wextra -pedantic -std=c99

.PHONY: clean

clean: dk
	rm -f dk
	rm -f src/delfi.i
	rm -f src/delfi.s
	rm -f src/kilo.i
	rm -f src/kilo.s