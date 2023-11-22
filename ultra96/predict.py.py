import os, warnings
from pynq import PL
from pynq import Overlay
from pynq import allocate 
import numpy as np
from numpy.fft import fft, ifft

from standardisations import means, stds
from random import randint


def fft_funct(x, n): 
    Ts = 0.05
    Sr = 1/Ts
    
    t = np.arange(0,(n)*Ts, Ts)
    
    X = fft(x)
    N = len(X)
    
    n = np.arange(N)
    T = N/Sr
    freq = n/T
    
    return np.abs(X)

def pre_process(reading):
    data = []
    temp = np.zeros((14,30))

    #fill with mean if there isnt enough data
    if len(reading) < 8*30:         
        num_readings = int(len(reading)/8)
        reading = np.array(reading)
        reading = reading.reshape((num_readings, 8))
        
        column_means = np.mean(reading, axis=0)
        new_row = np.array([column_means]).astype(int)
        for i in range(len(reading), 30):
            reading = np.vstack((reading, new_row))
        reading = reading.flatten()
        
    #get the first 30 readings
    reading = reading[0:8*30]
    
    count = 0
    for i in range(30):
        for j in range(8):
            temp[j][i] = reading[count]
            count += 1
            
    for j in range(6):
        data.extend(temp[j])

    #fft
    for j in range(6):
        data.extend(fft_funct(temp[j], 30))  
    
    #standardise
    data = np.array(data).reshape(12,30)
    count = 0

    for i in range(30): 
        for j in range(12): 
            data[j][i] = ((data[j][i] - means[j])/stds[j])*(2**20)

    data = data.flatten().tolist()
    return data

def predict_action(readings, ol):
    ol.ip_dict.keys()
    
    dma = ol.axi_dma_0
    dma_send = dma.sendchannel
    dma_recv = dma.recvchannel

    ip = ol.model_0
    
    #start the ip
    CONTROL_REGISTER = 0x0
    ip.write(CONTROL_REGISTER, 0x81)
    ip.register_map
    
    data = pre_process(readings)
    
    #allocate buffer space
    data_size = 12*30
    input_buffer = allocate(shape=(data_size,), dtype=np.int32)
    output_buffer = allocate(shape=(1,), dtype=np.uint32)
    
    for i in range(data_size): 
        input_buffer[i] = data[i]
    
    #send the data

    #start the dma
    dma_send.start()
    dma_recv.start()

    dma_send.transfer(input_buffer)
    dma_send.wait()
    dma_recv.transfer(output_buffer)
    dma_recv.wait()

    #read the action
    action = output_buffer[0]
    #print(action)
    del input_buffer, output_buffer
    dma.register_map.MM2S_DMACR.Reset = 1
    
    return action
