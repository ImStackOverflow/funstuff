FileReverse: FileReverse.java
	javac FileReverse.java
	echo Main-Class: FileReverse > Manifest
	jar cfm FileReverse.jar Manifest FileReverse.class
	echo "" > out
	java -jar FileReverse.jar in out
	del Manifest

FileCopy: FileCopy.java
	javac FileCopy.java

FileTokens: FileTokens.java
	javac FileTokens.java

clean:
	del FileReverse.jar out FileCopy.class FileTokens.class FileReverse.class

