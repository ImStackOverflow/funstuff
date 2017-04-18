	#------------------------------------------------------------------------------
#
#  Makefile for CMPS 101 pa1 
#  Made by Patrick Tantalo
#  Compiles all .java files in the current directory and creates an executable
#
#       https://classes.soe.ucsc.edu/cmps012b/Summer15/lab1.pdf
#
#------------------------------------------------------------------------------ 

MAINCLASS  = Priority
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS).jar 

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	rm Manifest	

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE) output.txt
