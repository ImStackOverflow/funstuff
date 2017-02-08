import java.io.*;

class ChessBoard {

  private static Node head; // linkedlist to store chesspieces

  static Node find(int x, int y, Node helper){//takes in (x,y) returns found node
    helper=helper.head;//start at head
    while (helper != null){//till end of linked list
      if (x == helper.piece.X && y == helper.piece.Y){
        return helper;
      }
      helper=helper.after;
    }
    return null;//returns null if piece doesnt exist
  }

  static boolean verify(Node lala){//returns true if good
    int good;//check kings
    lala = lala.head;
    Node helper;
    while (lala.after != null){//make sure no duplicates, returns false if there is
      helper = lala.after;
      while (helper != null){
        if (lala.piece.X == helper.piece.X
        && lala.piece.Y == helper.piece.Y){//x y cordinates match
          return false;//2 pieces in same place
      }
      helper=helper.after;
      }
      lala = lala.after;
    }
    helper = lala.head;
    good = 0;
    while(helper != null){
      if(helper.piece.type == 'k'){//white king
        good++;
      }
      if(helper.piece.type == 'K'){//black king
        good++;
      }
      helper = helper.after;
    }
    if (good == 2) return true;//2 kings of each color
    else return false;//no 2 kings  
  }
    static Node createBoard(String firstL, Node helper) throws IOException{//returns linked list of board
    String[] data = firstL.split(" ");//split line into characters
    int length = data.length-1;//last place in array
    /*for (int i = 0; i <= length; i++){
      System.out.print(data[i]);
    }*/
    int i = 0;//start after board size
    //System.out.println("lengnth is: "+length);
    while (i<length){//for all data
      
      //System.out.println("i is: "+i);
      switch (data[++i].toUpperCase()) {//create chess piece type

        case "K":
          helper.piece = new King();
          helper.piece.type = 'k';
          break;

        case "Q":
          helper.piece = new queen();
          helper.piece.type = 'q';
          break;

        case "R":
          helper.piece = new Rook();
          helper.piece.type = 'r';
          break;

        case "B":
          helper.piece = new Bishop();
          helper.piece.type = 'b';
          break;

        case "N":
          helper.piece = new Knight();
          helper.piece.type = 'n';
          break;
      }
      //System.out.println("i is: "+i+"piece type is: "+helper.piece.type);
      if(data[i]==data[i].toUpperCase()){//check if black
        helper.piece.type = Character.toUpperCase(helper.piece.type);
        helper.piece.shit = 'b';
      }
      helper.piece.X = Integer.parseInt(data[++i]);//add x place 
      helper.piece.Y = Integer.parseInt(data[++i]);//add y place
      helper.piece.boardSize = Integer.parseInt(data[0]);//add board size
      if(i<length){
        helper=createNode(helper);
      }
    }
    return helper.head;
  }

 public static void main(String[] args) {
    Scanner in = new Scanner(new File("input.txt"));//in file
    PrintWriter out = new PrintWriter("analysis.txt");//out file
    Node poop = new Node();//initiate linked list
    Node helper = new Node();
    boolean found = false;
    poop.head = poop;
    String[] look = new String[2];
    String input;
    int i = 0;
    while (in.hasNextLine()){
      input = in.nextLine();//get board data line
      poop = poop.head;
      poop = clearList(poop);
      poop = createBoard(input, poop);//make linked list of pieces
      input = in.nextLine();//get square
      if (verify(poop)==true){//board is good
        look = input.split(" ");//parse second line and get piece at space
        helper = find(Integer.parseInt(look[0]),Integer.parseInt(look[1]),poop);
        if (helper != null){//found space
          out.print(helper.piece.type+" ");
        }
        else{
          out.print("- ");
        }
      
      int[] attacks = new int[poop.piece.boardSize*poop.piece.boardSize];
      found = false;
      while(poop.after != null && found != true){
      attacks = poop.piece.attack(poop.piece);//generate attack array
        for (i = 0; attacks[i] != 0;){//all elements in attack array
          helper = find(attacks[i++],attacks[i++],poop);//search list for attack spaces
           if(helper != null && (helper.piece.shit != poop.piece.shit)){//node at piece it can attack
            attacks[i] = 0;//exit loop
            found = true;
             }
            }
            if (found == false) poop = poop.after;
          }
        if (found == true){
          out.println(poop.piece.type+" "+poop.piece.X+" "+poop.piece.Y+" "
          +helper.piece.type+" "+helper.piece.X+" "+helper.piece.Y);
      poop = poop.head;
        }
        else out.println("-");
      }

        else {
        out.println("Invalid");
      }
    }
    in.close();
    out.close();
      
  }
}

// End
