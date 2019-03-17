##echo diagram using tcp
### server
+ server obtains the listening port from first exec-param
+ server exec without any exec-param will listening port:20000
### client
+ client obtains the sending host from first exec-param
+ client obtains the sending port from second exec-param
+ without second exec-param, client will sendto port:20000
### parse_args_port.c
+ an simple, ugly function to parse port from string(exec-param)
