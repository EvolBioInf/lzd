all: lzdDoc.pdf
lzdDoc.pdf: lzdDoc.tex tab.tex ref.bib
	pdflatex lzdDoc
	bibtex lzdDoc
	pdflatex lzdDoc
	pdflatex lzdDoc
clean:
	rm -f lzdDoc.aux lzdDoc.bbl lzdDoc.blg lzdDoc.log lzdDoc.pdf
