#! /usr/bin/python

### BEGIN INIT INFO
# Provides:		Gmail Notification
# Required-Start:	$remote_fs $syslog
# Required-Stop:	$remote_fs $syslog
# Default-Start:	2 3 4 5
# Default-Stop:		
# Short-Description:	Gmail Notification (Info include: IP)
### END INIT INFO

import socket
import fcntl
import struct
from datetime import datetime

from email.header import Header
from email.mime.text import MIMEText
from smtplib import SMTP_SSL

def get_ip_addr(ifname) :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
    try :
        ip = socket.inet_ntoa(fcntl.ioctl(s.fileno(), 0x8915, struct.pack('256s', ifname[:15]))[20:24]);
    except IOError :
        ip = "N/A";
    return ip;

print "IP Address (eth0): ", get_ip_addr('eth0');
print "IP Address (wlan0): ",  get_ip_addr('wlan0');
print "Sending email..."

login, password = "your gmail address", "your gmail password";

msg = MIMEText("Time: " + datetime.now().strftime("%Y-%m-%d %H:%M:%S:%s") + "\nIP Address (eth0): " + get_ip_addr("eth0") + "\nIP Address (wlan0): " + get_ip_addr("wlan0"));
msg['Subject'] = Header("My Raspberry Pi IP", "utf-8");
msg['From'] = login;
msg['To'] = login;

s = SMTP_SSL("smtp.gmail.com", 465, timeout = 10);
s.set_debuglevel(0);

try :
    s.login(login, password);
    s.sendmail(msg['From'], msg['To'], msg.as_string());
finally :
    s.quit();
