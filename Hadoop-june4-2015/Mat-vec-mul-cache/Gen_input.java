import java.io.*;
import java.lang.*;
import java.util.*;
class Gen_input
{
	public static void main(String args[])
	{
		int Matrix_rows,Matrix_cols,Vector_size;
		if(args.length!=3){
			System.out.println("provide sufficient arguments <Matrix rows> <Matrix cols> <Vector size>");
			System.exit(-1);
		}	
		Matrix_rows = Integer.parseInt(args[0]);
		Matrix_cols = Integer.parseInt(args[1]);

		Vector_size = Integer.parseInt(args[2]);

		if(Matrix_cols != Vector_size)
		{
			System.out.println("multiplication not possible");
			System.exit(-1);
		}

		BufferedWriter bw = null;
                try {
              		 String mycontent;
			 File file = new File("Input-matrix.txt");

	 		 if (!file.exists()) {
	    		 file.createNewFile();
	  		}
	
			  FileWriter fw = new FileWriter(file);
			  bw = new BufferedWriter(fw);
       		 for(int i=0;i<Matrix_rows;i++)
	{
		for(int j=0;j<Matrix_cols;j++)
		{
			mycontent=i+","+j+","+(double)(Math.random()*100.0)+"\n";
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
                BufferedWriter b = null;
                try {
                         String mycontent;
                         File file1 = new File("Input-vector.txt");

                         if (!file1.exists()) {
                         file1.createNewFile();
                        }

                          FileWriter f = new FileWriter(file1);
                          b = new BufferedWriter(f);
                 for(int i=0;i<Vector_size;i++)
        {
                        mycontent=i+","+(double)(Math.random()*100.0)+"\n";
                        b.write(mycontent);
          //      }
        }

      } catch (IOException ioe) {
           ioe.printStackTrace();
        }
        finally
        {
           try{
              if(b!=null)
                 b.close();
           }catch(Exception ex){
               System.out.println("Error in closing the BufferedWriter"+ex);
            }
        }

	}
}
