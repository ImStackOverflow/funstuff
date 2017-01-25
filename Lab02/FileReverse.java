import java.io.*;
import java.util.Scanner;


class FileReverse{
	 public static void main(String[] args){
	 	String ass = "eat my big penis";
	 	String[] out = Reverse(ass);
	 	for (int i=0; i<=out.length-1; i++){
	 		System.out.println(out[i]);
	 	}
	}

	public static String[] Reverse(String s){//reverses words
		String[] shit = s.split(" ");//parses words
	 	String[] back = new String[shit.length];
	 	for (int i = 0; i<=shit.length-1;i++){//reverses words
	 		back[i] = wordReverse(shit[i]);
	 	}
	 	return back;//returns reversed words in order they were passed

	}
	public static String wordReverse(String word){//reverses words
	String[] input=word.split("");//parses characters
	StringBuilder output = new StringBuilder();
	int tail = input.length-1;//last element of word array
	for (int i = tail; i!=0; i--){
		output.append(input[i]);//store leters starting from last
	}
	return output.toString();//return reversed word
	}
	
	}