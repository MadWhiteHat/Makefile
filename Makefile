all: clean static dynamic blob

static:
	@${MAKE} -f Makefile.in static

dynamic:
	@${MAKE} -f Makefile.in dynamic

blob:
	@${MAKE} -f Makefile.in blob

clean:
	@${MAKE} -f Makefile.in clean
