import java.io.*;

public class Main
{
	static String s;
	static int size;
	static int curr;
	static int value[];
	static boolean err;
	static String ID[];

	public static void main(String[] args)
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while(true){
			System.out.print("> ");
			try{
				if((s = br.readLine())==null) {
					System.out.println();
					break;
				}
			}catch(IOException e){
				e.printStackTrace();	
			}
			if(s.charAt(0) != '(') {
				System.out.println("Error!");
				continue;
			}
			err = false;
			size = 0;
			curr = 0;
			value = new int[s.length()];
			ID = new String[s.length()];
			int res = Parse();
			if(!err) System.out.println(res);
		}
	}

	static int Parse(){
		curr++;
		//System.out.println("Entered Parse at curr = "+curr);
		int res = 0;
		skip_space();
		if(s.charAt(curr) == ')') curr++; else
		if(s.charAt(curr) == '(') res = Parse(); else
		if(curr+2<s.length() && s.charAt(curr) == 'l' && s.charAt(curr+1) == 'e' && s.charAt(curr+2) == 't') res = Dynamic_Let(); else
		if(s.charAt(curr) == '+'||s.charAt(curr) == '-'||s.charAt(curr) == '*'||s.charAt(curr) == '/') res = Interpreter(s.charAt(curr)); else 
		if(s.charAt(curr) >= '0' && s.charAt(curr) <='9') {
			while(s.charAt(curr) >= '0' && s.charAt(curr) <= '9') res = res*10 + (s.charAt(curr++)-'0');
		} else {
			String t = "";
			while(s.charAt(curr) != ' ' && s.charAt(curr) != ')') t += s.charAt(curr++);
			error("function "+t);
		}
		if(err) return 0;
		return res;
	}

	static int Dynamic_Let(){
		while(s.charAt(curr) != '(') curr++;
		//System.out.println("Dynamic_Let at curr = "+curr);
		int k = 0;
		int sz = size;
		curr++;
		while(true){
			skip_space();
			if(s.charAt(curr) == '(') { 
				k++; 
				curr++; 
			} else if(s.charAt(curr) == ')') {
				curr++;
				if(k == 0) break;
				k--;
			} else {
				String t = "";
				skip_space();
				while(s.charAt(curr) != ' ') t += s.charAt(curr++);
				ID[sz] = t;
				skip_space();
				int v = 0;
				if(s.charAt(curr) == '(') {
					v = Parse();
					if(err) return 0;
					//curr++;
				} else if(s.charAt(curr) < '0' || s.charAt(curr) > '9') {
					v = find_value();
					if(err) return 0;
					k--;
				} else
					while(s.charAt(curr) >= '0' && s.charAt(curr) <= '9') v = v*10 + (s.charAt(curr++)-'0');
				value[sz] = v;
				sz++;
				//System.out.println(t+" = "+v);
			}
		}
		skip_space();
		size = sz;
		int res = 0;
		if(s.charAt(curr) == ')') curr++; else
		if(s.charAt(curr) == '(') res = Parse(); else 
		if(s.charAt(curr) >= '0' && s.charAt(curr) <='9') {
			while(s.charAt(curr) >= '0' && s.charAt(curr) <= '9') res = res*10 + (s.charAt(curr++)-'0');
		} 
			else res = find_value();
		if(err) return 0;
		return res;
	}

	static int Interpreter(char op){
		curr++;
		int temp, result = 0;
		if(op == '*') result = 1;
		boolean flag = false, b = false;
		//System.out.println("Interpreter: curr = "+curr+"  op = "+op);
		while(true) {
			temp = 0;
			skip_space();
			if(s.charAt(curr) == ')') {curr++; break; }else
		  	if(s.charAt(curr) == '(') {
		  		temp = Parse();
				if(err) return 0;
		  	} else 
			if(s.charAt(curr) < '0' || s.charAt(curr) > '9') {
				temp = find_value();
				if(err) return 0;
			} else {
				while(s.charAt(curr) != ' ' && s.charAt(curr) != ')') temp = temp*10 + (s.charAt(curr++) - '0');
			}
			if(flag) b = true;
			if(!flag) { result = temp; flag = true; }else 
			if(op == '+') result += temp; else
			if(op == '-') result -= temp; else
			if(op == '*') result *= temp; 
				else result /= temp;
			//System.out.println(temp+" <- (temp)\nresult = "+result);
		}
		if(!b && op == '-') result = -result;
		return result;
	}

	static int find_value(){
		String t = "";
		while(s.charAt(curr) != ' ' && s.charAt(curr) != ')') t+=s.charAt(curr++);
		curr++;
		int sz = size;
		while(true){
			sz--;
			if(sz<0) {
				error("variable "+t);
				return 0;
			}else if(t.equals(ID[sz])) break;
		}
		return value[sz];
	}

	static void error(String s){
		System.out.println("(void-"+s+")");
		err = true;
	}

	static void skip_space(){
		if(curr<s.length())
			while(s.charAt(curr) == ' ') curr++;
	}
}
