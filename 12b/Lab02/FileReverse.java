import java.io.*;
import java.util.Scanner;


class FileReverse{
	 public static void main(String[] args) throws IOException{
		 Scanner in = new Scanner(new File(args[0]));//open up input file
		 PrintWriter out = new PrintWriter(new File(args[1]));//open up output file
		 String[] put = new String[2];//hold parsed string from file
		 for(int i=0; in.hasNext(); i++){//for all words in file
			  if (i==2){//reset buffer
				 i=0;
			 }
			 put[i]=in.next();//index parsed word
			 out.println(stringReverse(put[i]));//write reversed word to file
		 }
		 
		 out.close();
		 in.close();
	}
	//for reading in strings
	public static String[] Reverse(String st){//reverses words
		String[] shit = st.split(" ");//parses words
	 	String[] back = new String[shit.length];
	 	for (int i = 0; i<=shit.length-1;i++){//reverses words
	 		back[i] = stringReverse(shit[i]);
	 	}
	 	return back;//returns reversed words in order they were passed

	}
	//for reading in words
	public static String stringReverse(String s){//reverses words
	String[] input=s.split("");//parses characters
	StringBuilder output = new StringBuilder();
	int tail = input.length-1;//last element of word array
	for (int i = tail; i>=0; i--){
		output.append(input[i]);//store leters starting from last
	}
	return output.toString();//return reversed word
	}
	
	}