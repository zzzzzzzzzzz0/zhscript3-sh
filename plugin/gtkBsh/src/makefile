d = debug
f = -O0 -ggdb

name = src
pkname = gtksourceview-4
ifeq ($(shell pkg-config --validate $(pkname) 2> /dev/null ; echo $$?),1)
	pkname = gtksourceview-3.0
endif
$(info $(pkname))
ddir = ../../../target/$d
dodir = $(ddir)/obj/plugin/gtkBsh/$(name)
dtdir = $(ddir)/plugin/gtkBsh
target = $(dtdir)/$(name).so
gxx = g++
std = c++17
cflags = -std=$(std) $f -fPIC -c
ifeq ($d,debug)
	cflags += -D_$d_
endif
lflags = `pkg-config --libs $(pkname)`
ifeq ($(std),c++17)
	cflags += -D_std11_
	lflags += -lstdc++fs
endif

all: dir $(target)
$(dodir)/main.o: src/main2.cpp ../../../pub/fs.h ../../pub.h ../../../pub/tag.h ../../../pub/type.h ../../../pub/widget.h
	$(gxx) -o $@ $(cflags) $< `pkg-config --cflags $(pkname)`
$(dodir)/tag.o: ../../../pub/tag.cpp ../../../pub/tag.h ../../../pub/type.h
	$(gxx) -o $@ $(cflags) $< `pkg-config --cflags gtk+-3.0`
$(target): $(dodir)/main.o $(dodir)/tag.o
	$(gxx) -o $@ -shared $^ $(lflags)
dir:
	@mkdir -p $(dodir) $(dtdir)
clean:
	rm -f $(target) -r $(dodir)
