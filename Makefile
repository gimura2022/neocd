.PHONY: all
all: neocd0

.PHONY: clean
clean:
	$(RM) neocd0

README: neocd.1
	mandoc $< | col -b > $@
