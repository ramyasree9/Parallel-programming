javac -classpath $HADOOP_JAR_FILES/common/hadoop-common-2.2.0.jar:$HADOOP_JAR_FILES/mapreduce/hadoop-mapreduce-client-core-2.2.0.jar:$HADOOP_JAR_FILES/common/lib/commons-cli-1.2.jar -d test/ Wordcount.java  -Xlint:deprecation 
