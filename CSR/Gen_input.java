import java.io.*;
import java.util.*;
class Sparse
{
	public  int Mat_rows,Sparsity;
	public  double value[];
	public  int col_index[], row_ptr[];
	void init(int Mat_rows,int Sparsity)
	{
		this.Mat_rows=Mat_rows;
		this.Sparsity=Sparsity;
		value	=	new double[Mat_rows * Sparsity];
		col_index = 	new int[Mat_rows * Sparsity];
		row_ptr	=	new int[Mat_rows+1];
		row_ptr[0]	=	0;
	}
	void gen_Csr()
	{
		int Sparse_count	=	0;
		int count		=	0;
		for(int i=0 ; i < Mat_rows ; i++ )
		{
			Sparse_count	=	0;
			for(int j = 0; j< Mat_rows ; j++)
			{
				int flag =(int) (Math.random()* 100) % 2;
				int go  = (Sparsity - Sparse_count) - (Mat_rows-j);
				if((Sparse_count < Sparsity && flag == 0) || go == 0)
				{
					value[count]	=	Math.random()*100 ;
					col_index[count]	=	j;
					Sparse_count++;	
					count ++;
				}
			}
			row_ptr[i+1]	=	count;
		}
/*		for(int i=0; i<Mat_rows * Sparsity ; i++)
			System.out.println(value[i] + " " + col_index[i]);
		for(int i=0;i<= Mat_rows ; i++)
			System.out.println(row_ptr[i]);*/
	}
	void to_File()
	{
		 int index=0,val_ind=0;
                BufferedWriter bw = null,b=null;
      try {
         String mycontent;
         File file = new File("Input-mat-vect-csr.txt");

          if (!file.exists()) {
             file.createNewFile();
          }

          FileWriter fw = new FileWriter(file);
          bw = new BufferedWriter(fw);
         // bw.write(mycontent);
         for(int i=0;i<Mat_rows;i++)
        {
                for(int j=0;(j<row_ptr[i+1]-row_ptr[i]);j++)
                {
                        mycontent=index+","+col_index[val_ind]+","+value[val_ind]+"\n";
                        bw.write(mycontent);
                        val_ind++;
                }
                index++;

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
        try{
        File f=new File("Input-vector.txt");
        if(!f.exists())
        f.createNewFile();
        b=new BufferedWriter(new FileWriter(f));
        String s=null;
        for(int i=0;i<Mat_rows;i++)
        {
                s=i+","+(Math.random() * 100)+"\n";
                b.write(s);
        }
        }
        catch(Exception e){ }
        finally{
        try{
        if(b!=null)
                b.close();
        }catch(Exception a){ }
        }


	}	
}
class Gen_input
{
	public static void main(String args[])
	{
		Sparse s	=	new Sparse();
		if(args.length	!=	2)
		{
			System.out.println("provide sufficient arguments <no of rows> <sparsity: n of non zeros per row> ");
			System.exit(-1);
		}
		int Mat_rows	=	Integer.parseInt(args[0]);
		int Sparsity	=	Integer.parseInt(args[1]);
		s.init(Mat_rows,Sparsity);
		s.gen_Csr();
		s.to_File();
	}
}	
