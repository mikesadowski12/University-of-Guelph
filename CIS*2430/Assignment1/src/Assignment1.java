/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment1;

import java.util.Scanner;

/**
 *
 * @author michaelsadowski
 */
public class Assignment1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner scanner = new Scanner(System.in);
        String userInput = new String("none");
        String titleKeywords = new String();
        int startHour = 0;
        int startMinute = 0;
        int endHour = 0;
        int endMinute = 0;
        int userInputInt = 0;


        /*create planner object, and temp activity objects*/
        DayPlanner myPlanner = new DayPlanner();

        while ("quit".equals(userInput.toLowerCase()) == false && "q".equals(userInput.toLowerCase()) == false && "4".equals(userInput.toLowerCase()) == false) {

            if ("add".equals(userInput.toLowerCase()) || "1".equals(userInput.toLowerCase())) {
                System.out.print("\n1. <Home> Activity\n");
                System.out.print("2. <School> Activity\n");
                System.out.print("3. <Other> Activity\n");
                userInput = scanner.nextLine();
                if ("home".equals(userInput.toLowerCase()) || "1".equals(userInput.toLowerCase())) {
                    myPlanner.setHomeActivity(myPlanner.createHomeActivity());
                }
                if ("school".equals(userInput.toLowerCase()) || "2".equals(userInput.toLowerCase())) {
                    myPlanner.setSchoolActivity(myPlanner.createSchoolActivity());
                }
                if ("other".equals(userInput.toLowerCase()) || "3".equals(userInput.toLowerCase())) {
                    myPlanner.setOtherActivity(myPlanner.createOtherActivity());
                }
            } else if ("search".equals(userInput.toLowerCase()) || "2".equals(userInput.toLowerCase())) {
                do {
                    System.out.print("\n1. Home Activity\n");
                    System.out.print("2. School Activity\n");
                    System.out.print("3. Other Activity\n");
                    userInputInt = myPlanner.getIntFromUser();
                } while (userInputInt < 1 && userInputInt > 3);

                System.out.print("Enter one title keyword or full title: ");
                titleKeywords = scanner.nextLine();
                System.out.print("Enter approximate start hour (HH): ");
                startHour = myPlanner.getIntFromUser();
                System.out.print("Enter approximate start minute (MM): ");
                startMinute = myPlanner.getIntFromUser();
                System.out.print("Enter approximate end hour (HH): ");
                endHour = myPlanner.getIntFromUser();
                System.out.print("Enter approximate end minute (MM): ");
                endMinute = myPlanner.getIntFromUser();
                myPlanner.searchPlanner(titleKeywords, startHour, startMinute, endHour, endMinute, userInputInt);
            } else if ("print".equals(userInput.toLowerCase()) || "3".equals(userInput.toLowerCase())) {
                myPlanner.printPlanner();
            }
            mainMenu();
            userInput = scanner.nextLine();
        }

    }

    public static void mainMenu() {
        System.out.print("Welcome to the Day Planner\n");
        System.out.print("--------------------------\n");
        System.out.print("1. <Add> Activity        -\n");
        System.out.print("2. <Search> Activity     -\n");
        System.out.print("3. <Print> Planner       -\n");
        System.out.print("4. <Quit>                -\n");
        System.out.print("--------------------------\n");
        System.out.print("Command(1 2 3 or keyword): ");
    }

}
