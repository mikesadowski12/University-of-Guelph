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
public class Time {

    private int year;
    private String month;
    private int day;
    private int hour;
    private int minute;

    /* CONSTRUCTORS */
    public Time() {
        year = 0000;
        month = "";
        day = 0;
        hour = 0;
        minute = 0;

    }

    public Time(int year, String month, int day, int hour, int minute) {
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
    }

    /* ACCESSORS */
    public int getYear() {
        return year;
    }

    public String getMonth() {
        return month;
    }

    public int getDay() {
        return day;
    }

    public int getHour() {
        return hour;
    }

    public int getMinute() {
        return minute;
    }

    /* MUTATORS */
    public void setYear(int year) {
        this.year = year;
    }

    public boolean setMonth(String month) {
        if ("january".equals(month.toLowerCase()) || "february".equals(month.toLowerCase())
                || "march".equals(month.toLowerCase()) || "april".equals(month.toLowerCase())
                || "may".equals(month.toLowerCase()) || "june".equals(month.toLowerCase())
                || "july".equals(month.toLowerCase()) || "august".equals(month.toLowerCase())
                || "september".equals(month.toLowerCase()) || "october".equals(month.toLowerCase())
                || "november".equals(month.toLowerCase()) || "december".equals(month.toLowerCase())) {
            this.month = month;
            return true;
        }
        return false;

    }

    public boolean setDay(int day) {
        if (day <= 31 && day > 0) {
            this.day = day;
            return true;
        }
        return false;
    }

    public boolean setHour(int hour) {
        if (hour <= 12 && hour > 0) {
            this.hour = hour;
            return true;
        }
        return false;
    }

    public boolean setMinute(int minute) {
        if (minute <= 60 && minute >= 0) {
            this.minute = minute;
            return true;
        }
        return false;
    }

    /* EQUALS AND TOSTRING */
    public boolean timeEquals(Time other) {
        if (other == null) {
            return false;
        } else {
            return this.year == other.year
                    && this.month == other.month
                    && this.day == other.day
                    && this.day == other.day
                    && this.hour == other.hour
                    && this.minute == other.minute;
        }
    }

    public String toString() {
        return month + day + year + hour + ":" + minute;
    }

}
