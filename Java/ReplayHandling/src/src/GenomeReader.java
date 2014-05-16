	

package src;
     
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
     
    public class GenomeReader {
     
      public static void main(String[] args) {
     
            GenomeReader obj = new GenomeReader();
            obj.run(args[0], args[1]);
      }
     
      public ArrayList<String> listFilesForFolder(final File folder) {
             
              ArrayList<String> li = new ArrayList<String>();
             
              for (final File fileEntry : folder.listFiles()) {
                    if (fileEntry.isDirectory()) {
                        listFilesForFolder(fileEntry);
                    } else {
                        li.add(fileEntry.getName());
                    }
                }
             
              return li;
            }
     
      public void run(String arg0, String arg1) {
           
    	  	final File folder = new File(arg0);
            ArrayList<String> files = listFilesForFolder(folder);
            BufferedReader br = null;
            String line = "";
           
           	HashMap<String, String> genomes = new HashMap<String, String>();
           
            for (String file : files) {
                   
           
           
            try {
     
                    br = new BufferedReader(new FileReader(arg0+file));
                    while ((line = br.readLine()) != null) {
                    
                    	String[] lin = line.split(" ");
                    	if(!genomes.containsKey(lin[2])) genomes.put(lin[2], line);
                    }
     
            } catch (FileNotFoundException e) {
                    e.printStackTrace();
            } catch (IOException e) {
                    e.printStackTrace();
            } finally {
                    if (br != null) {
                            try {
                                    br.close();
                            } catch (IOException e) {
                                    e.printStackTrace();
                            }
                    }
            }
            
            ArrayList<String> sortedGenes = new ArrayList<String>(genomes.values());

            Collections.sort(sortedGenes, new Comparator<String>() {

                public int compare(String o1, String o2) {
                    return Integer.parseInt(o1.split(" ")[2]) - Integer.parseInt(o2.split(" ")[2]);
                }
            });
            
            PrintWriter writer;
//			try {
//				writer = new PrintWriter(file+".genome", "UTF-8");
//				
//				for (Map.Entry<String, String> entry : genomes.entrySet())
//	            {
//					String[] genes = entry.getValue().split(" ");
//					System.out.println("genes.length "+genes.length);
//	            	for (int i = 4; i < genes.length; i++) {
//						
//	            		writer.print("listOfGenomes"+genes[2]+"["+(i-4)+"] "+genes[i]+"\n");
//					}
//	            }
//				
//				writer.close();
//				
//			} catch (FileNotFoundException | UnsupportedEncodingException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
            try {
			} catch (Exception e) {
				// TODO: handle exception
			}
            
            try {
            	BufferedReader replayReader = new BufferedReader(new FileReader(arg1));
				writer = new PrintWriter(file+".genome", "UTF-8");
				
				while( (line = replayReader.readLine()) != null){
					writer.println(line);
				}
				replayReader.close();

				writer.print("\n");
				for (String genome : sortedGenes) {
					
					String[] genes = genome.split(" ");
					for (int i = 4; i < genes.length; i++) {
						
	            		writer.print("listOfGenomes"+genes[2]+"["+(i-4)+"] "+genes[i]+"\n");
					}
				}
				writer.close();
				
			} catch (FileNotFoundException | UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
           
            }
            
            System.out.println("Size of Hasmap "+genomes.size());
            System.out.println("Done");
      }
     
    }

