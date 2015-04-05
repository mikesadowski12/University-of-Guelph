/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
*/

import java.io.*;
import javax.swing.*;
import javax.swing.text.*;
import java.util.*;
import java.lang.String;
import java.awt.*;
import java.awt.event.*;
import javax.swing.JFileChooser;
import java.io.File;
import javax.swing.event.*;
import javax.swing.filechooser.FileNameExtensionFilter;

/*SOURCES:
 * 1. http://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html#zz-5.
*/ 

public class PM_Converter
{
	static { System.loadLibrary("PM_Converter"); }	
	
	/*enumerated type from assignment 1*/
	public enum param_t {INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, STRING_TYPE, LIST_TYPE };
	
	/*Pointer to the parameter manager C object*/
	private int parameterManager;/*See citation #1*/
	
	/*All the native functions to manage the parameter manager*/
	public native void PM_create_J();
	public native int PM_destroy_J();
	public native int PM_manage_J(String name, char ptype, int required);
	public native int PM_parseFrom_J(String name, char comment);
	public native int PM_hasValue_J(String name);
	public native void PM_getValue_J(String name);
	
	public PM_Converter()
	{
		PM_create_J();
	}
	
	public static void main(String[] args)
	{
		PM_Converter cm = new PM_Converter();
		cm.PM_manage_J("name", 's', 1);
		cm.PM_manage_J("information", 's', 0);
		cm.PM_manage_J("hp", 'i', 1);
		cm.PM_manage_J("mp", 'i', 0);
		cm.PM_manage_J("skills", 'l', 1);
		cm.PM_manage_J("is_boss", 'l', 0);
		cm.PM_manage_J("kill_ratio", 'l', 1);
	}	
	
}
