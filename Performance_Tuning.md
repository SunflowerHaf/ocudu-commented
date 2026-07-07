Set CPU Governor to Performance
  sudo apt install cpufrequtils
  sudo cpufreq-set -r -g performance
  grep ./sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
  cpufreq-info

Set Thread Priority Scheduling
  sudo groupadd usrp
  sudo usermod -aG usrp $USER
Add @usrp - rtprio 99 to the end of the file /etc/security/limits.conf

Adjust Network Buffers
  sudo sysctl -w net.core.wmem_max=33554432
  sudo sysctl -w net.core.rmem_max=33554432

Adjust Ethernet MTU
  ifconfig
  sudo ifconfig $ETHERNET mtu 9000 up

Increase Ring Buffers
  sudo ethtool -G $ETHERNET tx 4096 rx 4096

Disable C-State Support and Hyperthreading/Multithreading in the BIOS
