import java.io.*;
import java.util.Scanner;


class FileReverse{
	 public static void main(String[] args){
	 	String output = stringReverse("eat my big penis");
	 	System.out.println(output);


	}
	public static String stringReverse(String s){
	char input[s.length]=s.split("");
	char[] output = new char[s.length];
	for (int i = s.length; i>= 0; i--){
		output[s.length-i]=input[i];
	}
	}
}