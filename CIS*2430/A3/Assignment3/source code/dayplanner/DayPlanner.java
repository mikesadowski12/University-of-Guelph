import java.util.ArrayList;
import java.util.Scanner;

/** DayPlanner class
 *
 * @author Fei Song
 *
 * A class that adds and searches activities.
 *
 */

public class DayPlanner {

	public static final int MAX_SIZE = 5;

	public static final String[] types = new String[]{"home", "school", "other", "h", "s", "o"};

	/**
	 * Three separate lists for home, school, and other activities and their actual sizes
	 */
	private HomeActivity[] homes = new HomeActivity[MAX_SIZE];
	private SchoolActivity[] schools = new SchoolActivity[MAX_SIZE];
	private OtherActivity[] others = new OtherActivity[MAX_SIZE];
	private int homesSize; 
	private int schoolsSize; 
	private int othersSize; 
	

	public DayPlanner() {
		homes = new HomeActivity[MAX_SIZE];
		schools = new SchoolActivity[MAX_SIZE];
		others = new OtherActivity[MAX_SIZE];
		homesSize = 0;
		schoolsSize = 0;
		othersSize = 0;
	}

	/*
	 * Create a time object for the valid input
	 */
	public Time getTime(String line) {
               	String[] tokens = line.split("[ ,\n]+");
               	if (tokens.length != 5)
			return null;
		for (int i = 0; i < 5; i++ )
		    if (!tokens[i].matches("[-+]?[0-9]+"))
			return null;
                int year = Integer.parseInt(tokens[0]);
                int month = Integer.parseInt(tokens[1]);
                int day = Integer.parseInt(tokens[2]);
                int hour = Integer.parseInt(tokens[3]);
                int minute = Integer.parseInt(tokens[4]);
		if (Time.timeOK(year, month, day, hour, minute))
			return new Time(year, month, day, hour, minute);
		else
			return null;
	}
	
	/*
	 * Add a valid home activity
	 */
	public void addHomeActivity(HomeActivity home) {
		if (homesSize == MAX_SIZE)
			System.out.println("home list is full: activity not added");
		else	
			homes[homesSize++] = home;
	}
	
	/*
	 * Add a valid school activity
	 */
	public void addSchoolActivity(SchoolActivity school) {
		if (schoolsSize == MAX_SIZE)
			System.out.println("school list is full: activity not added");
		else
			schools[schoolsSize++] = school;
	}
	
	/*
	 * Add a valid other activity
	 */
	public void addOtherActivity(OtherActivity other) {
		if (othersSize == MAX_SIZE)
			System.out.println("other list is full: activity not added");
		else
			others[othersSize++] = other;
	}
	
	/** 
	 * Create an activity from the input and add it to the appropriate list
	 */
	public void addActivity(Scanner input) {
		String type = "";
		do {
			System.out.print( "Enter an activity type (home, school, or other)> " );
			type = input.nextLine();
		} while (!matchedKeyword(type, types));
		
		System.out.print("Enter a title> ");
		String title = input.nextLine();
		
		Time startingTime = null;
               	do {
			System.out.print( "Enter a starting time (year, month, day, hour, minute)> " );
			startingTime = getTime( input.nextLine() );
		} while (startingTime == null);

		Time endingTime = null;
               	do {
			System.out.print( "Enter an ending time (year, month, day, hour, minute)> " );
			endingTime = getTime( input.nextLine() );
		} while (endingTime == null);

		String location = "";
		if( type.equalsIgnoreCase("other") || type.equalsIgnoreCase("o") ) {
			System.out.print( "Enter a location> " );
			location = input.nextLine();
		}
		
		System.out.print( "Enter a line of comment> " );
		String comment = input.nextLine();
		
		if (type.equalsIgnoreCase("home") || type.equalsIgnoreCase("h"))
			addHomeActivity(new HomeActivity(title, startingTime, endingTime, comment));
		else if (type.equalsIgnoreCase("school") || type.equalsIgnoreCase("s"))
			addSchoolActivity(new SchoolActivity(title, startingTime, endingTime, comment));
		else
			addOtherActivity(new OtherActivity(title, startingTime, endingTime, location, comment));
	}

	/* 
	 * Check if a keyword is on a list of tokens
	 */
	private boolean matchedKeyword(String keyword, String[] tokens) {
		for (int i = 0; i < tokens.length; i++) 
			if (keyword.equalsIgnoreCase(tokens[i]))
				return true;
		return false;
	}

