/**
 * OtherActivity class
 *
 * @author Fei Song
 *
 * A class for representing and comparing other activities.
 *
 */
public class OtherActivity {

    private String title;       // short description of the activity
    private Time startingTime;  // starting time of the activity
    private Time endingTime;    // ending time of the activity
    private String location;    // location of the activity
    private String comment;     // additional detail for the activity

    /**
     * Create an other activity with all the required fields
     */
    public OtherActivity(String title, Time startingTime, Time endingTime, String location, String comment) {
        if (valid(startingTime, endingTime)) {
            this.title = title;
            this.startingTime = startingTime;
            this.endingTime = endingTime;
            this.location = location;
            this.comment = comment;
        } else {
            System.out.println("Invalid times for OtherActivity");
            System.exit(0);
        }
    }

    public OtherActivity(OtherActivity home) {
        this(home.getTitle(), home.getStartingTime(), home.getEndingTime(), home.getLocation(),home.getComment());
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
        if (endingTime == null) {
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
        if (startingTime == null) {
            System.out.println("Invalid ending time");
            System.exit(0);
        }
        this.endingTime = endingTime;
    }

    /**
     * Set a new value for location
     */
    public void setLocation(String location) {
        this.location = location;
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
     * Get the value of location
     */
    public String getLocation() {
        return location;
    }

    /**
     * Get the value of comment
     */
    public String getComment() {
        return comment;
    }

    /**
     * Check for equality of two other activities
     */

    @Override public boolean equals(Object other) {
        boolean result = false;
        if (other instanceof OtherActivity) {
            OtherActivity that = (OtherActivity) other;
            result = title.equals(that.title)
                    && startingTime.equals(that.startingTime)
                    && endingTime.equals(that.endingTime)
                    && location.equals(that.location)
                    && comment.equals(that.comment);
        }
        return result;
    }

    /**
     * Show the content of an other activity in a string
     */
    public String toString() {
        return title + ": " + startingTime + " to " + endingTime + ", " + location + ", " + comment;
    }
/*
    public static void main(String[] args) {
        Time startingTime = new Time(2009, 10, 22, 12, 30);
        Time endingTime = new Time(2009, 10, 22, 13, 20);
        OtherActivity activity = new OtherActivity("Lunch", startingTime, endingTime, "Time Horton", "");
        System.out.println("Other Activity: " + activity);
    }
    */
}
