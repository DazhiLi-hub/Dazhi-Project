#!/bin/bash
pkill mongod
pkill python3
rm -rf /root/logs/db_log.txt
rm -rf /root/logs/server_log.txt