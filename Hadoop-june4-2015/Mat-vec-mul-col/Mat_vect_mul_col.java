
/***********************************************************************
                           June 05, 2015

 Example              : Mat-vect-mul-col.java

 Objective 	      : To multiply matrix and vector by defining "n" column keys for a square real matrix
          		of size "n x n" using hadoop map reduce
                        Demonstrates the usage of:
				
			     Mapper
			     Reducer
                             ToolRunner
			     Configuration
			     Job
                             map()
                             reduce()
                                
 
 Input                 : The input file has one line of the following format for each element of matrix A and vector B 
			 A,i,j,A_ij and B,i,B_i

 Output                : The output file has one line of the following format for each element of the product of matrix A and vector B			       i,AB_i                            
                                                                        
 Created               : June-2015

 E-mail                : hpcfte@cdac.in

*******************************************************************************/

import java.util.*;
import java.io.IOException;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

/**************************Main class**********************************/
public class Mat_vect_mul_col extends Configured implements Tool
{
	/*******************Mapper class*************************/
	public static class Map1 extends Mapper<LongWritable,Text,Text,Text>
	{
		public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
		{
			Configuration c	 = context.getConfiguration();
			String s	 = value.toString();
			String input[]	 = s.split(",");
			Text outputkey	 = new Text();
			Text outputvalue = new Text();
			/* if the map function reads vetcor B data,the key,value format is 
			   key	: i th index of vector B
		           value: B, value  */
			if(input[0].equals("B"))
			{
				outputkey.set(input[1]);	
				outputvalue.set("B,"+input[2]);			
			        context.write(outputkey,outputvalue);
			}
			/* if the map function reads matrix A data,the key,value format is 
			   key	: j th index of Matrix A
		           value: A, i th index of A, value  */
			else if(input[0].equals("A"))
			{
				outputkey.set(input[2]);
				outputvalue.set("A,"+input[1]+","+input[3]);
				context.write(outputkey,outputvalue);
                        }

                }
        }
	/***********************Redcuer class***********************/
        public static class Reduce1 extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
                        String input[];
                        HashMap<Integer,Double> hashA	 =	new HashMap<Integer,Double>();
			double vector	=	0.0;
			int Matrix_rows	 =	 Integer.parseInt(context.getConfiguration().get("Matrix_rows"));
        		double result	 =	 0.0;
           		double a_ij;
			
			/* stores Matrix A values in a hash map and vector value in a variable */
                        for(Text value :values) {
                                input	=	 value.toString().split(",");
                                if(input[0].equals("A"))
                                        hashA.put(Integer.parseInt(input[1]),Double.parseDouble(input[2]));
				else
					vector	=	Double.parseDouble(input[1]);
			}

			/* multiplies value of vector variable to each value of matrix in hashmap */
           		 for (int j = 0; j < Matrix_rows; j++) {
               			 a_ij = hashA.containsKey(j) ? hashA.get(j) : 0.0f;
				 result = a_ij * vector;
               			 context.write(null, new Text(String.valueOf(j) + "," + Double.toString(result)));
               		 }
			
		}	
	}
	/*************************Mapper class************************/
	 public static class Map2 extends Mapper<LongWritable,Text,Text,Text>
        {
                public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
                {
                        Configuration c	=	context.getConfiguration();
                        String s	=	value.toString();
                        String input[]	=	s.split(",");
                        Text outputkey	=	new Text();
                        Text outputvalue=	new Text();
			/* sets key	:  i th index
			        value	:  value     */
			outputkey.set(input[0]);
			outputvalue.set(input[1]);
			context.write(outputkey,outputvalue);
                }
        }
	/*************************Reducer class*************************/
        public static class Reduce2 extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
                        String s;
                        double result	=	0.0;
			
			/* adds all the values corresponding to the key */
                        for(Text value :values){
                                s	=	value.toString();
				result	+=	Double.parseDouble(s);
                        }
                         context.write(null, new Text(key.toString() + "," + Double.toString(result)));

                }
        }
	public int run(String args[]) throws Exception
	{
		Configuration conf=getConf();
		conf.set("Matrix_rows", args[3]);
		
    	 	Job job = Job.getInstance(conf, "Mat_vect_mul_col");		//creates a new job with given job name
  		job.setJarByClass(Mat_vect_mul_col.class);	
	
		/* set the key class and value class for the job output */		
 	       	job.setOutputKeyClass(Text.class);
        	job.setOutputValueClass(Text.class);
		
 		/* set mapper and reducer for the job */
        	job.setMapperClass(Map1.class);
        	job.setReducerClass(Reduce1.class);
 		
		/* set the input foramt and output format for the job */
        	job.setInputFormatClass(TextInputFormat.class);
        	job.setOutputFormatClass(TextOutputFormat.class);
 
		/* add path to the list of inputs for the map-reduce job */
        	FileInputFormat.addInputPath(job, new Path(args[0]));
		
		/* set path of the output diretcory for the map-reduce job*/
        	FileOutputFormat.setOutputPath(job, new Path(args[1]));
        	
		/* Submit the job, then poll for progress until the job is complete */	
		boolean  succ	=	job.waitForCompletion(true);
		if (! succ) {
		      System.out.println("Job failed, exiting");
     			 return -1;
   		 }

		/****************** creating another job *******************/
        	Job job2 = Job.getInstance(conf, "Mat_vect_mul_col");		
        	job2.setJarByClass(Mat_vect_mul_col.class);
        	job2.setOutputKeyClass(Text.class);
        	job2.setOutputValueClass(Text.class);
 
        	job2.setMapperClass(Map2.class);
        	job2.setReducerClass(Reduce2.class);
 
        	job2.setInputFormatClass(TextInputFormat.class);
        	job2.setOutputFormatClass(TextOutputFormat.class);
 
        	FileInputFormat.addInputPath(job2, new Path(args[1]));
        	FileOutputFormat.setOutputPath(job2, new Path(args[2]));
 
		succ	=	job2.waitForCompletion(true);
		if (! succ) {
		      System.out.println("Job failed, exiting");
     			 return -1;
   		 }

		return 0;
	}
	/*************************Driver function*******************/
	public static void main(String args[]) throws Exception
	{
		if(args.length != 4){
			System.out.println("provide sufficient arguments<input file path> <intermediate file path> <output file path> <Matrix_rows>");
			System.exit(-1);
	}
		int res	=	ToolRunner.run(new Configuration(), new Mat_vect_mul_col(),args);
		System.exit(res);
	
	}
}
