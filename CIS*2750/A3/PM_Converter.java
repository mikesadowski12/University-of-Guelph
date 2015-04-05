/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
*/

/* SOURCES: 1. https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html#zz-5.
*/ 

public class PM_Converter
{
	static { System.loadLibrary("PM_Converter"); }
	
	/*Pointer to the parameter manager C object*/
	long parameters;/*See citation #1*/
		
	/*All the native functions to manage the parameter manager*/
	public native void PM_create_J(long parameters);
	public native int PM_destroy_J(long parameters);
	public native int PM_manage_J(String name, char ptype, int required, long parameters);
	public native int PM_parseFrom_J(String name, char comment, long parameters);
	public native int PM_hasValue_J(String name, long parameters);
	public native String[] PM_getValue_J(String name, long parameters);
	
	public static void main(String[] args)
	{
		PM_Converter pm = new PM_Converter();
		String[] test;
		
		pm.PM_create_J(pm.parameters);
		
		pm.PM_manage_J("name",'s',1,pm.parameters);
		pm.PM_manage_J("id",'i',1,pm.parameters);
		pm.PM_manage_J("regstat",'b',0,pm.parameters);
		pm.PM_manage_J("marks",'l',0,pm.parameters);
		pm.PM_manage_J("average",'f',0,pm.parameters);		
		System.out.println(pm.PM_parseFrom_J("example.txt",'#',pm.parameters));
		
		//System.out.println(pm.PM_hasValue_J("name", pm.parameters));		
		//System.out.println(pm.PM_hasValue_J("id", pm.parameters));	
		//System.out.println(pm.PM_hasValue_J("regstat", pm.parameters));		
		//System.out.println(pm.PM_hasValue_J("marks", pm.parameters));	
		//System.out.println(pm.PM_hasValue_J("average", pm.parameters));	
				
		System.out.println(pm.PM_getValue_J("name",pm.parameters)[0]);
		System.out.println(pm.PM_getValue_J("id",pm.parameters)[0]);
		System.out.println(pm.PM_getValue_J("regstat",pm.parameters)[0]);
		System.out.println(pm.PM_getValue_J("average",pm.parameters)[0]);
		
		test = pm.PM_getValue_J("marks", pm.parameters);
		for(int i = 0; i < test.length;i++)
		{
			System.out.println(test[i]);
		}
		pm.PM_destroy_J(pm.parameters);					
	}		
}	
