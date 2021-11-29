# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 13:20:11 2021

@author: vojoel
"""

from serial import Serial
import pandas as pd
from datetime import datetime
import time
import matplotlib.pyplot as plt

# Init
res = {}
res['Measurement'] = {}
res['Timestamp'] = {}


def save_data(res, maxit, timeint):
    '''
    Fills up res-dictionary with T-measurements from Arduino.

    Parameters
    ----------
    res : Resulting dictionary storing measurements and timestamps
    maxit : Positive integer, how many values to collect
    timeint : Positive float, how long to wait in seconds before collecting
              next data point
    Returns
    ----------
    Resulting array as DataFrame
    '''
    i = 0
    while(i<maxit):
        print("Iteration: " + str(i))
        arduino = Serial('COM5', 9600)
        line = arduino.readline()
        res['Measurement'][i] = float(line[0:len(line)].decode('utf-8'))
        res['Timestamp'][i] = str(datetime.now())
        arduino.close()
        time.sleep(timeint)
        i += 1
    return res

measurements = save_data(res, 50, 1)
pd.DataFrame(measurements).to_excel('Arduino_Task10.xlsx')






    
        
    
    
    
    
