import java.util.*;
import javax.swing.*;
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
public class Mat_vect_mul_block extends Configured implements Tool
{
	public static class Map1 extends Mapper<LongWritable,Text,Text,Text>
	{
		public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
		{
			Configuration c=context.getConfiguration();
			int Matrix_rows=Integer.parseInt(c.get("Matrix_rows"));
			int Partition_len=Integer.parseInt(c.get("Partition_len"));
			String s=value.toString();
			String input[]=s.split(",");
			Text outputkey =new Text();
			Text outputvalue =new Text();
			if(input[0].equals("B"))
			{
				for(int i=0;i<(Matrix_rows/Partition_len);i++)
				{
					outputkey.set(i+","+((Integer.parseInt(input[1]))/Partition_len));
					outputvalue.set("B,"+input[1]+","+input[2]);
			       		context.write(outputkey,outputvalue);
				}
			}
			else if(input[0].equals("A"))
			{
				outputkey.set(((Integer.parseInt(input[1]))/Partition_len)+","+((Integer.parseInt(input[2]))/Partition_len));
				outputvalue.set("A,"+input[1]+","+input[2]+","+input[3]);
				context.write(outputkey,outputvalue);
                        }

                }
        }
        public static class Reduce1 extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
			Configuration conf=context.getConfiguration();
                        String s[],skey[];
			skey=key.toString().split(",");
			int Matrix_rows=Integer.parseInt(conf.get("Matrix_rows"));
			int Partition_len=Integer.parseInt(conf.get("Partition_len"));
			int size=Partition_len;
			double Matrix[][];
			double Vector[];
			Matrix=new double[size][size];
			Vector=new double[size];
		//	context.write(null,key);
                        for(Text value :values)
                        {
                                s=value.toString().split(",");
                                if(s[0].equals("A"))
                                        {
						Matrix[(Integer.parseInt(s[1]))%Partition_len][(Integer.parseInt(s[2]))%Partition_len]=Double.parseDouble(s[3]);
					}
				else
					{		
						Vector[(Integer.parseInt(s[1]))%Partition_len]=Double.parseDouble(s[2]);
					}
			}
			double result=0.0;
				for(int i=0;i<size;i++)
				{
					result=0.0;
					for(int j=0;j<size;j++){
					result	=result+(Matrix[i][j]*Vector[j]);
					}
					context.write(null,new Text(skey[0]+","+Integer.toString(i)+","+Double.toString(result)));
				}
		}	
	}
	 public static class Map2 extends Mapper<LongWritable,Text,Text,Text>
        {
                public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
                {
                        Configuration c=context.getConfiguration();
                        String s=value.toString();
                        String input[]=s.split(",");
                        Text outputkey =new Text();
                        Text outputvalue =new Text();
			outputkey.set(input[0]);
			outputvalue.set(input[1]+","+input[2]);
			context.write(outputkey,outputvalue);
                }
        }
        public static class Reduce2 extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
                        String s[];
			Configuration conf=context.getConfiguration();
			int Matrix_rows=Integer.parseInt(conf.get("Matrix_rows"));
			int Partition_len=Integer.parseInt(conf.get("Partition_len"));
			int size=Partition_len;
                        double Result[]=new double[size];
			for(int i=0;i<size;i++)
			Result[i]=0.0;
		//	context.write(null,key);
                        for(Text value :values)
                        {
                                s=value.toString().split(",");
				Result[Integer.parseInt(s[0])]	+=Double.parseDouble(s[1]);
                        }
			for(int i=0;i<size;i++)
                         context.write(null, new Text((((Integer.parseInt(key.toString()))*Partition_len)+i) + "," + Double.toString(Result[i])));
                }
        }
                                                                                  	
	public int run(String args[]) throws Exception
	{
	Configuration conf=getConf();
	conf.set("Matrix_rows",args[3]);
	conf.set("Partition_len", args[4]);

        Job job = Job.getInstance(conf, "Mat_vect_mul_block");
        job.setJarByClass(Mat_vect_mul_block.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
 
        job.setMapperClass(Map1.class);
        job.setReducerClass(Reduce1.class);
 
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);
 
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
 
	job.waitForCompletion(true);

        Job job2 = Job.getInstance(conf, "Mat_vect_mul_block");
        job2.setJarByClass(Mat_vect_mul_block.class);
        job2.setOutputKeyClass(Text.class);
        job2.setOutputValueClass(Text.class);
 
        job2.setMapperClass(Map2.class);
        job2.setReducerClass(Reduce2.class);
 
        job2.setInputFormatClass(TextInputFormat.class);
        job2.setOutputFormatClass(TextOutputFormat.class);
 
        FileInputFormat.addInputPath(job2, new Path(args[1]));
        FileOutputFormat.setOutputPath(job2, new Path(args[2]));
 
	job2.waitForCompletion(true);
	return 0;
	}
	public static void main(String args[]) throws Exception
	{
	if(args.length!=5)
	{
		System.out.println("provide sufficient arguments<input file path> <intermediate file path> <output file path> <Matrix_rows> <Partition length>");
		System.exit(-1);
	}
	int res=ToolRunner.run(new Configuration(), new Mat_vect_mul_block(),args);
	System.exit(res);
	
	}
}
