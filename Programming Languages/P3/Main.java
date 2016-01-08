import java.io.*;

public class Main
{
	public static void main(String[] args)
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = null;
		while(true)
		{
			System.out.print("> ");
			try{
				if((s = br.readLine())==null) {
					System.out.println();
					break;
				}
			}catch(IOException e){
				e.printStackTrace();	
			}
			int n = s.length(), k = 0;
			int E[] = new int[n];
			for(int i=0; i<n; i++)
				if(s.charAt(i)=='(') {
					k++;
					E[k] = i;
				}
			for(int i=1; i<=k; i++){
				System.out.print("<E"+i+"> => (");
				int j = E[i], e = i, c = 0;
				while(true){
					j++;
					if(s.charAt(j)=='(') { 
						e++;
						if(c==0) System.out.print("<E"+e+">");
						c++;
					}
					if(s.charAt(j)==')') {
						if(c==0) break;
						c--;
						continue;
					} 
					if(c==0) System.out.print(s.charAt(j));
				}
				System.out.println(")");
			}
		}
	}
}
