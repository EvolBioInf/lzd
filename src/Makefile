CC=gcc
CFLAGS= -O3 -Wall -Wshadow -pedantic -std=gnu99 -g
# The source files, object files, libraries and executable name.
SRCFILES= lzd.c interface.c eprintf.c sequenceData.c stringUtil.c complexity.c factor.c esa.c stack.c
OBJFILES= lzd.o interface.o eprintf.o sequenceData.o stringUtil.o complexity.o factor.o esa.o stack.o
LIBS= -lm -ldivsufsort
EXECFILE=lzd
DIRECTORY=Lzd
VERSION=0.6
# The make rule for the executable
.PHONY : all
all : $(EXECFILE)
$(EXECFILE) : $(OBJFILES)

	$(CC) $(CFLAGS) -o $(EXECFILE) $(OBJFILES) $(LIBS)
$(EXECFILE).o: interface.h eprintf.h
interface.o: interface.h
eprintf.o: eprintf.h

doc:
	cd ../Doc; make clean; make pdf; cd ../$(DIRECTORY)_$(VERSION)

# Other Standard make rules
lint : 
	lint $(SRCFILES) | more
clean:
	rm -f *.o *~
tarfile:
	cd ../Doc; make clean; make pdf; cd ../$(DIRECTORY)_$(VERSION)
	mkdir $(DIRECTORY)_$(VERSION)
	cp -rf $(SRCFILES) *.h  README COPYING Makefile ../Doc/lzdDoc.pdf $(DIRECTORY)_$(VERSION)
	mkdir $(DIRECTORY)_$(VERSION)/Data
	cp ../Data/algPaper.fasta  ../Data/hsPaper1.fasta  ../Data/hsPaper2.fasta  ../Data/test.fasta $(DIRECTORY)_$(VERSION)/Data
	tar cvzfh $(EXECFILE)_$(VERSION).tgz $(DIRECTORY)_$(VERSION)
	mv $(EXECFILE)_$(VERSION).tgz ../
	/bin/rm -r $(DIRECTORY)_$(VERSION)

