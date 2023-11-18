#!/bin/bash

# Architecture of OS & kernel version
arch=$(uname -srvmo)

# Physical processors
pcpu=$(lscpu | awk -F : '
	/^Core\(s\) per socket/ {mult=$2}
	/^Socket\(s\)/ {mult*=$2}
	END {print mult}')

# Virtual processors
vcpu=$(nproc --all)

# RAM available/total MB (%)
rama=$(free -m | awk '/^Mem:/ {print $7}')
ramt=$(free -m | awk '/^Mem:/ {print $2}')
ramp=$(printf '%.2f' $((10000*rama/ramt))e-2)

# DISK available/total GB (%)
temp=$(df -x tmpfs -x devtmpfs --total | grep ^total)
tmpa=$(echo $temp | awk '{print $4}')
tmpt=$(echo $temp | awk '{print $2}')
dska=$(printf '%.2f' $((100*tmpa/1024/1024))e-2)
dskt=$(printf '%.2f' $((100*tmpt/1024/1024))e-2)
dskp=$(printf '%.2f' $((10000*tmpa/tmpt))e-2)

# CPU utilization rate (%)
cpup=$((100-$(vmstat 1 2 | tail -1 | awk '{print $15}')))

# Last reboot (yyyy-mm-dd HH:MM:SS)
lrbt=$(uptime -s)

# LVM in use
lvmu=$(if grep -q '/dev/mapper/' /etc/fstab
	then echo yes
	else echo no
	fi)

# Active TCP and UDP connections
acon=$(ss -Htu -o state connected | wc -l) 

# Logged users
logu=$(who | wc -l)

# IPv4 and MAC addresses
defd=$(ip route | grep default | awk '{print $NF}')
ipv4=$(ip address show $defd | grep -Eo 'inet ([0-9]*\.){3}[0-9]*' | awk '{print $2}')
maca=$(ip link show $defd | grep link | awk '{print $2}')

# sudo usage
sudo=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "	Architecture: $arch
	Physical processor(s): $pcpu
	Virtual processor(s): $vcpu
	Available memory: $rama/$ramt MB ($ramp%)
	Available disk space: $dska/$dskt GB ($dskp%)
	CPU usage: $cpup%
	Last reboot: $lrbt
	LVM in use? $lvmu
	Active Internet (TCP and UDP) connections: $acon
	Logged users: $logu
	Network: IPv4 $ipv4 MAC $maca
	Executed sudo commands: $sudo"
