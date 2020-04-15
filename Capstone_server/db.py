import pymongo
import json

dnn_result=[{'latitude':182,'longitude':8,'park_no':1,'status':True,'plate':'B2BJUY'},
            {'latitude':182,'longitude':12,'park_no':2,'status':False,'plate':''},
            {'latitude':182,'longitude':16,'park_no':3,'status':False,'plate':''},
            {'latitude':182,'longitude':20,'park_no':4,'status':True,'plate':'66YZ86'},
            {'latitude':186,'longitude':8,'park_no':5,'status':False,'plate':''},
            {'latitude':186,'longitude':12,'park_no':6,'status':False,'plate':''}]

updated_one={'latitude':186,'longitude':12,'park_no':6,'status':True,'plate':'D33LOP'}

updated_many=[{'latitude':182,'longitude':8,'park_no':1,'status':False,'plate':''},
              {'latitude':182,'longitude':12,'park_no':2,'status':False,'plate':''},
              {'latitude':182,'longitude':16,'park_no':3,'status':True,'plate':'JKL886'},]

plate='D33LOP'

class park_db:
    def __init__(self,host,port):
        self.host=host
        self.port=port
        self.client=pymongo.MongoClient(host=self.host,port=self.port)
        self.db=self.client.park
        self.collection=self.db.parklots
        self.collection_client=self.db.backup

    def all_init(self,park_dic):
        self.collection.delete_many({})
        self.collection.insert_many(park_dic)

    # def back_write(self,park_dic):
    #     self.collection_client.delete_many({})
    #     self.collection_client.insert_many(park_dic)
    #
    # def back_read(self):
    #     all_list = []
    #     results = self.collection_client.find().sort('park_no', pymongo.ASCENDING)
    #     for result in results:
    #         del result['_id']
    #         all_list.append(result)
    #     return all_list

    def update_one(self,updated_one):
        condition={'park_no':updated_one['park_no']}
        self.collection.update_one(condition,{'$set':updated_one})

    def update_many(self,updated_many):
        for i in updated_many:
            self.update_one(i)

    def find_all(self):
        all_list=[]
        results=self.collection.find().sort('park_no',pymongo.ASCENDING)
        for result in results:
            del result['_id']
            all_list.append(result)
        return all_list

    def find_empty(self):
        empty_list=[]
        results=self.collection.find({'status':False})
        for result in results:
            del result['_id']
            empty_list.append(result)
        return empty_list

    def find_yours(self,plate):
        result=self.collection.find_one({'plate':plate})
        if result==None:
            return "Wrong plate number"
        del result['_id']
        return result

#testing example
park=park_db('127.0.0.1',27017)
park.all_init(dnn_result)
park.update_one(updated_one)
park.update_many(updated_many)
park.find_all()
park.find_empty()
park.find_yours(plate)