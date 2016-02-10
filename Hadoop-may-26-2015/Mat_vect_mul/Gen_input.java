import java.io.*;
import java.util.*;
class Gen_input
{
	public static void main(String args[])
	{
		int m,n,p;
		if(args.length!=3)
		{
			System.out.println("provide sufficient arguments");
			System.exit(-1);
		}	
		m=Integer.parseInt(args[0]);
		n=Integer.parseInt(args[1]);
		p=Integer.parseInt(args[2]);
		BufferedWriter bw = null;
      try {
	 String mycontent;
	 File file = new File("Input-mat-vect-mul.txt");

	  if (!file.exists()) {
	     file.createNewFile();
	  }

	  FileWriter fw = new FileWriter(file);
	  bw = new BufferedWriter(fw);
	 // bw.write(mycontent);
       	 for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			mycontent="A,"+i+","+j+","+(float)((i+100)*(j+100)/20)+"\n";
			bw.write(mycontent);
		}
	}
  
       	 for(int i=0;i<n;i++)
	{
		for(int j=0;j<p;j++)
		{
			mycontent="B,"+i+","+j+","+(float)((i+100)*(j+100)/30)+"\n";
			bw.write(mycontent);
		}
	}

      } catch (IOException ioe) {
	   ioe.printStackTrace();
	}
	finally
	{ 
	   try{
	      if(bw!=null)
		 bw.close();
	   }catch(Exception ex){
	       System.out.println("Error in closing the BufferedWriter"+ex);
	    }
	}
	}
}
