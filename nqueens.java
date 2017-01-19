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
	board[qLocation[0][0]-1][qLocation[0][1]-1] = true; //set location to true
	return board;

	}
	
	public static void main(String[] args){
		int[][] check = new int[16][16];
		boolean[][] chessBoard = initial(); //create chess board
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
			board[qRow-1][i]= true; //all spaces above and below
			board[i][qCol-1]=true; //all spaces left and right
		}

		int i = 0;
		int dRow = qRow+1;
		int dCol = qCol+1;
		while (dCol<board.length && dRow < board.length){ 
		System.out.printf(dRow-i+" "+(dCol-i));
			board[dRow-i][dCol-i]=true;//upper left diagonal
			dRow=qRow;
			dCol=qCol;
			i++;
		}/*
		i = 0;
		while (dCol>0 && dRow > 0){ 
			board[dRow+i][dCol+i]=true;//lower right diagonal
			dRow=qRow;
			dCol=qCol;
			i++;
		}
		i=0;
		while (dCol>0 && dRow > 0){ 
			board[dRow-i][dCol+i]=true;//upper right diagonal
			dRow=qRow;
			dCol=qCol;
			i++;
		}
		i=0;
		while (dCol>0 && dRow > 0){ 
			board[dRow+i][dCol-i]=true;//lower left diagonal
			dRow=qRow;
			dCol=qCol;
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