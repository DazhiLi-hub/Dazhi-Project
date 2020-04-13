import db
import time

#listening example
new_data_exist=False
updated_one={'latitude':186,'longitude':12,'park_no':6,'status':False,'plate':''}
def listener():
    while(True):
        if new_data_exist:
            db.park.update_one(updated_one)
        print('System updating .')
        time.sleep(1)
        print('System updating ..')
        time.sleep(1)
        print('System updating ...')
        time.sleep(1)

listener()