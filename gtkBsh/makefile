d = debug
f = -O0 -ggdb

ddir = ../target/$d
dodir = $(ddir)/obj/gtkBsh
target = $(ddir)/gtkBsh
gxx = g++
std = c++20
cflags = -std=$(std) $f `pkg-config --cflags gtk+-3.0` -c
ifeq ($d,debug)
	cflags += -D_$d_
endif
ifeq ($(std),c++20)
	cflags += -D_std20_
endif
lflags = `pkg-config --libs gtk+-3.0` -ldl
ifeq ($(std),c++17)
	cflags += -D_std11_
	lflags += -lstdc++fs
endif

all: dir $(target)
$(dodir)/main.o: src/main.cpp src/fanqiechaodan.h src/window.h src/main_plugin.h ../plugin/pub.h ../pub/tag.h ../pub/type.h ../pub/widget.h src/pub.h ../pub/l4.h ../pub/fs.h src/label_box.h src/views.h src/view.h src/pub2.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/fanqiechaodan.o: src/fanqiechaodan.cpp src/fanqiechaodan.h src/window.h src/main_plugin.h ../plugin/pub.h ../pub/tag.h ../pub/type.h ../pub/widget.h src/pub.h ../pub/l4.h ../pub/fs.h src/label_box.h src/views.h src/view.h src/pub2.h src/slave.cpp src/slave.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/pub.o: src/pub.cpp src/pub.h ../pub/tag.h ../pub/type.h ../pub/l4.h ../pub/fs.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/pub2.o: src/pub2.cpp src/pub2.h src/main_plugin.h ../plugin/pub.h ../pub/tag.h ../pub/type.h ../pub/widget.h src/window.h src/pub.h ../pub/l4.h ../pub/fs.h src/label_box.h src/views.h src/view.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/slave.o: src/slave.cpp src/slave.h ../plugin/pub.h ../pub/tag.h ../pub/type.h ../pub/widget.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/window.o: src/window.cpp src/pub2.h src/main_plugin.h ../plugin/pub.h ../pub/tag.h ../pub/type.h ../pub/widget.h src/window.h src/pub.h ../pub/l4.h ../pub/fs.h src/label_box.h src/views.h src/view.h src/xianchang.h src/screenshot.h src/event.h
	$(gxx) -o $@ $(cflags) $<
$(dodir)/tag.o: ../pub/tag.cpp ../pub/tag.h ../pub/type.h
	$(gxx) -o $@ $(cflags) $<
$(target): $(dodir)/main.o $(dodir)/fanqiechaodan.o $(dodir)/pub.o $(dodir)/pub2.o $(dodir)/slave.o $(dodir)/window.o $(dodir)/tag.o
	$(gxx) -o $@ $^ $(lflags)
dir:
	@mkdir -p $(dodir)
clean:
	rm -f $(target) -r $(dodir)
