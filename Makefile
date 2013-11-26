documentation = README.md

all:
	@echo "There is nothing to build in this directory."

vi:
	vi $(documentation)

spell:
	aspell --lang=en_GB check $(documentation)

clean:
	rm -f $(documentation).bak

include common.mk

