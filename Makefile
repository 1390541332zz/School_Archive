ARCHIVE = ECE1574
SUBDIRS = $(subst ./, , $(sort $(dir $(wildcard ./*/))))

all: compile

compile:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	$(RM) $(ARCHIVE).tar $(ARCHIVE).zip
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done

tar:
	clean
	tar -cvf $(ARCHIVE).tar $(SUBDIRS)

zip:
	clean
	zip $(ARCHIVE).zip $(SUBDIRS)
