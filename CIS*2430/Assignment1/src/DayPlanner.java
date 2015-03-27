/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment1;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author michaelsadowski
 */
public class DayPlanner {

    private HomeActivity[] homeActivities;
    private SchoolActivity[] schoolActivities;
    private OtherActivity[] otherActivities;
    private int homeActivitiesCount;
    private int schoolActivitiesCount;
    private int otherActivitiesCount;

    public DayPlanner() {
        int i = 0;

        homeActivities = new HomeActivity[100];
        schoolActivities = new SchoolActivity[100];
        otherActivities = new OtherActivity[100];

        for (i = 0; i < homeActivities.length; i++) {
            homeActivities[i] = new HomeActivity();
        }
        for (i = 0; i < schoolActivities.length; i++) {
            schoolActivities[i] = new SchoolActivity();
        }
        for (i = 0; i < otherActivities.length; i++) {
            otherActivities[i] = new OtherActivity();
        }

        homeActivitiesCount = 0;
        schoolActivitiesCount = 0;
        otherActivitiesCount = 0;

    }

    /* ACCESSORS */
    public HomeActivity[] getHomeActivity() {
        return homeActivities;
    }

    public SchoolActivity[] getSchoolActivity() {
        return schoolActivities;
    }

    public OtherActivity[] getOtherActivity() {
        return otherActivities;
    }

    public int getHomeActivityCount() {
        return homeActivitiesCount;
    }

    public int getSchoolActivityCount() {
        return schoolActivitiesCount;
    }

    public int getOtherActivityCount() {
        return otherActivitiesCount;
    }
    /* MUTATORS - Add objects to the arrays in this class*/

    public void setHomeActivity(HomeActivity newActivity) {
        this.homeActivities[homeActivitiesCount++] = newActivity;
    }

    public void setSchoolActivity(SchoolActivity newActivity) {
        this.schoolActivities[schoolActivitiesCount++] = newActivity;
    }

    public void setOtherActivity(OtherActivity newActivity) {
        this.otherActivities[otherActivitiesCount++] = newActivity;
    }

    /* EQUALS */
    public boolean dayPlannerEquals(DayPlanner other) {
        if (other == null) {
            return false;
        } else {
            return this.homeActivities == other.homeActivities
                    && this.schoolActivities == other.schoolActivities
                    && this.otherActivities == other.otherActivities;
        }
    }

    /* PRINT PLANNER */
    public void printPlanner() {
        int i = 0;

        for (i = 0; i < homeActivities.length; i++) {
            if (!homeActivities[i].getTitle().equals("")) {
                System.out.print(homeActivities[i].toString());
            }
        }
        for (i = 0; i < schoolActivities.length; i++) {
            if (!schoolActivities[i].getTitle().equals("")) {
                System.out.print(schoolActivities[i].toString());
            }
        }
        for (i = 0; i < otherActivities.length; i++) {
            if (!otherActivities[i].getTitle().equals("")) {
                System.out.print(otherActivities[i].toString());
            }
        }
    }
    /*searches title for keywords, then sees if the times provided fall between the times of an object*/

    public void searchPlanner(String titleKeywords, int startTimeHour, int startTimeMinute, int endTimeHour, int endTimeMinute, int activityType) {
        int i = 0;

        /*check for keywords in the title, see if any that are matches fall between the given times*/
        if (activityType == 1) {
            for (i = 0; i < homeActivities.length; i++) {
                if (homeActivities[i].getTitle().toLowerCase().contains(titleKeywords.toLowerCase())) {
                    if (startTimeHour >= homeActivities[i].getStartTime().getHour()
                            && startTimeMinute >= homeActivities[i].getStartTime().getMinute()
                            && endTimeHour <= homeActivities[i].getEndTime().getHour()
                            && endTimeMinute <= homeActivities[i].getEndTime().getMinute()) {
                        System.out.print("\n" + homeActivities[i].toString() + "\n\n");
                    }
                }
            }
        }
        if (activityType == 2) {
            for (i = 0; i < schoolActivities.length; i++) {
                if (schoolActivities[i].getTitle().toLowerCase().contains(titleKeywords.toLowerCase())) {
                    if (startTimeHour >= schoolActivities[i].getStartTime().getHour()
                            && startTimeMinute >= schoolActivities[i].getStartTime().getMinute()
                            && endTimeHour <= schoolActivities[i].getEndTime().getHour()
                            && endTimeMinute <= schoolActivities[i].getEndTime().getMinute()) {
                        System.out.print("\n" + schoolActivities[i].toString() + "\n\n");
                    }
                }
            }
        }
        if (activityType == 3) {
            for (i = 0; i < otherActivities.length; i++) {
                if (otherActivities[i].getTitle().toLowerCase().contains(titleKeywords.toLowerCase())) {
                    if (startTimeHour >= otherActivities[i].getStartTime().getHour()
                            && startTimeMinute >= otherActivities[i].getStartTime().getMinute()
                            && endTimeHour <= otherActivities[i].getEndTime().getHour()
                            && endTimeMinute <= otherActivities[i].getEndTime().getMinute()) {
                        System.out.print("\n" + otherActivities[i].toString() + "\n\n");
                    }
                }
            }
        }
    }
    /* CREATE ACTIVITY */

