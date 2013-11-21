documentation = README.md

#
# Note: make requires that we set the value of a variable OUTSIDE any rules.
#

timestamp = `date +%Y%m%d.%H%M`

all:
	@echo "There is nothing to build in this directory."

vi:
	vi $(documentation)

notes:
	(cd ../notes && make vi)

quotes:
	(cd ../notes && make quotes)

bibtex:
	(cd ../bibtex && make vi)

commit:
	git add .
	git commit -am "commit from Makefile $(timestamp)"
	make sync

sync:
	git pull --rebase
	git push

readme:
	vi $(documentation)

spell:
	aspell --lang=en_GB check $(documentation)

clean:
	rm -f $(documentation).bak

