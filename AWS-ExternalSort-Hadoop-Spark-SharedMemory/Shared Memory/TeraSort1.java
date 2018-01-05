import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;



public class TeraSort1
{
	static long L = 100; // record size 100 B
	static long M = 1000000000;  // slice size 1 GB
	static long N; // size of the file in disk
	
	static void externalSort()
	{
		try
		{
			ExecutorService service = Executors.newFixedThreadPool(4);
			File data = new File("data.txt");
			N = data.length();
			
			int slices = (int) Math.ceil((double) N/M);
			
			for(int i=0; i<=slices; i++)
			{
				final int sliceNum = i;
				service.execute(new Runnable() {
					
					@Override
					public void run() {
						try {
							FileInputStream in = new FileInputStream("data.txt");
							BufferedReader br = new BufferedReader(new InputStreamReader(in));
							br.skip(M*sliceNum);
							int lines = (int) (M/L);
							String[] filearray = new String[lines];
							for (int i=0; i<lines; i++) {
								filearray[i] = br.readLine();
							}
							Arrays.sort(filearray);
							FileWriter fw = new FileWriter("Temp-File" + Integer.toString(sliceNum) + ".txt");
							PrintWriter pw = new PrintWriter(fw);
							for (int i = 0; i < lines; i++)
							{
								pw.println(filearray[i]);
							}
							br.close();
							pw.close();
							fw.close();
							
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});
				
			}
			service.shutdown();
			while (!service.isTerminated()) {
				// waiting for all tasks to complete
			}
			
			
			String[] mer = new String[slices];
			BufferedReader[] brs = new BufferedReader[slices];
   
			for (int i = 0; i < slices; i++)
			{

				brs[i] = new BufferedReader(new FileReader("Temp-File" + Integer.toString(i) + ".txt"));
				String t = brs[i].readLine();
				if (t != null)
				{
					/*for (int j = 0; j < mer.length; j++)
						{*/
							mer[i] = t;
						//}
				
				}
				
				else
				{
					mer[i] = "";
				}
				
				//System.out.println(mer[i]);
				
			}
			
			FileWriter fw = new FileWriter("external-sorted.txt");
			PrintWriter pw = new PrintWriter(fw);
			
			for (int i = 0; i < N/L; i++)
			{
				String min = mer[0];
				int minFile = 0;
				
				for (int j = 0; j < slices; j++)
				{
					if (min.compareTo(mer[j]) > 0)
					{
						min = mer[j];
						minFile = j;
					}
					
					//System.out.println(minFile);					
				}
				
				pw.println(min);
	
				String t = brs[minFile].readLine();
				if(t != null)
				{
					mer[minFile] = t;
				}
				else
				{
					mer[minFile] = "~!@#$%";
				}	

			}

			
			for (int i = 0; i < slices; i++) {
				brs[i].close();
				new File("Temp-File" + Integer.toString(i) + ".txt").delete();
			}
   
			pw.close();
			fw.close();
			}
		
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void main(String args[])
	{
		
		long start_t = System.currentTimeMillis();
		externalSort();
		long end_t = System.currentTimeMillis();
		long total_t = end_t - start_t;
		System.out.println("Total Time : " +total_t+ " milliseconds");
	}
}