	/*
	 * Check if all keywords are in a string 
	 */
	private boolean matchedKeywords(String[] keywords, String title) {
		String[] tokens = title.split( "[ ,\n]+" );
		for (int i = 0; i < keywords.length; i++) 
			if (!matchedKeyword(keywords[i], tokens))
				return false;
		return true;
	}

	/*
	 * Search for all home activities that satisfy a search request
	 */
	public HomeActivity[] searchHomeActivities(Time startingTime, Time endingTime, String[] keywords) {
                HomeActivity[] matches = new HomeActivity[MAX_SIZE];
                int x = 0;
                
		for (int i = 0; i < homesSize; i++) 
			if ((startingTime == null || homes[i].getStartingTime().compareTo(startingTime) >= 0) &&
			    (endingTime == null || homes[i].getEndingTime().compareTo(endingTime) <= 0) &&
			    (keywords == null || matchedKeywords(keywords, homes[i].getTitle())))
				matches[x++] = new HomeActivity(homes[i]);
                return matches;
	}

	/*
	 * Search for all school activities that satisfy a search request
	 */
	public SchoolActivity[] searchSchoolActivities(Time startingTime, Time endingTime, String[] keywords) {
                SchoolActivity[] matches = new SchoolActivity[MAX_SIZE];
                int x = 0;
                
		for (int i = 0; i < schoolsSize; i++) 
			if ((startingTime == null || schools[i].getStartingTime().compareTo(startingTime) >= 0) &&
			    (endingTime == null || schools[i].getEndingTime().compareTo(endingTime) <= 0) &&
			    (keywords == null || matchedKeywords(keywords, schools[i].getTitle())))
				matches[x++] = schools[i]; 	
                return matches;
	}

	/*
	 * Search for all other activities that satisfy a search request
	 */
	public OtherActivity[] searchOtherActivities(Time startingTime, Time endingTime, String[] keywords) {
                OtherActivity[] matches = null;
                int x = 0;
                
		for (int i = 0; i < othersSize; i++) 
			if ((startingTime == null || others[i].getStartingTime().compareTo(startingTime) >= 0) &&
			    (endingTime == null || others[i].getEndingTime().compareTo(endingTime) <= 0) &&
			    (keywords == null || matchedKeywords(keywords, others[i].getTitle())))
				matches[x++] = others[i]; 
                return matches;
	}

	/**
	 * Gather a search request and find the matched activites in the related list(s)
	 */ 
	public void searchActivities(Scanner input) {
		String type = "";
		do {
			System.out.print("Enter an activity type (home, school, or other)> ");
			type = input.nextLine();
		} while (!type.isEmpty() && !matchedKeyword(type, types));
		
		Time startingTime = null;
		do {
			System.out.print("Enter a starting time (year, month, day, hour, minute)> ");
			String line = input.nextLine();
			if (line.isEmpty()) 
				break;
			else
				startingTime = getTime(line);
		} while (startingTime == null);

		Time endingTime = null;
		do {
			System.out.print("Enter an ending time (year, month, day, hour, minute)> ");
			String line = input.nextLine();
			if (line.isEmpty()) 
				break;
			 else
				endingTime = getTime(line);
		} while (endingTime == null);

 		System.out.print("Enter title keywords: ");
		String[] keywords = null;
		String line = input.nextLine();
		if (!line.isEmpty())
			keywords = line.split("[ ,\n]+");

		// search for matched activities
		System.out.println("Matched activities: ");
		if (type.isEmpty() || type.equalsIgnoreCase("home") || type.equalsIgnoreCase("h"))
			searchHomeActivities(startingTime, endingTime, keywords);

		if (type.isEmpty() || type.equalsIgnoreCase("school") || type.equalsIgnoreCase("s"))
			searchSchoolActivities(startingTime, endingTime, keywords);

		if (type.isEmpty() || type.equalsIgnoreCase("other") || type.equalsIgnoreCase("o"))
			searchOtherActivities(startingTime, endingTime, keywords);
	}
	
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		DayPlanner planner = new DayPlanner();
		String command = "";
		do {
			System.out.print("Enter add, search, or quit> ");
			command = input.nextLine();
			if (command.equalsIgnoreCase("add") || command.equalsIgnoreCase("a"))
				planner.addActivity(input);
			else if (command.equalsIgnoreCase("search") || command.equalsIgnoreCase("s"))
				planner.searchActivities(input);			
		} while (!command.equalsIgnoreCase("quit") && !command.equalsIgnoreCase("q"));
	}
}
