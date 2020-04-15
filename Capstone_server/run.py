from flask import Flask,request
import db
import json

last_update=None
app = Flask(__name__)

#list_a is the old one, list_b is the new one
def get_diff(list_a,list_b):
    diff_list=[]
    for i in range(len(list_a)):
        if list_a[i]['status'] != list_b[i]['status'] or list_a[i]['plate'] != list_b[i]['plate']:
            diff_list.append(list_b[i])
        else:
            continue
    if diff_list==[]:
        return "No update information"
    else:
        return diff_list

# @app.route('/post', methods=['POST'])
# def post():
#     uid = request.form['uid']
#     name =  request.form['name']
#     print('uid: %s, name: %s' % (uid, name))
#     return 'OK.'

@app.route('/',methods=['GET'])
def all_send():
    global last_update
    last_update=db.park.find_all()
    return json.dumps(last_update)

@app.route('/empty',methods=['GET'])
def empty_send():
    results=db.park.find_empty()
    return json.dumps(results)

#getting URL eg. http://127.0.0.1:5000/yours?plate=D33LOP
@app.route('/yours',methods=['GET'])
def yours_send():
    plate=request.args.get('plate','Flask')
    results=db.park.find_yours(plate)
    return json.dumps(results)

@app.route('/update',methods=['GET'])
def update_send():
    global last_update
    new_update=db.park.find_all()
    print(last_update)
    print(new_update)
    results=get_diff(last_update,new_update)
    last_update=new_update
    return json.dumps(results)

if __name__ == "__main__":
    app.run(debug=True)