import java.io.*;

class shit{
	static public void main (String[] args){
		int[][] holy = new int[6][6];
		int pee = 0;
	for(int i = 0; i<6; i++){
	for (int j = 0; j<6; j++){
		holy[i][j] = pee;
		pee++;
	}
	}
	for(int i = 0; i<6; i++){
	for (int j = 0; j<6; j++){
	System.out.print(holy[i][j]+" ");
	}
	System.out.println();
	}
	System.out.println(holy[1][5]);
}
}