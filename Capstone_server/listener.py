import db
import time
import json

#listening example

data_path="/Users/dazhili/PycharmProjects/Mask_RCNN/parking_lot_status.json"
while True:
    with open(data_path) as f:
        parking_status = json.load(f)
        db.park.all_init(parking_status)
        print("system updated")
        time.sleep(300)