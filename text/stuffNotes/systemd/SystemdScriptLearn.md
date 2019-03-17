### first file
/lib/systemd/system/default.service

### script file
##### [Unit]
* Requires=
* Wants=
* After=
* Conflicts=

##### [name].target flow
*condition*
 [Unit]:Wants=
 [Unit]:After=

*exec*
\> [Unit]:Requires=
\> [name].target.wants/\*
\> [Service]:ExecStart=

#### Note:
* ExecStart= it's not a shell common.<br></br>
* If you want to use '&','\>',<br></br>
  ExecStart=/bin/sh -c "shell command"

### Simple Example
on /lib/systemd/system/test.service
* $ systemctl enable test.service
```
[Unit]
Description=mytest

[Service]
Type=simple
GuessMainPID=yes
ExecStart=/bin/sh -c "echo xyz > /home/ll/text.txt"
Restart=no

[Install]
WantedBy=multi-user.target
```
