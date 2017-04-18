// Filename: ChessBoard.java
//
// Contains class ChessBoard that creates a linkedlist of chessboard where each node holds a chesspiece to be placed
//
// This needs to be compiled with ChessPiece.java, Node.java, Utilities.java, King.java, Queen.java, Knight.java, Rook.java, Bishop.java and Pawn.java.
//
// Output:
//     - analysis.txt file is created corresponding board and query entry in input.txt
//
// Santrupti Nerli, Jan 2017
//
import java.io.*;
import java.util.*;

class ChessBoard {

  private static Node head; // linkedlist to store chesspieces
  private static int board_size; // board_size
  public static BufferedWriter writer; // write to write to file

  // constructor
  public ChessBoard() {
    head = new Node();
  }

  // Method to perform insertion at head of list
  // Input: Node to be inserted
  // Output: void
  public Node insert(Node ass) {
    Node temp = head.getNext();
    head.setNext(ass);
    ass.setNext(temp);
    return head;
  }

  public Node delete(Node delete){//deletes given node, returns head
    Node helper = head;//set new node to head
    if (delete == head){//if trying to delete head
      head = head.getNext();
      delete.setNext(null);
    }
    else {//not trying to delete head
      while(delete != helper.getNext()) helper = helper.getNext();//get node before
      helper.setNext(delete.getNext());//set previous node to node after delete
      delete.setNext(null);//delete node
    }
      return head;//success return head
  }

  // Method to find Node in a given location
  // Input: integer row and column to look for
  // Output: Node found
  public Node findChessPiece(int row, int col) {
    Node piece = head.getNext();
    while(piece != null) {
      if(piece.getRow() == row && piece.getCol() == col) {
        return piece;
      }
      piece = piece.getNext();
    }
    return null;
  }

  //find white king
  //no input
  //returns White king, otherwise null
  public Node findWhiteKing() {
    //System.out.println("finding White king");
    Node piece = head.getNext();
    while(piece != null) {
      if(piece.getChessPiece() instanceof King && piece.getColor() == true) {
        return piece;
      }
      piece = piece.getNext();
    }
    return null;
  }

  //find black king
  //no input
  //returns black king, otherwise null
  public Node findBlackKing() {
    //System.out.println("finding black king");
    Node piece = head.getNext();
    while(piece != null) {
      if(piece.getChessPiece() instanceof King && piece.getColor() == false) {
        return piece;
      }
      piece = piece.getNext();
    }
    return null;
  }

  // Method to count the number of chesspieces for a given type
  // This method will helps us check the validity case
  // Input: character color
  // Output: returns the count
  public int countPiecesOfType(char pieceType) {
    Node piece = head.getNext();
    int pieceCtr = 0;
    // loop through to check if the same piece type is found
    while(piece != null) {
      if(Utilities.returnChessPieceType(piece) == pieceType) {
        pieceCtr++;
      }
      piece = piece.getNext();
    }
    return pieceCtr;
  }

  // Method to count the number of chesspieces on a single location
  // This method will helps us check the validity case
  // Input: integer row and column
  // Output: returns the count
  public int countPiecesInLocation(int row, int col) {
    Node piece = head.getNext();
    int pieceCtr = 0;
    // loop through to check if any two pieces overlap
    while(piece != null) {
      if(piece.getRow() == row && piece.getCol() == col) {
        pieceCtr++;
      }
      piece = piece.getNext();
    }
    return pieceCtr;
  }

  // Method to check if two pieces occupy the same place
  // This method utilizes the countPiecesInLocation method to see
  // if there are more than two pieces in a single location
  // Input: none
  // Output: returns true if two pieces occupy same position
  public boolean twoPiecesOccupySamePosition() {
    Node piece = head.getNext();
    // loop through and see if any of the pieces overlap
    while(piece != null) {
      if(countPiecesInLocation(piece.getRow(), piece.getCol()) > 1) {
        return true;
      }
      piece = piece.getNext();
    }
    return false;
  }

  // Method to check validity
  // basically looks if there are not two chesspieces in the same location and
  // one each colored king is present
  // Input: none
  // Output: returns if it is valid or not
  public boolean checkValidity() {
    if(!twoPiecesOccupySamePosition() && countPiecesOfType('k') == 1 && countPiecesOfType('K') == 1) {
      return true;
    }
    else {
      return false;
    }
  }

  // Method to check if two nodes given are different or the same ones
  // It serves as a helper when trying to find the attack
  // Input: two nodes
  // Output: returns if they are same or different pieces
  public boolean isDifferent(Node one, Node other) {
    if(one.getRow() == other.getRow() && one.getCol() == other.getCol() && one.getColor() == other.getColor()) {
      return false;
    }
    return true;
  }

