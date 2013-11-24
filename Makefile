include ../Makefiles/git1.mk

all:
	@echo "There is nothing to build in this directory."

include ../Makefiles/git2.mk

vi:
	vi $(documentation)

notes:
	(cd ../notes && make vi)

quotes:
	(cd ../notes && make quotes)

bibtex:
	(cd ../bibtex && make vi)

spell:
	aspell --lang=en_GB check $(documentation)

clean:
	rm -f $(documentation).bak

