.PHONY: all
all: neocd0

.PHONY: clean
clean:
	$(RM) neocd0

README: morse.1
	mandoc $< | col -b > $@
