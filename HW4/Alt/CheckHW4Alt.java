// To check HW4:
// First copy this file and input.txt into directory with your assignment
// Run the following commands:
// make
// javac CheckHW4-alt.java
// java CheckHW4Alt

import java.io.*;
import java.util.regex.*;
import java.util.ArrayList;

class CheckHW4Alt {


    // Convenient method to print error message and exit
    // Input: String message to be printed
    // Output: void, simply exits program

    private static void errExit(String message) {

        System.err.println(message);
        System.exit(1);
    }

    private static boolean isInt(String s) {
        try { 
            int i = Integer.parseInt(s); 
            return true; 
        } catch(NumberFormatException er) { 
            return false; 
        }
    }

    private static boolean isNull(String s) {
        if (s.equals("null")) {
            return true;
        }
        return false;
    }


    // Method to check if validity line is valid
    // Input: line
    // Output: boolean, if the validity line is valid, returns true

    private static boolean checkIfValidInput(String line) {
        line = line.trim();
        boolean valid = true;
        String[] parts = line.split(" ");
        if (line.equals(""))
            return true;
        for (int i=0;i<parts.length;i++) {
            if (!(isInt(parts[i]) || isNull(parts[i])))
                valid = false;
        } 
        return valid;
    }


    // Method to read the solution from solution.txt generated by your program
    // Input: Filename passed via command line agrument
    // Output: boolean, it comes handy to say whether a particular case passed or not

    private static boolean readFromSolutionFile(String file) {

        // ready the arguments before reading
        int count = 1;

        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            while ((line = reader.readLine()) != null) {
                boolean valid = checkIfValidInput(line);
                if (valid) {
                    System.out.println("Case " + count+ " passed");
                } else {
                    System.out.println("Case " + count+ " failed");
                }
                count++;                   
            }
            reader.close();

            
        }
        catch (IndexOutOfBoundsException e) {
            errExit("Array index is out of bounds"); // throw error when inserting elements into arrays fail
        }
        catch (Exception e) {
            errExit("Exception occurred trying to read file"); // throw a generic exception if failure to read occurs
        }
        return true;
    }


    // Main method
    // Input: filename as command line argument
    // Output: void

    public static void main(String[] args) {
        File f_jar = new File("Priority.jar");
        if (!f_jar.exists()) 
            errExit("Note: No file names Priority.jar");
        File f_dir = new File("../Alt");
        if (!f_dir.exists()) 
            errExit("Note: Directory not named Alt");
        File f_hw4 = new File("../../HW4");
        if (!f_hw4.exists()) 
            errExit("Note: directory Alt is not in a directory named HW4");
        File f_output = new File("output.txt");
        if (f_output.exists())
            errExit("Delete output.txt and run again");
        try {
            Process proc = Runtime.getRuntime().exec(new String[]{"java", "-jar", "Priority.jar"});
            BufferedReader reader =
                new BufferedReader(new InputStreamReader(proc.getInputStream()));
            while ((reader.readLine()) != null) {}
            proc.waitFor();
          }
          catch(Exception e) {
            errExit("Student's program thows an exception: " + e);
          }
     
          // call the respective methods to read from file and display the chessboard
          readFromSolutionFile("output.txt");
    }

}

// End
