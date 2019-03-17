#!/bin/bash
S:<<! how to connect to hidden wifi in the console
<password> has to be included with two double quotation marks

$ nmcli con add type wifi con-name <connect name> ifname wlan0 ssid <ssid>
$ nmcli con modify <connect name> wifi-sec.key-mgmt wpa-psk
$ nmcli con modify <connect name> wifi-sec.psk <password>
$ nmcli con up <connect name>
!

SID="13220"
PSK="gdut3220"
IFACE_0="wlan0"
IFACE_1="wlan1"

# for first wifi-card
CON_NAME=${SSID}_${IFACE_0}
nmcli con add type wifi con-name ${CON_NAME} ifname ${IFACE_0} ssid ${SSID}
nmcli con modify ${CON_NAME} wifi-sec.key-mgmt wpa-psk
nmcli con modify ${CON_NAME} wifi-sec.psk ${PSK}
nmcli con up ${CON_NAME}

# for another wifi-card
CON_NAME=${SSID}_${IFACE_1}
nmcli con add type wifi con-name ${CON_NAME} ifname ${IFACE_1} ssid ${SSID}
nmcli con modify ${CON_NAME} wifi-sec.key-mgmt wpa-psk
nmcli con modify ${CON_NAME} wifi-sec.psk ${PSK}
nmcli con up ${CON_NAME}

