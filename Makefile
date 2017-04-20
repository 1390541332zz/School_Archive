ARCHIVE = ECE1574
SUBDIRS = $(subst ./, , $(sort $(dir $(wildcard ./Lab*/) $(wildcard ./Project*/))))
JOBCOUNT := 9

define clean =
	$(RM) ./$(ARCHIVE).tar ./$(ARCHIVE).zip
	for dir in $(SUBDIRS); do \
		$(MAKE) -j$(JOBCOUNT) clean -C $$dir; \
	done
endef

all: compile

compile:
	for dir in $(SUBDIRS); do \
		$(MAKE) -j$(JOBCOUNT) -C $$dir; \
	done

clean:
	$(clean)

tar:
	$(clean)
	tar -cvf ./$(ARCHIVE).tar ./$(SUBDIRS)

zip:
	$(clean)
	zip ./$(ARCHIVE).zip ./$(SUBDIRS)