    public HomeActivity createHomeActivity() {
        String[] titleMonthCommentLocation = new String[4]; /*[0] = title  [1] = month  [2] = comment  [3] = location*/

        Scanner scanner = new Scanner(System.in);
        Time[] startEndTime = new Time[2];/*[0] = startTime  [1] = endTime*/

        startEndTime[0] = new Time();
        startEndTime[1] = new Time();

        /*get all the information*/
        titleMonthCommentLocation = getTitleMonthCommentsLocationFromUser(0);//*get title, month comment and location if needed*/

        startEndTime = getTimeInfoFromUser();

        while (!startEndTime[0].setMonth(titleMonthCommentLocation[1])) {
            System.out.print("Enter valid month (ie January/November): ");
            titleMonthCommentLocation[1] = scanner.nextLine();
        }
        startEndTime[0].setMonth(titleMonthCommentLocation[1]);
        startEndTime[1].setMonth(titleMonthCommentLocation[1]);

        String title = titleMonthCommentLocation[0];
        Time startTime = startEndTime[0];
        Time endTime = startEndTime[1];
        String comment = titleMonthCommentLocation[2];

        /*create object, return it*/
        HomeActivity newHomeActivity = new HomeActivity(title, startTime, endTime, comment);

        return newHomeActivity;
    }

    public SchoolActivity createSchoolActivity() {
        String[] titleMonthCommentLocation = new String[4]; /*[0] = title  [1] = month  [2] = comment  [3] = location*/

        Scanner scanner = new Scanner(System.in);
        Time[] startEndTime = new Time[2];/*[0] = startTime  [1] = endTime*/

        startEndTime[0] = new Time();
        startEndTime[1] = new Time();

        /*get all the information*/
        titleMonthCommentLocation = getTitleMonthCommentsLocationFromUser(0);//*get title, month command and location if needed*/

        startEndTime = getTimeInfoFromUser();
        while (!startEndTime[0].setMonth(titleMonthCommentLocation[1])) {
            System.out.print("Enter valid month (ie January/November): ");
            titleMonthCommentLocation[1] = scanner.nextLine();
        }

        startEndTime[0].setMonth(titleMonthCommentLocation[1]);
        startEndTime[1].setMonth(titleMonthCommentLocation[1]);

        /*create object, return it*/
        SchoolActivity schoolActivity = new SchoolActivity(titleMonthCommentLocation[0], startEndTime[0], startEndTime[1], titleMonthCommentLocation[2]);

        return schoolActivity;
    }

    public OtherActivity createOtherActivity() {
        String[] titleMonthCommentLocation = new String[4]; /*[0] = title  [1] = month  [2] = comment  [3] = location*/

        Scanner scanner = new Scanner(System.in);
        Time[] startEndTime = new Time[2];/*[0] = startTime  [1] = endTime*/

        startEndTime[0] = new Time();
        startEndTime[1] = new Time();

        /*get all the information*/
        titleMonthCommentLocation = getTitleMonthCommentsLocationFromUser(1);//*get title, month command and location if needed*/

        startEndTime = getTimeInfoFromUser();

        while (!startEndTime[0].setMonth(titleMonthCommentLocation[1])) {
            System.out.print("Enter valid month (ie January/November): ");
            titleMonthCommentLocation[1] = scanner.nextLine();
        }

        startEndTime[0].setMonth(titleMonthCommentLocation[1]);
        startEndTime[1].setMonth(titleMonthCommentLocation[1]);

        /*create object, return it*/
        OtherActivity otherActivity = new OtherActivity(titleMonthCommentLocation[0], startEndTime[0], startEndTime[1], titleMonthCommentLocation[3], titleMonthCommentLocation[2]);

        return otherActivity;
    }

    /* FUNCTIONS TO MAKE GETTING INPUT EASIER*/
    /*gets month, comment and location, return as an array*/
    public String[] getTitleMonthCommentsLocationFromUser(int inputCode) {
        Scanner scanner = new Scanner(System.in);
        String[] titleMonthCommentLocation = new String[4];/*[0] = title  [1] = month  [2] = comment  [3] = location*/

        System.out.print("Enter title: ");
        titleMonthCommentLocation[0] = scanner.nextLine();
        System.out.print("Enter comment: ");
        titleMonthCommentLocation[2] = scanner.nextLine();

        if (inputCode == 1) {/*only grab location if needed*/

            System.out.print("Enter location: ");
            titleMonthCommentLocation[3] = scanner.nextLine();
        }

        System.out.print("Enter month (ie January/November): ");
        titleMonthCommentLocation[1] = scanner.nextLine();

        return titleMonthCommentLocation;
    }
    /*makes sure a positive int is inputted and returns it*/

    public int getIntFromUser() {
        Scanner scanner = new Scanner(System.in);
        int userInput = 0;

        do {
            while (!scanner.hasNextInt()) {
                scanner.next(); // this is important!
            }
            userInput = scanner.nextInt();
        } while (userInput < 0);/*make sure it's always positive*/

        return userInput;
    }

    public Time[] getTimeInfoFromUser() {
        int year, day = 0;
        Time[] startEndTime = new Time[2];/*[0] = startTime  [1] = endTime*/

        startEndTime[0] = new Time();
        startEndTime[1] = new Time();

        do {
            System.out.print("Enter day (DD): ");/*get the day and set it to both time objects*/

        } while (startEndTime[0].setDay(getIntFromUser()) == false);
        startEndTime[0].setDay(day);
        startEndTime[1].setDay(day);

        System.out.print("Enter year (YYYY): ");/*get the year and set it to both time objects*/

        year = getIntFromUser();
        startEndTime[0].setYear(year);
        startEndTime[1].setYear(year);

        do {
            System.out.print("Enter start hour (HH): ");
        } while (startEndTime[0].setHour(getIntFromUser()) == false);

        do {
            System.out.print("Enter start minute (MM): ");
        } while (startEndTime[0].setMinute(getIntFromUser()) == false);

        do {
            System.out.print("Enter end hour (HH): ");
        } while (startEndTime[1].setHour(getIntFromUser()) == false);

        do {
            System.out.print("Enter end minute (MM): ");
        } while (startEndTime[1].setMinute(getIntFromUser()) == false);

        return startEndTime;
    }
}
