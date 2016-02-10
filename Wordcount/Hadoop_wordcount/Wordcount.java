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
public class Wordcount
{
/*_______________mapper class______________*/
	public static class Map extends Mapper<LongWritable,Text,Text,IntWritable>
	{
		IntWritable one=new IntWritable(1);
		public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
		{
				Text word =new Text();
				StringTokenizer s=new StringTokenizer(value.toString());
				while(s.hasMoreTokens())
				{
					word.set(s.nextToken());
					context.write(word,one);
				}
		}
	}
/*______________reducer class________________*/
	public static class Reduce extends Reducer<Text,IntWritable,Text,Text>
	{
		public void reduce(Text key,Iterable<IntWritable> values,Context context) throws IOException,InterruptedException
		{
			int sum=0;
			for(IntWritable val:values)
			{
				sum=sum+val.get();			
			}
			System.out.println("----------inside-----------");
			context.write(key,new Text(Integer.toString(sum)));
		}
	}
	public static void main(String args[]) throws Exception
	{
		Configuration c=new Configuration();
		if(args.length!=2)
		{
		System.out.println("provide sufficient arguments");
		System.exit(-1);
		}
		Job job=Job.getInstance(c,"Wordcount");
		job.setJarByClass(Wordcount.class);
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(IntWritable.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.addInputPath(job,new Path(args[0]));
		FileOutputFormat.setOutputPath(job,new Path(args[1]));
	//	job.submit();
		job.waitForCompletion(true);
	
	}
}