  // Method to see if any of the pieces attack
  // as soon as you encounter the first attack, just print it and return
  // Input: none
  // Output: returns nothing
  public void isOneAttackingOther(Node piece) {
    // get the first valid chesspiece (remember not the head)
    Node helper = head.getNext();
    // loop through each of the remaining chesspieces and check for attack
    while(helper != null) {
      Node other = head.getNext();
      while(other != null) {
        if(isDifferent(helper, other) && helper.getChessPiece().isAttacking(other.getRow(), other.getCol())) {
          writeToAnalysisFile(Utilities.returnChessPieceType(helper) + " " + helper.getCol() + " " + helper.getRow() + " " + Utilities.returnChessPieceType(other) + " " + other.getCol() + " " + other.getRow() + "\n");
          return;
        }
        other = other.getNext();
      }
      helper = helper.getNext();
    }
    writeToAnalysisFile("-\n");
  }
  //return pieces that piece is attacking, helper node points to where to start in list
  //input: attack piece
  //return: attacked node
  public Node Attack(Node piece, Node helper){
    //System.out.println("at attack");
	  while (helper != null){
	   if(isDifferent(helper, piece) && piece.getChessPiece().isAttacking(helper.getRow(), helper.getCol())) {
		   return helper;
	   }
	   helper = helper.getNext();
	  }
	  return helper;
  }

  //method to check if signs match
  //input: 2 numbers
  //return true if sign match false otherwise
  public boolean sameSign(int a, int b){
   if(a < 0 && b < 0) return true;
   if (a > 0 && b > 0) return true;
	 if (a == 0 && b == 0) return true;
    //if(a*b > 0) return true;
    else return false;
  }
  
	//checks for pieces blocking
  //input: 2 nodes want to check
  //output: true is no blocking, false if piece is blocking
  public boolean canAttack(Node attack, Node dicked){//attack = atacking piece, dicked is attacked piece
    //System.out.println("at canAttack");
    if(attack.getColor() == dicked.getColor()) return false;//cant attack same color

   //System.out.println("at canAttack");
    int checkX = attack.getCol() - dicked.getCol();//get dist between dicked and attack
    int checkY = attack.getRow() - dicked.getRow();
    //System.out.println("attacking: ("+attack.getCol()+","+attack.getRow()+") attacked: ("+dicked.getCol()+","+dicked.getRow()+")");
    int betweenX, betweenY;
    Node helper = head.getNext();

    while(helper != null){
	   helper = Attack(attack, helper);
	   if (helper == null) return true;//reached end of list no blocks

	   else if (helper == dicked || helper == attack);//only want to check for pieces between
      //do nothing
	  
    else if (helper != null){
		//System.out.println(helper.getChessPiece()+"x: "+helper.getCol()+"y: "+helper.getRow());
		betweenX = attack.getCol() - helper.getCol();//get dist between attack and possible block
		betweenY = attack.getRow() - helper.getRow();
		//System.out.println("bx: "+betweenX+" by: "+betweenY+" cx: "+checkX+" cy: "+checkY);
		if(Math.abs(betweenX) <= Math.abs(checkX) && Math.abs(betweenY) <= Math.abs(checkY)){//block is closer to attack than desired attack
			if(sameSign(betweenX,checkX) && sameSign(betweenY,checkY)){//in same attacking path
				return false;
        }
		  }
	   }
     helper = helper.getNext();//move along
	 }
  return true;//can attack piece, no block
  }

  //performs moves
  //input chessboard and int[4] with moves
  //output true if move was valid false otherwise
  public static boolean Moving(ChessBoard c, int spaces[]){
	  //System.out.println("at moving");
	  //System.out.println("x: "+spaces[0]+" y: "+spaces[1]);
	  Node attack = c.findChessPiece(spaces[1], spaces[0]);
	  Node dicked = c.findChessPiece(spaces[3], spaces[2]);
	  Node penis = dicked;
	  if (attack == null){//check piece at attacking space
		  //System.out.println("no piece at attack space");
      //c.writeToAnalysisFile("invalid: no piece at attack space");
		  return false;
	  }
    if (attack.getChessPiece().isAttacking(spaces[3],spaces[2])){//if piece can move there
	     if (dicked != null){//piece at moving space
		 
			   if (c.canAttack(attack, dicked)){//if no block
			  //System.out.println("taking piece");
			  attack.posSwitch(dicked.getRow(), dicked.getCol());
        //c.writeToAnalysisFile("valid: taking piece ");
			  c.delete(dicked);
		  }
		  else{//blocked
				//System.out.println("position blocked");
        //c.writeToAnalysisFile("invalid: position blocked ");
				return false;
		  }
		  }
		 

	  else {//trying to move to empty space
		  dicked = attack.dummy();
		  dicked.posSwitch(spaces[3],spaces[2]);
		  //System.out.println("penis");
		  if (c.canAttack(attack, dicked)){//if no block
		  attack.posSwitch(spaces[3], spaces[2]);
      //c.writeToAnalysisFile("Valid: moving to empty space");
		  }
		  else{//blocked
				//System.out.println("position blocked");
        //c.writeToAnalysisFile("invalid position blocked");
				return false;
		  }
	  }
	  //convertFromListToMatrixAndPrint(1);
	  return true;
  }
       //System.out.println("piece cant move there invalid");
       //c.writeToAnalysisFile("invalid: piece cant move there");
       return false;
  }

  
  //moves moves king to position and checks if attacked
  //input: king and moveto spaces[x],[y]
  //output: true if attacked, false otherwise
  
