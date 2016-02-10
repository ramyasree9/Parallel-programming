
/***********************************************************************
                           June 08, 2015

 Example              : Mat-vect-mul.java

 Objective 	      : To multiply matrix and vector using DistributedCache provided by Map-Reduce framework
                        Demonstrates the usage of:
				
			     Mapper
			     Reducer
                             ToolRunner
			     Configuration
			     Job
			     DistributedCache
			     setup()
                             map()
                             reduce()
                                
 
 Input                 : The input files have one line of the following format for each element of matrix A and vector B 
			 i,j,A_ij and i,B_i

 Output                : The output file has one line of the following format for each element of the product of matrix A and vector B			       i,AB_i                            
                                                                        
 Created               : June-2015

 E-mail                : hpcfte@cdac.in

*******************************************************************************/

import java.util.*;
import java.io.*;
import java.io.IOException;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.filecache.DistributedCache;
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
public class Mat_vect_mul extends Configured implements Tool
{
	/*******************Mapper class*************************/
	public static class Map1 extends Mapper<LongWritable,Text,Text,Text>
	{
		private HashMap<Long,Double> vector  =new HashMap<Long,Double>();
		
		/* called once at the beginning of the task */
		public void setup(Context context) throws IOException,InterruptedException
		{
			BufferedReader br	=	null;
			Path[] files=DistributedCache.getLocalCacheFiles(context.getConfiguration());
			if(files != null && files.length > 0)
				 br=new BufferedReader(new FileReader(files[0].toString()));
			String line = null;

			/* reads the cached file into a hashmap */
			try{
				while((line=br.readLine())!= null){
					String input[] = line.split(",");
					vector.put(Long.valueOf(input[0]),Double.valueOf(input[1]));
				}
			}
			finally{
				br.close();
			}
		}
		public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
		{
			Configuration c	 = context.getConfiguration();
			String s	 = value.toString();
			String input[]	 = s.split(",");
			Text outputkey	 = new Text();
			Text outputvalue = new Text();
			double	result	 =	0.0;
	
 			/* multiplies matrix and vector entry with matching column value */
			
			result	=	(Double.parseDouble(input[2]))*(vector.get(Long.parseLong(input[1])));
			outputkey.set(input[0]);
			outputvalue.set(Double.toString(result));
			context.write(outputkey,outputvalue);

                }
        }
	/***********************Redcuer class***********************/
        public static class Reduce1 extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
                        String input[];
        		double result	 =	 0.0;
			
			/* adds all the values corresponding to a key */
                        for(Text value :values) {
                                result	+=	 Double.parseDouble(value.toString());
			}

			context.write(null,new Text(key+","+Double.toString(result)));
			
		}	
	}
	public int run(String args[]) throws Exception
	{
		Configuration conf=getConf();
		
		/* creates a new job with given job name */
    	 	Job job = Job.getInstance(conf, "Mat_vect_mul");	
  		job.setJarByClass(Mat_vect_mul.class);	
	
		/* adds input-vector file to the cache */
		DistributedCache.addCacheFile(new Path(args[1]).toUri(),job.getConfiguration());

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
        	FileOutputFormat.setOutputPath(job, new Path(args[2]));
        	
		/* Submit the job, then poll for progress until the job is complete */	
		boolean  succ	=	job.waitForCompletion(true);
		if (! succ) {
		      System.out.println("Job failed, exiting");
     			 return -1;
   		 }

		return 0;
	}
	/*************************Driver function*******************/
	public static void main(String args[]) throws Exception
	{
		if(args.length != 3){
			System.out.println("provide sufficient arguments <input matrix file path>  <input vector file path> <output file path>");
			System.exit(-1);
	}
		int res	=	ToolRunner.run(new Configuration(), new Mat_vect_mul(),args);
		System.exit(res);
	
	}
}
