import java.io.*;
import java.util.*;

class Priority{
	private static int[][] queue = new int[400][2];
	private static int head = 0, tail = 0;
	public static PrintWriter out;

	//sort according to priority
	public static void prioritize(int[][] data){
		int i = tail-1; //start from inserted data
		while (i != head && queue[i-1][1] < data[0][1]){
			queue[i][0] = queue[i-1][0];
			queue[i][1] = queue[i-1][1];
			queue[i-1][0] = data[0][0];
			queue[i-1][1] = data[0][1];	
			i = (--i) % queue.length;
		}
	}

	//add to queue and sort
	public static void enqueue(int[][] data){
		if (increase(tail) == head){ //check that space still in queue
			writeToFile("queue isnt big enough for that buddy");
			System.exit(0);
		}
		queue[tail][0] = data[0][0];
		queue[tail][1] = data[0][1];
		tail = increase(tail);
		prioritize(data);
	}

	//return head value
	public static int dequeue() {
		if (head == tail){
			return -666;
		}
		int balls = queue[head][0];
		head = increase(head);
		return balls;
	}

	//incriment counter circularly
	public static int increase(int increase){
		return (++increase) % queue.length;
	}

	//analysis writer
	public static void writeToFile(String lit){
		if(lit.equals("-666 ")) out.print("null ");
		else out.print(lit);
	}

	//prints current queue
	public static void printQueue(){
		System.out.print("The queue is: ");
		for (int i = head;i < tail ;i++ ) {
			System.out.print(" ("+queue[i][0]+","+queue[i][1]+")");			
		}
		System.out.print('\n');
	}


	//reads input file and performs data accordingly 
	public static void parseFile() throws IOException{
		Scanner in = new Scanner(new FileReader("input.txt"));
		String line, holder;
		StringTokenizer analyze;
		//String[] analyze = line.split("//(");
		int[][] data = new int[1][2];
		while(in.hasNextLine()){
			line = in.nextLine();
			analyze = new StringTokenizer(line);

			while(analyze.hasMoreTokens()){
				
				line = analyze.nextToken();
				if (line.equals("d")){
					writeToFile(Integer.toString(dequeue())+" ");
				}

				else{
					for (int i = 0; i < 2; i++) {
						holder = line.replaceFirst(".*?(\\d+).*", "$1");
						data[0][i] = Integer.parseInt(holder);
						if (i == 0) line = analyze.nextToken();
					}
					enqueue(data);
				}
			//printQueue();
		}
		head = 0;
		tail = 0;
		writeToFile("\n");
		
		}
	}


	public static void main(String args[]) throws IOException{
		try{
			out = new PrintWriter("output.txt");
			parseFile();
			out.close();
		}
		catch (Exception e){
			System.out.println("error in scanner");
		}
		
		
		
	}
}