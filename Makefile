CFLAGS+=-Wall

all: demo demo-builtin snappy-shm-open.so
.PHONY: all

demo: LDLIBS+=-lrt
demo: demo.c
	$(LINK.o) -o $@ $^ $(LDLIBS)

demo-builtin: LDLIBS+=-lrt
demo-builtin: demo.c snappy.c
	$(LINK.o) -o $@ $^ $(LDLIBS)

snappy-shm-open.so: snappy.c
	$(LINK.o) -fPIC -shared $^ -o $@ $(LDLIBS)

clean:
	rm -f demo demo-builtin snappy-shm-open.so
.PHONY: clean

install: demo
	install -d $(DESTDIR)/usr/bin
	install -d $(DESTDIR)/usr/lib
	install demo $(DESTDIR)/usr/bin/ -m 775
	install demo-builtin $(DESTDIR)/usr/bin/ -m 775
	install demo-wrapper $(DESTDIR)/usr/bin/ -m 775
	install snappy-shm-open.so $(DESTDIR)/usr/lib/ -m 775
.PHONY: install
