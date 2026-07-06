
.PHONY: clean

all: yerith-erp-server-configurations-data-help.tex
	pdflatex yerith-erp-server-configurations-data-help.tex
	pdflatex yerith-erp-server-configurations-data-help.tex
	evince yerith-erp-server-configurations-data-help.pdf&


deepclean: clean
	rm -f *.blg *.idx *.ilg

clean:
	rm -f *.aux *.ind *.bbl *.log *.lot *.lof *.out *.toc