  public boolean Kings(ChessBoard c, Node king, int[] move){
    boolean outCome;
    int[] goBack = {king.getRow(), king.getCol()};
    king.posSwitch(move[1], move[0]);
    outCome = c.checkAttack(king);
    king.posSwitch(goBack[0], goBack[1]);
    return outCome;
  }
  
  
  
  //checks if given number is >0 && <boardsize
  //input: number
  //output: true for yes false for out of bound
  public static boolean inBounds(int checkx, int checky){
	  if (checkx > 0 && checkx <= board_size){//x in bounds
      if (checky > 0 && checky <= board_size){//y in bounds
        return true;//sall good
      }
	  }
	  return false;
  }
  
  //takes in king to check, generates possible movements and checks if attacked at them, counts for origional king placement
  //input: chessboard and king to get checked
  //output: true if checkmated false if otherwise
  public boolean checkMate(ChessBoard c, Node king){
    int[] shift = new int[2];
    boolean did = false;
    int row, col, moves = 0, checks = 0;
    int attackRow[] = {-1, -1, 0, 1, 0, 1, 1, -1}; // possible attack row positions
    int attackCol[] = {0, -1, -1, -1, 1, 1, 0, 1}; // possible attack col positions
    //check if king is currently in check
    moves = 1;
    if(checkAttack(king)) checks ++;
     for(int i = 0; i < 8; i++) {
          row = king.getRow() + attackRow[i];
          col = king.getCol() + attackCol[i];
          if(inBounds(row,col) && findChessPiece(row,col) == null) {//piece is in bounds and no piece already there
            
            moves++;//can make valid move
            shift[0] = col;
            shift[1] = row;
            if(Kings(c, king, shift)) {
              did = true; //zero case
              checks++;//is attacked at that move
            }
            
          }
        }
        //System.out.println("moves: "+moves+" checks: "+checks);
     if (checks == moves && did) return true;//if all valid moves get attacked then in check
     return false;
  }
  
  
  //checks origional board to see if any piece is attacking king 
  //input: chessboard and king piece
  //output: true if piece is atacking king
  public boolean checkAttack(Node king){
    //System.out.println("at checkcheck");
    //System.out.println("x: "+king.getCol()+" y: "+king.getRow());
	  Node attacking = head.getNext();
    Node gettingA = new Node();
    while(attacking != null){//go each node in list
      gettingA = Attack(attacking, head.getNext());//get piece that current node can attack
      while (gettingA != null){
        if(gettingA == king){//if attacked piece is king
          if (canAttack(attacking, king)){//check if can attack
            //System.out.println("attacking: ("+attacking.getCol()+","+attacking.getRow()+") king: ("+king.getCol()+","+king.getRow()+")");
            return true;
            }
            gettingA = null;//otherwise blocked, move onto next node
          }
          else { 
            gettingA = Attack(attacking, gettingA.getNext());//piece attacked isn't king, doesnt matter
            //move along
          }
        }
    attacking = attacking.getNext();//analyze next piece/node
    if (attacking == king) attacking = attacking.getNext();//make sure not to analyse self
    }
    return false; //no pieces can attack king
  }
  
  // Method to write to the analysis.txt file
  // Input: String to write
  // Output: void, just write
  public void writeToAnalysisFile(String stringToWrite) {
    try {
        writer.write(stringToWrite);
    }
    catch (Exception e) {
        Utilities.errExit("Exception occurred while trying to write to file: writeToAnalysisFile"); // throw a generic exception if failure to read occurs
    }
  }

  // Method to iterate through the list and update a 2D array for printing the board
  // onto the console
  // Input: integer board number read from input.txt
  // Output: void, jusr print the solution
  public static void convertFromListToMatrixAndPrint(int board_no) {
    // Initialize isFilled board
    char[][] isFilled = new char[board_size+1][board_size+1];
    for(int i = 0; i < board_size; i++) {
      for(int j = 0; j < board_size; j++) {
        isFilled[i][j] = '-';
      }
    }
    // iterate through the list and update isFilled matrix
    Node piece = head.getNext();
    while(piece != null) {
      isFilled[piece.getRow()][piece.getCol()] = Utilities.returnChessPieceType(piece);
      piece = piece.getNext();
    }

    System.out.println("Board No: " + (board_no/2));
    Utilities.printSolution(isFilled, board_size);
  }

