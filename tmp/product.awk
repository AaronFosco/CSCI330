BEGIN {
 FS=":"
 printf("%3d\t%-25s\t%7f\n", "1", "2", "3")
 
}

{
 printf("%3d\t%-25s\t%7.2f\n", $1, $2, $3) 
}
END {
 print NR
 }
Davy Jones               	            Security	     60
Ricky Davis              	           Developer	    169
Samantha Smith           	         Salesperson	     80
Matt Smith               	              Doctor	     20
David Tennant            	              Doctor	1010444
Buckminster Fuller       	            Engineer	  10059
Clara Oswald             	               Nurse	     39
Amelia Pond              	               Nurse	     20
