/**
 * Time class
 *
 * @author Fei Song
 *
 * A class for representing and comparing different times.
 *
 */
public class Time {

    private int year;
    private int month;
    private int day;
    private int hour;
    private int minute;

    private class IncorrectTimeException extends Exception {
    }

    /**
     * Create a time object with all the requirement elements
     */
    public Time(int year, int month, int day, int hour, int minute){
        if (timeOK(year, month, day, hour, minute)) {
            this.year = year;
            this.month = month;
            this.day = day;
            this.hour = hour;
            this.minute = minute;
        } else {
            //throw new IncorrectTimeException();
        }
    }

    /**
     * Create a time object with no arguments
     */
    public Time() {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
    }

    /**
     * Set a new value for year
     */
    public void setYear(int year) throws IncorrectTimeException {

        if (year >= 0) {
            this.year = year;
        } else {
            throw new IncorrectTimeException();
        }
    }

    /**
     * Set a new value for month
     */
    public void setMonth(int month) throws IncorrectTimeException {
        if (month >= 0 && month <= 12) {
            this.month = month;
        } else {
            throw new IncorrectTimeException();
        }
    }

    /**
     * Set a new value for day
     */
    public void setDay(int day) throws IncorrectTimeException {
        if (day >= 0 && day <= 31) {
            this.day = day;
        } else {
            throw new IncorrectTimeException();
        }
    }

    /**
     * Set a new value for hour
     */
    public void setHour(int hour) throws IncorrectTimeException {
        if (hour >= 0 && hour <= 23) {
            this.hour = hour;
        } else {
            throw new IncorrectTimeException();
        }
    }

    /**
     * Set a new value for minute
     */
    public void setMinute(int minute) throws IncorrectTimeException {
        if (minute >= 0 && minute <= 59) {
            this.minute = minute;
        } else {
            throw new IncorrectTimeException();
        }
    }

    /**
     * Check for equality with a given time object
     */
    @Override public boolean equals(Object other) {
        boolean result = false;
        if (other instanceof Time) {
            Time that = (Time) other;
            result = year == that.year
                    && month == that.month
                    && day == that.day
                    && hour == that.hour
                    && minute == that.minute;
        }
        return result;
    }
    /**
     * Compare two time objects for ordering
     */
    public int compareTo(Time other) {
        if (year < other.year) {
            return -1;
        } else if (year > other.year) {
            return 1;
        } else if (month < other.month) {
            return -1;
        } else if (month > other.month) {
            return 1;
        } else if (day < other.day) {
            return -1;
        } else if (day > other.day) {
            return 1;
        } else if (hour < other.hour) {
            return -1;
        } else if (hour > other.hour) {
            return 1;
        } else if (minute < other.minute) {
            return -1;
        } else if (minute > other.minute) {
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * Get the value for year
     */
    public int getYear() {
        return year;
    }

    /**
     * Get the value for month
     */
    public int getMonth() {
        return month;
    }

    /**
     * Get the value for day
     */
    public int getDay() {
        return day;
    }

    /**
     * Get the value for hour
     */
    public int getHour() {
        return hour;
    }

    /**
     * Get the value for minute
     */
    public int getMinute() {
        return minute;
    }

    /**
     * Show the content of a time object in a string
     */
    public String toString() {
        return hour + ":" + minute + ", " + month + "/" + day + "/" + year;
    }

    /**
     * Validate all the fields for a time object
     */
    static public boolean timeOK(int year, int month, int day, int hour, int minute) {
        return (year >= 0) && (month >= 0) && (month <= 12) && (day >= 0) && (day <= 31)
                && (hour >= 0) && (hour <= 23) && (minute >= 0) && (minute <= 59);
    }
/*
    public static void main(String[] args) {
        Time startingTime = null;
        if (Time.timeOK(2014, 10, 22, 12, 30)) {
            startingTime = new Time(2014, 10, 22, 12, 30);
        }

        Time endingTime = null;
        if (Time.timeOK(2014, 10, 22, 13, 20)) {
            endingTime = new Time(2014, 10, 22, 13, 20);
        }

        if (startingTime != null && endingTime != null) {
            int result = startingTime.compareTo(endingTime);
            if (result < 0) {
                System.out.println(startingTime + " precedes " + endingTime);
            } else if (result > 0) {
                System.out.println(startingTime + " follows " + endingTime);
            } else {
                System.out.println(startingTime + " equals " + endingTime);
            }
        }
    }
    */
}
