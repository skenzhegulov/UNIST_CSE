import java.io.*;
import java.util.*;

public class Computer {
 	static Scanner in = new Scanner(System.in);

	static int Register[], RAM[], i, m, k, x, t, j = 0;

	static void f2dn(int d, int n){
		Register[d] = n;	
		k++;
	}

	static void f3dn(int d, int n){
		Register[d] = (Register[d] + n) % 1000;	
		k++;
	}

	static void f4dn(int d, int n){
		Register[d] = (Register[d] * n) % 1000;	
		k++;
	}

	static void f5ds(int d, int s){
		Register[d] = Register[s];	
		k++;
	}

	static void f6ds(int d, int s){
		Register[d] = (Register[d] + Register[s]) % 1000;	
		k++;
	}

	static void f7ds(int d, int s){
		Register[d] = (Register[d] * Register[s]) % 1000;	
		k++;
	}
	
	static void f8da(int d, int a){
		Register[d] = RAM[Register[a]];	
		k++;
	}

	static void f9sa(int s, int a){
		RAM[Register[a]] = Register[s];
		k++;
	}

	static void f0ds(int d, int s){
		k++;
		while(Register[s] % 10 != 0) {
			k++;
			int y = RAM[Register[d]];
			execute(y / 100, y / 10 % 10, y % 10);
		}
	}

	static void execute(int a, int b, int c){
		if(a==2) f2dn(b,c); else
		if(a==3) f3dn(b,c); else
		if(a==4) f4dn(b,c); else 
		if(a==5) f5ds(b,c); else
		if(a==6) f6ds(b,c); else
		if(a==7) f7ds(b,c); else
		if(a==8) f8da(b,c); else
		if(a==9) f9sa(b,c); else f0ds(b,c);		
	}

	public static void main(String[] args){
		String s;
		s = in.nextLine();
		t = Integer.parseInt(s);
		s = in.nextLine();
		while(true){
			j++;
			Register = new int[10];
			for(i=0; i<10; i++) Register[i] = 0;
			RAM = new int[1000];
			for(i=0; i<1000; i++) RAM[i] = 0;
			k = 1;
			i = 0;
			s = in.nextLine();
			while(!(s.isEmpty())) {
				x = Integer.parseInt(s);
				RAM[i] = x;
				i++;
				s = in.nextLine();
			}
			m = i;
			for(i=0; i<m; i++) 
				if(RAM[i] == 100) break; else execute(RAM[i] / 100, RAM[i] / 10 % 10, RAM[i] % 10);
			System.out.println(k);
			if(j<t) System.out.println(); else break;
		}
	}
}
