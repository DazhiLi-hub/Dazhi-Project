pycode_path=./
log_path=./logs
pkill python3
nohup python3 ${pycode_path}/run.py > ${log_path}/server_log.txt 2>&1 &
com_1=$(ps | grep "python3")
if [ -n "${com_1}" ]
then
echo "Flask start successfully"
echo "Access the web from ip address 127.0.0.1:5000"
else
echo "Flask start failed, please check codes and restart"
exit
fi
python3 ${pycode_path}/listener.py > /dev/null 2>&1 &
com_2=$(ps | grep "python3")
if [ -n "${com_2}" ]
then
echo "Listener start successfully"
else
echo "Listener start failed, please check codes and restart"
exit
fi