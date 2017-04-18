# Makefile with macros #------------------------------------------------------------------------------
JAVASRC = chess.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = chess
CLASSES = Bishop.class King.class Knight.class Node.class queen.class Rook.class chessPiece.class chess.class
JARFILE = Chessboard.jar
all: $(JARFILE)
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)
clean:
	rm $(CLASSES) $(JARFILE) analysis.txt

