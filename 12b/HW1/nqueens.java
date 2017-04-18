import java.io.*;
import java.util.Scanner;

class queens{
	int qY;
	int qX;

}

public class nqueens extends queens{

	static int[][] qLocation;

	static boolean[][] initial(queens piece) {

	System.out.println("input board size and placement of first queen");
	Scanner sc = new Scanner(System.in); //get board size
	int size = sc.nextInt();//save first number as size of board
	boolean[][] board = new boolean[size][size]; //create board
	piece.qX = sc.nextInt()-1; //set location of given queen to first index
	piece.qY = sc.nextInt()-1; // in form (x)(y)
	board[piece.qY][piece.qX] = true; //set location to true
	qLocation = new int[size][2];//create array to store locations of length "size"
	qLocation[0][0] = piece.qX; //store cordinates
	qLocation[0][1] = piece.qY;
	return board;
	}
	
	public static void main(String[] args) throws IOException{
		PrintWriter output = new PrintWriter("solutions.txt");//create solutions text file
		
		queens piece = new queens();//create queens var to hold coordinates
		boolean[][] chessBoard = initial(piece); //create chess board
		
		if (generate(chessBoard,piece,0,chessBoard.length)==1){//if successfull in placing all queens
			//output.println("Solutions are:");
			for (int i=0; i < chessBoard.length; i++){//print solution array
				for (int j=0;j<2;j++){
					output.print((qLocation[i][j]+1)+" ");
				}
				output.println();
			}
		}
		else {//couldnt place all the queens
			output.println("No Solution");
		}
		output.close();
	}
	static void printBoard(boolean[][] chessBoard){
		for (int i = 0; i<chessBoard.length;i++){//debug to print boolean board
			for (int j = 0; j<chessBoard.length;j++){
				int k = 0;
				if (chessBoard[i][j] == true){
					k = 1;
				}
				else {
					k=0;
				}
				//System.out.print(chessBoard[i][j]+" ");
				System.out.print(k+" ");
			}
			System.out.println("  "+(i+1));
		}
		
	}
	static int generate(boolean[][] board, queens piece, int startCol, int qRemaining){
		
		fillIn(board, piece);//pass in board and piece to draw attack lines
		queens solution = findSpace(board);//find open spaces
				//printBoard(board);
				//System.out.println("placed queen at: "+solution.qX + " "+solution.qY);

		if (solution.qX == -1){//no more free spaces
			if (qRemaining==1) {//all queens placed
				return 1;//success!
			}
			else{//no more spaces but still  more queens
				return 0;//impossible!
			}
		}
		
		
		else {//still more queens to be placed
			qLocation[startCol+1][0]=solution.qX;//add x cordinate to solutions
			qLocation[startCol+1][1]=solution.qY;//add y cordinate
			return generate (board, solution, startCol+1,qRemaining-1);//and do it again
		}

	}


	//fills in diagonals and collums/rows adjacent to queen
	static void fillIn(boolean[][] board, queens piece) { 
	
		for (int i = 0;i<board.length;i++){
			board[piece.qY][i]= true; //all spaces above and below
			board[i][piece.qX]=true; //all spaces left and right
		}
		
		int i = 0;
		while (piece.qY+i!=(board.length) && piece.qX-i>=0){//down and left
			board[piece.qY+i][piece.qX-i] = true;//switch to "unable to place queen"
			i++;
		}
		//System.out.println("board after down and left");
		//printBoard(board);
		
		i=0;
		while (piece.qX-i>=0 && piece.qY-i>=0){//up and left
			board[piece.qY-i][piece.qX-i]=true;
			i++;
		}
		//System.out.println("board after up and left");
		//printBoard(board);
		
		
		i=0;
		while (piece.qY+i!=(board.length) && piece.qX+i!=(board.length)){//down and right
			board[piece.qY+i][piece.qX+i] = true;
			i++;
		}
		//System.out.println("board after down and right");
		//printBoard(board);
		

		i=0;
		while (piece.qY-i>=0 && piece.qX+i<= board.length-1){//up and right
			board[piece.qY-i][piece.qX+i] = true;			
			i++;
		}
		//System.out.println("board after up and right");
		//printBoard(board);
		
		
	}
	static queens findSpace(boolean[][] board){ //find white spaces
		queens solution = new queens();
		for (int i = 0; i<board.length; i++){//go through board ubntil white space is found
			for (int j=0;j<board.length; j++){
				if (board[j][i] == false) {
					solution.qY = j;
					solution.qX = i;
					return solution;//return location of empty space
				}
			}
		}
		solution.qX = -1;
		return solution; //return -1 if cannot find empty space
	}
}