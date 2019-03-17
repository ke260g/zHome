#!/bin/bash
#########
apt-get update
apt-get install network-manager network-manager-gnome
systemctl disable networking
# edit the /etc/network/interfaces, comment the ignore interface
systemctl enable NetworkManager.service
reboot

# nmcli/nmtui connect to the wifi stuff
apt-get install qt5-default qtcreator git cppman
apt-get install pinfo ranger htop dstat trash-cli
apt-get install apt-file usbutils
apt-get install pure-ftpd ncftp nfs-kernel-server
systemctl enable pure-ftpd.service

:<<! how to connect to hidden wifi in the console
<password> has to be included with two double quotation marks

$ nmcli con add type wifi con-name <connect name> ifname wlan0 ssid <ssid>
$ nmcli con modify <connect name> wifi-sec.key-mgmt wpa-psk
$ nmcli con modify <connect name> wifi-sec.psk <password>
$ nmcli con up <connect name>
!

apt-file update
apt-file list package_name
apt-file search file_name
