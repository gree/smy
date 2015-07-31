RUBY=ruby
SCRIPT=../../tool/state2cpp.rb

TARGETS := $(shell find . -name "*.yml" -type f -exec basename {} .yml \;)

SRCS=$(TARGETS:=.yml)
PDFS=$(TARGETS:=.pdf)
PNGS=$(TARGETS:=.png)
SVGS=$(TARGETS:=.svg)

all: $(PDFS) $(PNGS) $(SVGS)

clean:
	@rm $(PDFS) $(PNGS) $(SVGS)

.SUFFIXES: .yml .pdf .png .svg

.yml.pdf:
	$(RUBY) $(SCRIPT) $^
.yml.png:
	$(RUBY) $(SCRIPT) $^
.yml.svg:
	$(RUBY) $(SCRIPT) $^
