ARCHIVE = ECE1574
SUBDIRS = $(subst ./, , $(sort $(dir $(wildcard ./*/))))

define clean =
	$(RM) $(ARCHIVE).tar $(ARCHIVE).zip
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
endef

all: compile

compile:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	$(clean)

tar:
	$(clean)
	tar -cvf $(ARCHIVE).tar $(SUBDIRS)

zip:
	$(clean)
	zip $(ARCHIVE).zip $(SUBDIRS)
