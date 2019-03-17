### cmd
+ sh$ mysql -u \<user\> -p < mysql_script.sql
    then enter passwd
+ db$ show databases
+ db$ use \<database\>
+ db$ create table \<table_name\>

# notes
### reset root password safely
1. sh$ service mysql stop
2. sh$ chmod 544 /usr/bin/mysql\*
    + without this cmd, it's really dangerous
3. sh$ mysqld_safe --skip-grant-tables &
    + if without 2., every user in the OS can modify root's mysql
4. db$ UPDATE user SET Password=PASSWORD('newpassword') where USER='root';
5. db$ FLUSH PRIVILEGES;
    + as mentioned in 1, any user in system can modify
6. db$ quit;
7. killall mysqld
8. sh$ chmod 755 /usr/bin/mysql\*
9. sh$ service mysql start
