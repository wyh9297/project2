import random
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys
import numpy as np
import Ui_Dialog

import serial
from time import sleep
import pymysql  # 引入pymssql模块
import time
from matplotlib import pyplot as plt
import matplotlib
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
def recv(serial):
    while True:
        data = serial.read_all()
        if data == '':
            continue
        else:
            break
        sleep(0.02)
    return data

def getData(serial):
    data = recv(serial)
    if data != b'':
        print(data)
        temp = "";
        id = "";
        if (len(data) == 3):
            temp = str(int(data[0]) - 48) + str(int(data[1]) - 48);
            id = str(int(data[2]) - 48);
        elif(len(data) == 6):
            rr=random.randint(1, 10)
            if(rr>5):
                temp = str(int(data[3]) - 48) + str(int(data[4]) - 48);
                id = str(int(data[5]) - 48);
            else:
                temp = str(int(data[0]) - 48) + str(int(data[1]) - 48);
                id = str(int(data[2]) - 48);
        # press=str(int(data[2])-48)+str(int(data[3])-48)+str(int(data[4])-48);
        if (temp != "00" and temp != ""):
            # print(temp," ",id)
            return [temp, id]
    return ['-1', '-1']


def conn_init():
    '''连接数据库并初始化'''
    connect = pymysql.connect(
        host='rm-uf614v1zjojkhd4tw7o.mysql.rds.aliyuncs.com',
        port=3306,
        user='wyh123',
        password='Ab123456',
        database="prodesign2"
    )  # 服务器名,账户,密码,数据库名
    if connect:
        print("连接成功!")
    cursor_obj = connect.cursor(pymysql.cursors.DictCursor)
    return [cursor_obj, connect]


if __name__ == '__main__':

    serial = serial.Serial('COM14', 19200, timeout=0.2)  # /devyUSB0
    if serial.isOpen():
        print("open success")
    else:
        print("open failed")
    temperature_1=[]
    temperature_2=[25,25,25,25]

    TimeList=[]
    count_time=0
    count1=1
    count2=1
    cursor_obj, connect = conn_init()
    while True:
        Strtemperature , Strid = getData(serial)
        temperature=int(Strtemperature)
        id=int(Strid)
        if(id==1 and temperature!= -1):
            temperature_1.append(temperature)
            count1=count1+1
        elif(id==2 and temperature!= -1):
            temperature_2.append(temperature)
            count2=count2+1
        TimeList.append(count_time)
        count_time=count_time+1;
        print(temperature," ",count1," ",id)
        if(count1!=0 and count1%5==0):
            x1=[]
            for i in range(1,len(temperature_1)+1):
                x1.append(i)
            x2=[]
            for i in range(1,len(temperature_2)+1):
                x2.append(i)
            y1=temperature_1
            y2=temperature_2
            plt.plot(x1,y1)
            plt.plot(x2,y2)
            plt.show()
            sleep(3)
            # plt.close()
            if count1>=10000:
                count1=0
                count2=0
        sleep(1)
        device_id = int(id)
        if (temperature != -1):
            print(temperature, device_id)
            time_stamp = str(int(time.time()*1000))  # 以字符串时间戳的形式储存时间
            # print(type(time_stamp))
            temperature=float(temperature)
            cursor_obj.execute("insert into device_temperature(device_id,temperature,time) \
        				value(%d,%.2f,%s)" % (device_id, temperature, time_stamp))
            connect.commit()


