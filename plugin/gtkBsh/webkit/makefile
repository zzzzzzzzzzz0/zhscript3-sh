d = debug
f = -O0 -ggdb

name = webkit
pkname = webkit2gtk-4.0
ddir = ../../../target/$d
dodir = $(ddir)/obj/plugin/gtkBsh/$(name)
dtdir = $(ddir)/plugin/gtkBsh
target = $(dtdir)/$(name).so
gxx = g++
cflags = $f -fPIC -c
ifeq ($d,debug)
	cflags += -D_$d_
endif

all: dir $(target)
$(dodir)/main.o: src/main4.cpp ../../pub.h ../../../pub/tag.h ../../../pub/type.h ../../../pub/widget.h
	$(gxx) -o $@ $(cflags) $< `pkg-config --cflags $(pkname)`
$(dodir)/tag.o: ../../../pub/tag.cpp ../../../pub/tag.h ../../../pub/type.h
	$(gxx) -o $@ $(cflags) $< `pkg-config --cflags gtk+-3.0`
$(target): $(dodir)/main.o $(dodir)/tag.o
	$(gxx) -o $@ -shared $^ `pkg-config --libs $(pkname)`
dir:
	@mkdir -p $(dodir) $(dtdir)
clean:
	rm -f $(target) -r $(dodir)
