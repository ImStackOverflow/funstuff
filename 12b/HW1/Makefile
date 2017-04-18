nQueens: nqueens.java
	javac nqueens.java
	echo Main-class: nqueens > Manifest
	jar cvfm NQueens.jar Manifest nqueens.class queens.class
	del Manifest

clean:
	del -f NQueens.jar nqueens.class queens.class