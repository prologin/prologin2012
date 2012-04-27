FILES := slides.tex

all: $(FILES:.tex=.pdf)

%.pdf: %.tex
	texi2pdf --clean $<
#	PDFLATEX="xelatex --shell-escape" texi2pdf --clean $<

clean:

distclean: clean
	rm -f $(FILES:.tex=.pdf)

display: all
	evince $(FILES:.tex=.pdf)
