#!/bin/bash
log_path=/root/logs
pycode_path=/root/Capstone_server
nohup mongod > ${log_path}/db_log.txt 2>&1 &
com_1=$(ps | grep "mongod")
if [ -n "${com_1}" ]
then
echo "mongodb service start!"
else
echo "mongodb start failed, please try again"
exit
fi
nohup python3 ${pycode_path}/run.py > ${log_path}/server_log.txt 2>&1 &
com_2=$(ps | grep "python3")
if [ -n "${com_2}" ]
then
echo "Falsk start successfully"
echo "Access the web from ip address 39.107.76.62"
else
echo "Flask start failed, please check codes and restart"
exit
fi
#python3 ${pycode_path}/listener.py > /dev/null 2>&1 &