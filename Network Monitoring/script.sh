#!/bin/sh

### command to start the packet capturing ###
/usr/sbin/tcpdump -ne -c 1000 > /var/www/html/X/X1/Capture/capture

### Grep the IP, ARP, UDP packets info from the captured packet by tcpdump###
grep "IP" Capture/capture >  Capture/IP/main
grep "ARP" Capture/capture >  Capture/ARP/main
grep "UDP" Capture/capture >  Capture/UDP/main

### cut different field from the IP packets which are placed in Capture/IP/main###
cut -d " " -f1 Capture/IP/main > Capture/IP/ip1
cut -d " " -f2 Capture/IP/main > Capture/IP/ip2
cut -d " " -f4 Capture/IP/main > Capture/IP/ip11
cut -d "," -f1 Capture/IP/ip11 > Capture/IP/ip3
cut -d " " -f9 Capture/IP/main > Capture/IP/ip12
cut -d ":" -f1 Capture/IP/ip12 > Capture/IP/ip4
cut -d " " -f10 Capture/IP/main > Capture/IP/ip13
cut -d "." -f5 Capture/IP/ip13 > Capture/IP/ip7
cut -d "." -f1,2,3,4 Capture/IP/ip13 > Capture/IP/ip5
cut -d " " -f12 Capture/IP/main > Capture/IP/ip14
cut -d "." -f5 Capture/IP/ip14 > Capture/IP/ip15
cut -d ":" -f1 Capture/IP/ip15 > Capture/IP/ip8
cut -d "." -f1,2,3,4 Capture/IP/ip14 > Capture/IP/ip6

### combine all the 8 field and place it into a single file named as ip10###
paste Capture/IP/ip1 Capture/IP/ip2 Capture/IP/ip3 Capture/IP/ip4 Capture/IP/ip5 Capture/IP/ip6 Capture/IP/ip7 Capture/IP/ip8 > Capture/IP/ip10


### cut different field from the ARP packets which are placed in Capture/ARP/main###
cut -d " " -f1 Capture/ARP/main > Capture/ARP/arp1
cut -d " " -f2 Capture/ARP/main > Capture/ARP/arp2
cut -d " " -f4 Capture/ARP/main > Capture/ARP/arp10
cut -d "," -f1 Capture/ARP/arp10 > Capture/ARP/arp3
cut -d " " -f9 Capture/ARP/main > Capture/ARP/arp11
cut -d ":" -f1 Capture/ARP/arp11 > Capture/ARP/arp4
cut -d " " -f12 Capture/ARP/main > Capture/ARP/arp5
cut -d " " -f14 Capture/ARP/main > Capture/ARP/arp6

### combine all the 8 field and place it into a single file named as arp9###
paste Capture/ARP/arp1 Capture/ARP/arp2 Capture/ARP/arp3 Capture/ARP/arp4 Capture/ARP/arp5 Capture/ARP/arp6 > Capture/ARP/arp9

### cut different field from the UDP packets which are placed in Capture/UDP/main###
cut -d " " -f1 Capture/UDP/main > Capture/UDP/udp1
cut -d " " -f2 Capture/UDP/main > Capture/UDP/udp2
cut -d " " -f4 Capture/UDP/main > Capture/UDP/udp10
cut -d "," -f1 Capture/UDP/udp10 > Capture/UDP/udp3
cut -d " " -f9 Capture/UDP/main > Capture/UDP/udp11
cut -d ":" -f1 Capture/UDP/udp11 > Capture/UDP/udp4
cut -d " " -f10 Capture/UDP/main > Capture/UDP/udp13
cut -d "." -f5 Capture/UDP/udp13 > Capture/UDP/udp7
cut -d "." -f1,2,3,4 Capture/UDP/udp13 > Capture/UDP/udp5
cut -d " " -f12 Capture/UDP/main > Capture/UDP/udp14
cut -d "." -f5 Capture/UDP/udp14 > Capture/UDP/udp15
cut -d ":" -f1 Capture/UDP/udp15 > Capture/UDP/udp8
cut -d "." -f1,2,3,4 Capture/UDP/udp14 > Capture/UDP/udp6

### combine all the 8 field and place it into a single file named as udp9###
paste Capture/UDP/udp1 Capture/UDP/udp2 Capture/UDP/udp3 Capture/UDP/udp4 Capture/UDP/udp5 Capture/UDP/udp6 Capture/UDP/udp7 Capture/UDP/udp8 > Capture/UDP/udp9

### place all packet info into a single file all1###
cat Capture/IP/ip10 Capture/UDP/udp9 Capture/ARP/arp9 > Capture/All/all1

### place all the source_ip into a single file top###
cat Capture/IP/ip5 Capture/ARP/arp5 Capture/UDP/udp5 > Capture/Top/top

### take top five source_ip machine which are send max packet###
sort -nr Capture/Top/top > Capture/Top/top1
uniq -c Capture/Top/top1 > Capture/Top/top2
sort -nr Capture/Top/top2 > Capture/Top/top3
head -n 03 Capture/Top/top3 > Capture/Top/top4

### seperate the source_ip field and total no. of packet info###
cut -c9- Capture/Top/top4 > Capture/Top/top5
cut -c1,2,3,4,5,6,7 Capture/Top/top4 > Capture/Top/top6
paste Capture/Top/top6 Capture/Top/top5 > Capture/Top/top7
