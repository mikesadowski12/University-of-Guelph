/*
 * This is my first java application
 */
 
import java.util.Scanner;

/**
 *
 * @author  TA CIS*2430
  */
public class Lab1 {

    /**
     * @param args the command line arguments
     * main(int arc, char** argv)
     */
    public static void main(String[] args) {
       
        //Check if arguments exist
        if(args.length < 1)
        {
            System.out.println("Not enough arguments!");
            System.exit(0);
        }
        
        
        //Convert argument string into an integer
        int len =  Integer.parseInt(args[0]);
        
        String name;
      
      	//Prompt user for input
        System.out.print("Please Enter your name: ");
        
        //Define scanner to accept user input
        Scanner in = new Scanner(System.in);
        
        //Scan in next string
        name = in.next();
    
        //int len = name.length();
        
        //Print out "len" times
        for(int i=0;i<len;i++)
        {
            System.out.println("Hello "+name+" is my name. ");
        }
      }
}
