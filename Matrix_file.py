import numpy as np
def numpy_to_file(filename,M,f):
    #file=open(filename,"w+")
    (x,y)=M.shape
    temp_s=str(x)+" "+str(y)
    #file.write(temp_s)
    np.savetxt(filename,M,delimiter=' ',fmt=f,header=temp_s,comments='')
def str_to_vec(string):
    return list(map(float,string.split(' ')))
def file_to_numpy(filename):
    file=open(filename)
    strings=file.readlines()
    res=np.array([str_to_vec(strings[1])])
    for i in range(2,len(strings)):
        temp=np.array([str_to_vec(strings[i])])
        res=np.concatenate((res,temp),axis=0)
    return res
    
    
