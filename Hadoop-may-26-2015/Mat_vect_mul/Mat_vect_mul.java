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
public class Mat_vect_mul
{
	public static class Map extends Mapper<LongWritable,Text,Text,Text>
	{
		public void map(LongWritable key,Text value,Context context) throws IOException,InterruptedException
		{
			Configuration c=context.getConfiguration();
			int m=Integer.parseInt(c.get("m"));
			int p=Integer.parseInt(c.get("p"));
			String s=value.toString();
			String input[]=s.split(",");
			Text outputkey =new Text();
			Text outputvalue =new Text();
			if(input[0].equals("B"))
			{
				for(int i=0;i<m;i++)
				{
					outputkey.set(i+","+input[2]);
					outputvalue.set("B,"+input[1]+","+input[3]);
					  context.write(outputkey,outputvalue);

				}
			}
			else
			{
				for(int k=0;k<p;k++)
				{
					outputkey.set(input[1]+","+k);
					outputvalue.set("A,"+input[2]+","+input[3]);
					  context.write(outputkey,outputvalue);

                                }
                        }
//                        context.write(outputkey,outputvalue);

                }
        }
        public static class Reduce extends Reducer<Text,Text,Text,Text>
        {
                public void reduce(Text key,Iterable<Text> values,Context context) throws IOException,InterruptedException
                {
                        String s[];
                        HashMap<Integer,Float> hashA =new HashMap<Integer,Float>();
                        HashMap<Integer,Float> hashB =new HashMap<Integer,Float>();
                        for(Text value :values)
                        {
                                s=value.toString().split(",");
                                if(s[0].equals("A"))
                                        hashA.put(Integer.parseInt(s[1]),Float.parseFloat(s[2]));
				else
					hashB.put(Integer.parseInt(s[1]),Float.parseFloat(s[2]));
			}
				int n = Integer.parseInt(context.getConfiguration().get("n"));
        			float result = 0.0f;
           			float a_ij;
           			 float b_jk;
           			 for (int j = 0; j < n; j++) {
               			 a_ij = hashA.containsKey(j) ? hashA.get(j) : 0.0f;
                //		System.out.println(a_ij);
			//	JOptionPane.showMessageDialog(null,a_ij);
				b_jk = hashB.containsKey(j) ? hashB.get(j) : 0.0f;
               // 		System.out.println(b_jk);
	     		//	JOptionPane.showMessageDialog(null,b_jk);
				result += a_ij * b_jk;
           			 }
           	//		 if (result != 0.0f) {
               			 context.write(null, new Text(key.toString() + "," + Float.toString(result)));
                  //      }
                }

		
	}	
	public static void main(String args[]) throws Exception
	{
	Configuration conf = new Configuration();
	if(args.length!=5)
	{
		System.out.println("provide sufficient arguments");
		System.exit(-1);
	}
	conf.set("m", args[2]);
        conf.set("n", args[3]);
        conf.set("p", args[4]);


        Job job = Job.getInstance(conf, "Mat_vect_mul");
        job.setJarByClass(Mat_vect_mul.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
 
        job.setMapperClass(Map.class);
        job.setReducerClass(Reduce.class);
 
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);
 
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
 
       // job.submit();
	job.waitForCompletion(true);
	
	}
}
