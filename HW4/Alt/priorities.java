import java.io.*;
import java.util.*;

class priorities{
	private static int[][] queue = new int[400][2];
	private static int head = 0, tail = -1;
	private static boolean initialized = false;
	public static PrintWriter out;

	public static void prioritize(int[][] data){
		System.out.println("at prioritize");

		int i = tail-1;
		System.out.println("data[0][1] = "+data[0][1]+ "queue["+i+"][1] = "+queue[i+1][1]);
		if (i+1 == head && queue[i+1][1]<=data[0][1]){
			return;
		}
		while (i+1 != head && queue[i][1] < data[0][1]){
			queue[i+1][0] = queue[i][0];
			queue[i+1][1] = queue[i][1];
			queue[i][0] = data[0][0];
			queue[i][1] = data[0][1];	
			i = (--i) % queue.length;
		}
	}
	public static void enqueue(int[][] data){
		System.out.println("at enqueue: queue.length = "+queue.length);
		tail = (++tail) % queue.length;
		System.out.println("head is: "+head+" tail is: "+tail);
		if (tail == head && initialized == true){
			writeToFile("queue isnt big enough for that buddy");
			System.exit(0);
		}
		initialized = true; 
		queue[tail][0] = data[0][0];
		queue[tail][1] = data[0][1];
		prioritize(data);
	}

	public static int dequeue() {
		System.out.println("at dequeue");
		if (head == tail){
			writeToFile("nothing in the queue buddy");
			System.exit(0);
		}
		int balls = queue[head][0];
		head = (++head) % queue.length;
		return balls;
	}

	public static void writeToFile(String lit){
		out.println(lit);
	}

	public static void printQueue(){
		System.out.println("at printqueue");
		System.out.print("The queue is: ");
		//while(queue[i][1] != 0){
		for (int i = head;i <= tail ;i++ ) {
			System.out.print(" ("+queue[i][0]+","+queue[i][1]+")");			
			//i++;
		}
	}


	public static void parseFile(){
		Scanner in = new Scanner(new FileReader("input.txt"));
		Scanner line = in.getLine();
		int[][] data = new int[1][2];
		int deletes = StringUtils.countOccurencesOf(line,'d');
		System.out.println(deletes+" deques");
		while(line.hasNextInt()){
			data[0][0] = in.nextInt();
			data[0][1] = in.nextInt();
			System.out.println("the numbers were: "+data[0][0]+","+data[0][1]);
			enqueue(data);
		}
		for (int i = 0; i <= deletes; i++) {
			dequeue();
		}
		printQueue();
	}
	public static void main(String args[]) throws IOException{
		out = new PrintWriter("output.txt");
		parseFile();
		out.close();
		
		
	}
}