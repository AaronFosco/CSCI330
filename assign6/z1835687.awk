#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-330      Assignment #: 6    Semester: Fall2017  ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
#||                                                               ||
#||  TA's Name: May Myo Khine                                     ||
#||                                                               ||
#||  Due: Wednesday 11/29/2017 by 11:59PM                         ||
#||                                                               ||
#||  Description:                                                 ||
#||     This is a script to be used with a database file using    ||
#||     the awk command. This script will print out an organized  ||
#||     Ranking of Associates from the database file.             ||
# \_______________________________________________________________/

BEGIN {
	FS = ":"
	print "No-op Computing"
	print "2017 Sale Associates Ranking"
	printf("%-17s\t%-15s\t%13s\n", "Name", "Position", "Sales Ammount")
	print "======================================================"
}

#The patterns that are looked for is the ammount of fields
#per record. Data is stored in arrays Accordingly

#4 fields indciate a product

NF==4{
	procat[$1]=$2
	prodesc[$1]=$3
	proprice[$1]=$4
}

#3 fields indicate an associtate

NF==3 {
	split($2,name," ")
	asname[$1]=name[2]", "name[1]
	aspos[$1]=$3
	astotsale[$1]=0.00
}

#5 fields indicate a sale

NF==5 {
	saldate[$1]=$4
	
	#loop to add up the total sales
	counter=0
	while (counter < $3) {
		astotsale[$5]+=proprice[$2]
		counter++
	}
}

END {
        #loop to print out all sales in sorted order
	for (i in astotsale) {
		printf("%-20s\t%-15s\t%10.2f\n", asname[i], aspos[i], astotsale[i]) | "sort -nr -k 4"
	}
}
