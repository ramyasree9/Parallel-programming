#for compilation of hadoop #WordCount.java#  program
javac -classpath $HADOOP_JAR_FILES/common/hadoop-common-2.2.0.jar:$HADOOP_JAR_FILES/mapreduce/hadoop-mapreduce-client-core-2.2.0.jar:$HADOOP_JAR_FILES/common/lib/commons-cli-1.2.jar -d test/ WordCount.java  -Xlint:deprecation 

#Creation of #wordcount.jar# file 
jar -cvf wordcount.jar -C test/ .

#storing #wordinput.txt# file into HDFS
hadoop fs -put wordinput.txt wordinput.txt
 
#Execution of #WordCount.java# program
hadoop jar <wordcount.jar> <WordCount> <wordinput.txt> <output>

#NOTE:
