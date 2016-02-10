import java.io.*;
import java.util.*;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;

public class WordCount extends Configured implements Tool
{

  public static class WordMapper extends MapReduceBase implements Mapper<LongWritable,Text,Text,IntWritable>
  {
    //@Override
    public void map(LongWritable key,Text value,OutputCollector<Text,IntWritable> output,Reporter r)throws IOException
    {
      String s=value.toString();
      for(String word:s.split(" "))
      {
        if(word.length()>0)
        output.collect(new Text(word),new IntWritable(1));
      }
    }
  }

  public static class WordReducer extends MapReduceBase implements Reducer<Text,IntWritable,Text,IntWritable>
  {
    public void reduce(Text key,Iterator<IntWritable>values,OutputCollector<Text,IntWritable> output,Reporter r)throws IOException
    {
      int count=0;
      while(values.hasNext())
      {
        IntWritable i=values.next();
        count=count+i.get();
      }
      output.collect(key,new IntWritable(count));
    }
  }

  public int run(String[] args)throws Exception
  {
    if(args.length<2)
    {
      System.out.println("give the correct command promot inputs");
      return -1;
    }
    JobConf conf=new JobConf(WordCount.class);
    conf.setJobName("wordcount");
    FileInputFormat.setInputPaths(conf,new Path(args[0]));
    FileOutputFormat.setOutputPath(conf,new Path(args[1]));
    conf.setMapperClass(WordMapper.class);
    conf.setReducerClass(WordReducer.class);
    conf.setMapOutputKeyClass(Text.class);
    conf.setMapOutputValueClass(IntWritable.class);
    conf.setOutputKeyClass(Text.class);
    conf.setOutputValueClass(IntWritable.class);
    JobClient.runJob(conf);
    return 0;
  }
  public static void main(String[] args)throws Exception
  {
    int exitcode=ToolRunner.run(new WordCount(),args);
    System.exit(exitcode);
  }
}
