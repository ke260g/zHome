#!/bin/env python3
"""
"""
import os
import sys
if len(sys.argv) != 4:
    print(sys.argv[0], "<ifname> <ssid> <psk>")
    sys.exit()

IFNAME=sys.argv[1]
SSID=sys.argv[2]
PSK=sys.argv[3]

cmdDel = "nmcli con del {0}".format(SSID)
cmdAdd = "nmcli con add type wifi con-name {0} ifname {1} ssid {0}".format(SSID, IFNAME)
cmdWpa = "nmcli con modify {0} wifi-sec.key-mgmt wpa-psk".format(SSID)
cmdPsk = "nmcli con modify {0} wifi-sec.psk {1}".format(SSID, PSK)
cmdUp  = "nmcli con up {0}".format(SSID)
print(cmdDel)
print(cmdAdd)
print(cmdWpa)
print(cmdPsk)
print(cmdUp)

"""
os.system(cmdDel)
os.system(cmdAdd)
os.system(cmdWpa)
os.system(cmdPsk)
os.system(cmdUp)
"""
