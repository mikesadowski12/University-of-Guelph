/**
 * HomeActivity class
 *
 * @author Fei Song
 *
 * A class for representing and comparing home activities.
 *
 */
public class HomeActivity {

    private String title;       // short description of the activity
    private Time startingTime;  // starting time of the activity
    private Time endingTime;    // ending time of the activity
    private String comment;     // additional details about the activity

    /**
     * Create a home activity with all the required fields
     */
    public HomeActivity(String title, Time startingTime, Time endingTime, String comment) {
        if (valid(startingTime, endingTime)) {
            this.title = title;
            this.startingTime = startingTime;
            this.endingTime = endingTime;
            this.comment = comment;
        } else {
            System.out.println("Invalid times for HomeActivity");
            System.exit(0);
        }
    }

    public HomeActivity(HomeActivity home) {
        this(home.getTitle(), home.getStartingTime(), home.getEndingTime(), home.getComment());
    }

    /**
     * Check the validity for a potential activity
     */
    public static boolean valid(Time startingTime, Time endingTime) {
        return (startingTime != null) && (endingTime != null);
    }

    /**
     * Set a new value for title
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * Set a new value for starting time
     */
    public void setStartingTime(Time startingTime) {
        if (startingTime == null) {
            System.out.println("Invalid starting time");
            System.exit(0);
        } else {
            this.startingTime = startingTime;
        }
    }

    /**
     * Set a new value for ending time
     */
    public void setEndingTime(Time endingTime) {
        if (endingTime == null) {
            System.out.println("Invalid ending time");
            System.exit(0);
        }
        this.endingTime = endingTime;
    }

    /**
     * Set a new value for comment
     */
    public void setComment(String comment) {
        this.comment = comment;
    }

    /**
     * Get the value of title
     */
    public String getTitle() {
        return title;
    }

    /**
     * Get the value of starting time
     */
    public Time getStartingTime() {
        return startingTime;
    }

    /**
     * Get the value of ending time
     */
    public Time getEndingTime() {
        return endingTime;
    }

    /**
     * Get the value of comment
     */
    public String getComment() {
        return comment;
    }

    /**
     * Check for the equality of two home activities
     */
    @Override
    public boolean equals(Object other) {
        boolean result = false;
        if (other instanceof HomeActivity) {
            HomeActivity that = (HomeActivity) other;
            result = title.equals(that.title)
                    && startingTime.equals(that.startingTime)
                    && endingTime.equals(that.endingTime)
                    && comment.equals(that.comment);
        }
        return result;
    }

    /**
     * Show the content of a home activity in a string
     */
    public String toString() {
        return title + ": " + startingTime + " to " + endingTime + ", " + comment;
    }
    /*	
     public static void main(String[] args) {
     Time startingTime = new Time(2009, 10, 22, 12, 30);
     Time endingTime = new Time(2009, 10, 22, 13, 20);
     HomeActivity activity = new HomeActivity("Call friends", startingTime, endingTime, "");
     System.out.println("Home Activity: " + activity);
     }
     */
}
