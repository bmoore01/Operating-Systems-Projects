wout=`w -i | awk '{print $3}' | grep "\."`
#echo "$wout";
for ip in `echo "$wout"`;
do  
   echo "IP: $ip"; 
   hops=`traceroute -n -w 1 $ip | grep -v "to" | awk '{print $2}'`
   hops=`echo "$hops" | grep -v "\*"`
   #echo "$hops"
   for hop in `echo "$hops"`
   do 
		coords=`curl -s ipinfo.io/$hop | grep loc | sed 's/.*: "\(.*\)",/\1/'`
		echo "  $ip: $hop: ($coords)"
   done 
done
