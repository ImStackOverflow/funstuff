import java.io.*;
import java.util.ArrayList;
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
	piece.qY = sc.nextInt()-1; //set location of given queen to first index
	piece.qX = sc.nextInt()-1; // in form (x)(y)
	board[piece.qY][piece.qX] = true; //set location to true
	qLocation = new int[size][2];//create array to store locations of length "size"
	qLocation[0][0] = piece.qY; //store cordinates
	qLocation[0][1] = piece.qX;
	return board;
	}
	
	public static void main(String[] args){
		queens piece = new queens();//create queens var to hold coordinates
		boolean[][] chessBoard = initial(piece); //create chess board
		System.out.println(generate(chessBoard,piece,0,chessBoard.length));
		if (generate(chessBoard,piece,0,chessBoard.length)==1){
			System.out.println("the solutions to your stupid problem is:");
			for (int i=0; i < chessBoard.length; i++){
				for (int j=0;j<2;j++){
					System.out.print(qLocation[i][j]+" ");
				}
				System.out.println();
			}
		}
		else {
			System.out.println("there was no solution to your stupid intput");
		}
		
		
		
		for (int i = 0; i<chessBoard.length;i++){//debug to print boolean board
			for (int j = 0; j<chessBoard.length;j++){
				int k = 0;
				if (chessBoard[i][j] == true){
					k = 1;
				}
				else {
					k=0;
				}
				System.out.print(k+" ");
			}
			System.out.println("  "+(i+1));
		}
		
		/*
		chessBoard = fillIn(chessBoard,qLocation[0][0],qLocation[0][1]);
		check[0][0] = findSpace(chessBoard);
		System.out.println(check[0][0]);
		*/
	}
	static int generate(boolean[][] board, queens piece, int startCol, int qRemaining){
		if (qRemaining==0) {//all queens placed
			return startCol;//success!
		}
		fillIn(board, piece);//pass in board and piece to draw attack lines
		queens solution = findSpace(board, startCol);
		if (solution.qX == -1){//no more free spaces
			return startCol;
		}
		else {//still more queens to be placed
			qLocation[startCol][0]=solution.qX;//add x cordinate
			qLocation[startCol][1]=solution.qY;//add y cordinate
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
		i=0;
		while (piece.qX-i>=0 && piece.qY-i>=0){//up and left
			board[piece.qY-i][piece.qX-i]=true;
			i++;
		}
		i=0;
		while (piece.qY+i!=(board.length) && piece.qX+i!=(board.length)){//down and right
			board[piece.qY+i][piece.qX+i] = true;
			i++;
		}
		i=0;
		while (piece.qY+i!=(board.length) && piece.qX-i>=0){//up and right
			board[piece.qY-i][piece.qX+i] = true;			
			i++;
		}

		/*
		int bDiag = piece.qY;
		int dX=piece.qX+bDiag; //set to upper most right diagonal bound
		int dY=piece.qY-bDiag;
		for (int i = 0;  dY+i!=(board.length) && dX-i>=0; i++){
			board[dY+i][dX-i] = true;
		}
		bDiag = board.length-(piece.qY+1);//get to upper most left diagonal bound of board
		System.out.println("bDiag = "+bDiag);
		System.out.println("qX = "+piece.qX);
		System.out.println("qY = "+piece.qY);
		dX = piece.qX+bDiag;
		dY = piece.qY+bDiag;
		System.out.println((dY)+" pee "+(dX));
		for (int i =0; dX-i!=0 && dY-i!=0;i++){
			System.out.println((dY-i)+" "+(dX-i));
			board[dY-i][dX-i]=true;//switch to "unable to place queen"
		}
		
		/*
		while (qCol<board.length && qRow < board.length){ 
		System.out.printf(qRow-i+" "+(qCol-i));
			board[qRow-i][qCol-i]=true;//upper left diagonal
			i++;
		}/*
		i = 0;
		while (qCol>0 && qRow > 0){ 
			board[qRow+i][qCol+i]=true;//lower right diagonal
			qRow=qRow;
			qCol=qCol;
			i++;
		}
		i=0;
		while (qCol>0 && qRow > 0){ 
			board[qRow-i][qCol+i]=true;//upper right diagonal
			qRow=qRow;
			qCol=qCol;
			i++;
		}
		i=0;
		while (qCol>0 && qRow > 0){ 
			board[qRow+i][qCol-i]=true;//lower left diagonal
			qRow=qRow;
			qCol=qCol;
			i++;
		}
		*/
		
	}
	static queens findSpace(boolean[][] board, int start){ //find white spaces
		queens solution = new queens();
		for (int i = start; i<board.length; i++){//go through board ubntil white space is found
			for (int j=0;j<board.length; j++){
				if (board[i][j] == false) {
					solution.qX = i;
					solution.qY = j;
					return solution;//return location of empty space
				}
			}
		}
		solution.qX = -1;
		return solution; //return -1 if cannot find empty space
	}
}