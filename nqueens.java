import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

class nqueens{

	static int[][] qLocation = new int[10][2];

	static boolean[][] initial() {

	System.out.println("input board size and placement of first queen");
	Scanner sc = new Scanner(System.in); //get board size
	int size = sc.nextInt();
	boolean[][] board = new boolean[size][size]; //create board
	qLocation[0][0] = sc.nextInt(); //set location of given queen to first index
	qLocation[0][1] = sc.nextInt(); // in form (x)(y)
	board[qLocation[0][0]][qLocation[0][1]] = true; //set location to true
	return board;

	}
	
	public static void main(String[] args){
		int[][] check = new int[16][16];
		boolean[][] chessBoard = initial(); //create chess board
		System.out.println(qLocation[0][0]+" "+qLocation[0][1]);
		fillIn(chessBoard, qLocation[0][0], qLocation[0][1]);
		
		
		
		
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


	//fills in diagonals and collums/rows adjacent to queen
	static void fillIn(boolean[][] board, int qRow, int qCol) { 

		for (int i = 0;i<board.length;i++){
			board[qRow][i]= true; //all spaces above and below
			board[i][qCol]=true; //all spaces left and right
		}

		int bDiag = board.length-qRow-1;//get to lower most right diagonal bound of board
		int dRow = qRow+bDiag;
		int dCol = qCol+bDiag;
		for (int i =0; dCol-i>=0;i++){
			System.out.println(dCol-i+" "+(dRow-i));
			board[dRow-i][dCol-i]=true;
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
	static int findSpace(boolean[][] board){ //find white spaces
		int solution[][] = new int[board.length][board.length];
		for (int i = 0; i<board.length; i++){//go through board ubntil white space is found
			for (int j=0;j<board.length; j++){
				if (board[i][j] == false) {
					return solution[i][j];//return location of empty space
				}
			}
		}
			return -1; //return -1 if cannot find empty space
	}
}