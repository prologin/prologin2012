SOURCE=subject.tex subject_content.tex preambule.tex
MAIN_FILE=subject.tex
PDF=subject.pdf

all: ${PDF}

view: ${PDF}
	evince ${PDF}

clean:
	find . \( -name "*.aux" -o -name "*.idx" -o -name "*.log" -o \
	-name "*.toc" \) -exec rm -f {} \;

distclean: clean
	rm -f ${PDF}

${PDF}: ${SOURCE}
	pdflatex ${MAIN_FILE}
	pdflatex ${MAIN_FILE}
	pdflatex ${MAIN_FILE}