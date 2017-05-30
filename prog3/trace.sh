#!/bin/bash

# include the smartlog library
source '/usr/lib/smartlog/smartlog.sh'


# get connected IPs
log "Getting connected IP addresses"

if connIPs=($(w -i | grep -E -o '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}')) ; then
		ok
else
		fail
fi

# get connected users
log "Getting connected users"
if connUsers=($(w -i | grep -E -o '^[a-z]{1,}[0-9]{1,}')); then
		ok
else
		fail
fi

# loop through IPs and usernames 
for index in ${!connIPs[*]}; do
		#traceroute ip addresses
		echo "User: ${connUsers[$index]} IP: ${connIPs[$index]}"
		hops=`traceroute -n -w 1 ${connIPs[$index]} | grep -v "to" | awk '{print $2}'`
		hops=`echo "$hops" | grep -v "\*"`
			for hop in $hops; do
					# query coordinate database
					coords=`curl -s ipinfo.io/$hop | grep loc | sed 's/.*: "\(.*\)",/\1/'` 
					echo " ${connIPs[$index]}:	$hop:	($coords)"
			done
done