  // Method to read from input.txt
  // for each chessboard and query, perform all the required operations
  // an then proceed further
  // Input: none
  // Output: void, jusr read and perform requested operations
  public static void readFromInputFile(){
    int lineCtr = 0;
    ChessBoard c = null;

    try {
        BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
        String line;
        //line = reader.readLine();
             while ((line = reader.readLine()) != null) {
        //for (int j = 0; j<2 ;j++ ) {
            String[] args = line.split(" "); // Reader assumes that the input format is as given in the instruction
            // If the line is 2i, then I know that it is a configuration of a ChessBoard
            // so create a new ChessBoard here, parse board size and insert
            // given chesspieces into the linked list
            if(lineCtr % 2 == 0) {
              c = new ChessBoard();
              board_size = Integer.parseInt(args[0]);
              for(int i = 1; i < args.length; i += 3) {
                head = c.insert(new Node(args[i].charAt(0), Integer.parseInt(args[i+2]), Integer.parseInt(args[i+1])));
              }
            }
            else {//on line after board info
              Utilities.printList(head);
              performOperations(c,args,lineCtr-1);
            }
            lineCtr++; // move to the getNext() line
        }
        reader.close();
    }
    catch (NumberFormatException e) {
        Utilities.errExit("All arguments must be integers"); // throw error incase parsing integer fails
    }
    catch (IndexOutOfBoundsException e) {
        Utilities.errExit("Array index is out of bounds"); // throw error when inserting elements into arrays fail
    }
    catch (Exception e) {
        System.out.println(e.getMessage());
        //Utilities.errExit();//"Exception occurred trying to read file"); // throw a generic exception if failure to read occurs
    }
  }

  // Method to perform all the requested operations
  // namely, check validity, perform the search query
  // check for attack
  // Input: ChessBoard and the query
  // Output: returns the count
  public static void performOperations(ChessBoard c, String[] input, int board_no) {
    int i = 0;
    Node helper = new Node();
    Node compare = new Node();
    boolean whiteCheck, blackCheck, whiteMate, blackMate;

    try {
      // Check for validity here
      if(c.checkValidity() == false) {
        writer.write("Invalid board\n");
        return;
      }
      System.out.println("at begining: ");
      //convertFromListToMatrixAndPrint(board_no);
      //check for checkMate
      System.out.println("after whitemate: ");
      whiteMate = c.checkMate(c, c.findWhiteKing());
      
      //convertFromListToMatrixAndPrint(board_no);
      
      System.out.println("after blackmate: ");
      blackMate = c.checkMate(c, c.findBlackKing());
      
      //convertFromListToMatrixAndPrint(board_no);

      //check for check
      whiteCheck = c.checkAttack(c.findWhiteKing());
      blackCheck = c.checkAttack(c.findBlackKing());

      //do moves
      int[] query = new int[4];
      for (i = 0; i < input.length; i++){
        query[i%4] = Integer.parseInt(input[i]);
        if(( (i+1) % 4) == 0){
           if(Moving(c,query)) c.writeToAnalysisFile("Valid ");
           else{
            c.writeToAnalysisFile("Invalid ");
            break;
           }
         }
      }
      c.writeToAnalysisFile("\n");
      if (whiteMate) c.writeToAnalysisFile("White checkmated ");
      //if (blackMate && blackCheck) c.writeToAnalysisFile("black checkmated ");
      //if(whiteCheck) c.writeToAnalysisFile("White in check ");
      //if(blackCheck) c.writeToAnalysisFile("Black in check ");      
      else if (blackMate) c.writeToAnalysisFile("Black checkmated ");
      
      
      else {
        if(blackCheck) c.writeToAnalysisFile("Black in check ");
        if(whiteCheck) c.writeToAnalysisFile("White in check ");
        
        if(!blackCheck && !whiteCheck) c.writeToAnalysisFile("All kings safe");
      }
      
      
      
      c.writeToAnalysisFile("\n");
      //convertFromListToMatrixAndPrint(board_no);
    }
    catch(Exception e) {
      Utilities.errExit("Error while performing operations");
    }

  }

public static void main(String[] args) {
    try{
      writer = new BufferedWriter(new FileWriter("analysis.txt")); // open the file to write
      readFromInputFile(); // read from input file and perform operations
      System.out.println("shit done");
      writer.close(); // close the writer
   }
    catch(Exception e) {
      Utilities.errExit("Error");
    }


  }
}

// End
