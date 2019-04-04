SUBDIRS += c++ gtests parser

all:
	+$(MAKE) -C c++
	+$(MAKE) -C gtests
	+$(MAKE) -C parser

.PHONY: clean all

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
