from flask import Flask,render_template,url_for,request,redirect,abort
from werkzeug.datastructures import ImmutableMultiDict
import pymongo
import random

def invitation_code():
    ret = ""
    for i in range(6):
        num = random.randint(0, 9)
        # num = chr(random.randint(48,57))
        letter = chr(random.randint(97, 122))#Lower class
        Letter = chr(random.randint(65, 90))#Uper class
        s = str(random.choice([num,letter,Letter]))
        ret += s
    return ret

app=Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

# @app.route('/login',methods=['POST'])
# def login():
#     user = request.form['nm']
#     return redirect(url_for('success',name=user))

@app.route('/signin',methods=['GET','POST'])
def sign_in():
    if request.method=='GET':
        return render_template('signin.html')
    elif request.method=='POST':
        invitation=request.form['invitation_num']
        guest=collection.find_one({'invitation_num':invitation})
        if(guest):
            return render_template('login.html',guest=guest)
        else:
            return render_template('fault.html')
    else:
        abort(400)

@app.route('/signup',methods=['GET','POST'])
def sign_up():
    if request.method == 'GET':
        return render_template('signup.html')
    elif request.method == 'POST':
        new_guest=request.form
        new_guest=new_guest.to_dict(flat=True)
        new_guest['invitation_num']=invitation_code()
        while(collection.find_one({'invitation_num':new_guest['invitation_num']})):
            new_guest['invitation_num'] = invitation_code()
        collection.insert_one(new_guest)
        return render_template('success.html',new_guest=new_guest)
    else:
        abort(400)

if __name__=='__main__':
    client = pymongo.MongoClient(host='localhost', port=27017)
    db = client.guest
    collection = db.guest_list
    app.run(debug=True)