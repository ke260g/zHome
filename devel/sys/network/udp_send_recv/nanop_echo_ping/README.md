echo_nanop.c, run on server, a daemon
    receive any data from port:3095
    then echo back a "NanoPi3" message.
    place it in /etc/init.d
echo_nanop.service, systemd daemon script
    need to be `systemctl enable`
ping_nanop.c, run on client
    send data to port:3095
    and waiting echo-back-message
    wait to timeout or message receive
    first argument as the server ip
    usage: ./ping_nanop 192.168.3.200
