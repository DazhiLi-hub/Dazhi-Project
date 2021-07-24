import torch

class PUF_data:
    def __init__(self,path,sample_rate):
        self.path=path
        self.sample_rate=sample_rate
        self.training_set=([],[])
        self.testing_set=([],[])

    def get_data(self):
        with open(self.path,'r') as file:
            lines=file.readlines()
            dataset = [[] for i in range(len(lines))]
            for i in range(len(dataset)):
                dataset[i][:]=(item for item in lines[i].strip().split(','))
            for i in range(len(dataset)):
                dataset[i]=dataset[i][:-1]+dataset[i][-1].split(';')
            for x in range(len(dataset)):
                for y in range(len(dataset[0])):
                    dataset[x][y] = float(dataset[x][y])
            border=int(self.sample_rate*len(dataset))
            training_set_data=dataset[:border]
            testing_set_data=dataset[border:]
            training_set_feed=[]
            training_set_target=[]
            testing_set_feed=[]
            testing_set_target=[]
            for i in range(len(training_set_data)):
                training_set_feed.append(training_set_data[i][:-1])
                if (training_set_data[i][-1] == -1):
                    training_set_target.append(float(0))
                elif (training_set_data[i][-1] == 1):
                    training_set_target.append(float(1))
            for i in range(len(testing_set_data)):
                testing_set_feed.append(testing_set_data[i][:-1])
                if(testing_set_data[i][-1]==-1):
                    testing_set_target.append(float(0))
                elif(testing_set_data[i][-1]==1):
                    testing_set_target.append(float(1))
            self.training_set=(torch.tensor(training_set_feed),torch.tensor(training_set_target))
            self.testing_set=(torch.tensor(testing_set_feed),torch.tensor(testing_set_target))

    def get_len(self):
        return len(self.training_set[1])+len(self.testing_set[1])