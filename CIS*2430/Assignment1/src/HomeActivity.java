/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment1;

/**
 *
 * @author michaelsadowski
 */
public class HomeActivity {

    private String title;
    private Time startTime;
    private Time endTime;
    private String comment;

    
    /* CONSTRUCTORS */
    public HomeActivity() {
        title = "";
        startTime = new Time();
        endTime = new Time();
        comment = "";
    }

    public HomeActivity(String title, Time startTime, Time endTime, String comment) {
        this.title = title;
        this.startTime = startTime;
        this.endTime = endTime;
        this.comment = comment;
    }    
    /* ACCESSORS */
    public String getTitle() {
        return title;
    }

    public Time getStartTime() {
        return startTime;
    }

    public Time getEndTime() {
        return endTime;
    }

    public String getComment() {
        return comment;
    }

    /* MUTATORS */
    public void setTitle(String title) {
        this.title = title;
    }

    public void setStartTime(Time startTime) {
        this.startTime = startTime;
    }

    public void setEndTime(Time endTime) {
        this.endTime = endTime;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    /* EQUALS AND TOSTRING */
    public boolean homeActivityEquals(HomeActivity other) {
        if (other == null) {
            return false;
        } else {
            return this.title.equals(other.title)
                    && this.startTime == other.startTime
                    && this.endTime == other.endTime
                    && this.comment.equals(other.comment);
        }
    }

    public String toString() {        
        return startTime.getMonth() + " " + startTime.getDay() + " '"+title + "': " + startTime.getHour() + ":" + startTime.getMinute() + " TO " + endTime.getHour() + ":" + endTime.getMinute() + " (" + comment + ") AT home\n";
    }  
}
