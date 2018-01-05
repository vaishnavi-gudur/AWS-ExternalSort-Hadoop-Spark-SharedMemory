import java.util.*; 

import java.io.IOException; 

import org.apache.hadoop.fs.Path; 
import org.apache.hadoop.io.*; 
import org.apache.hadoop.mapred.*; 

public class HTeraSort 
{ 
   public static class HMapper extends MapReduceBase implements 
   Mapper<LongWritable, Text, Text, Text> 
   { 
      
      public void map(LongWritable key, Text value, 
      OutputCollector<Text, Text> output,   
      Reporter reporter) throws IOException 
      { 
         output.collect(new Text(value.toString().substring(0, 10)), new Text(value.toString().substring(10))); 
      } 
   } 
   
   public static class HReduce extends MapReduceBase implements 
   Reducer< Text, Text, Text, Text> 
   {  
      public void reduce( Text key, Iterator <Text> values, OutputCollector<Text, Text> output, Reporter reporter) throws IOException 
         { 
            while (values.hasNext()) 
            { 
            	output.collect(key, values.next()); 
            } 
 
         } 
   }  
   
   public static void main(String args[])throws Exception 
   { 
      JobConf conf = new JobConf(HTeraSort.class); 
      conf.setJobName("TeraSort"); 
      conf.setOutputKeyClass(Text.class);
      conf.setOutputValueClass(Text.class); 
      conf.setMapperClass(HMapper.class); 
      conf.setCombinerClass(HReduce.class); 
      conf.setReducerClass(HReduce.class); 
      conf.setInputFormat(TextInputFormat.class); 
      conf.setOutputFormat(TextOutputFormat.class); 
      
      FileInputFormat.setInputPaths(conf, new Path(args[0])); 
      FileOutputFormat.setOutputPath(conf, new Path(args[1])); 
      
      JobClient.runJob(conf); 
   } 
} 