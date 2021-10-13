#coding:utf-8

# 导入matplotlib模块并使用Qt5Agg
import matplotlib
matplotlib.use('Qt5Agg')
# 使用 matplotlib中的FigureCanvas (在使用 Qt5 Backends中 FigureCanvas继承自QtWidgets.QWidget)
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from PyQt5 import QtCore, QtWidgets,QtGui
from PyQt5.QtWidgets import *
import matplotlib.pyplot as plt
import sys
import numpy as np
import pymysql
import pandas as pd
from numpy import *
import time
temperatures1=[]
temperatures2=[]
times=[]
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


class App(QtWidgets.QDialog):
    def __init__(self, parent=None):
        # 父类初始化方法
        super(App, self).__init__(parent)

        self.initUI()

    def initUI(self):
        self.setWindowTitle('温度曲线')
        # 几个QWidgets
        self.figure = plt.figure()
        self.canvas = FigureCanvas(self.figure)
        self.button_plot = QtWidgets.QPushButton("绘制函数图像")
        self.line = QLineEdit()  # 输入函数
        self.resize(1000,550)
        # 连接事件
        self.plot_()
        self.button_plot.clicked.connect(self.plot_)

        # 设置布局
        layout = QtWidgets.QVBoxLayout()
        layout.addWidget(self.canvas)
        # layout.addWidget(self.line)
        # layout.addWidget(self.button_plot)
        self.setLayout(layout)

    # 连接的绘制的方法
    def plot_(self):
        ax = self.figure.add_axes([0.1, 0.1, 0.8, 0.8])
        ax.clear()  # 每次绘制一个函数时清空绘图
        x = times
        y1 = temperatures1  # 使用了eval函数
        y2 = temperatures2
        ax.plot(x, y1)
        ax.plot(x,y2)
        self.canvas.draw()

if __name__ == '__main__':
    cursor_obj, connect = conn_init()
    data = pd.read_sql("SELECT * FROM device_temperature WHERE device_id=1",con=connect)
    # data['device_id'] = 1
    # print(data)
    L1=data
    print(L1)
    # data['device_id'] = 2
    # print(data)
    data2 = pd.read_sql("SELECT * FROM device_temperature WHERE device_id=2",con=connect)
    L2=data2
    # print(L2['temperature'])
    data.head()
    data_array1=np.array(L1['temperature'])
    data_list1=data_array1.tolist()
    time_array=np.array(L1['time'])
    time_list=time_array.tolist()
    print(time_list)
    for i in range(0,10):
        temperatures1.append(data_list1[i])
        qq=int(time_list[i])/1000
        now=time.localtime(qq)
        print(now)
        strTime=str(now.tm_min)+"m"+str(now.tm_sec)+"s"
        times.append(strTime)
    print(temperatures1)
    data_array2 = np.array(L2['temperature'])
    data_list2 = data_array2.tolist()
    print(data_list2)
    for i in range(0, 10):
        temperatures2.append(data_list2[i])
    print(temperatures2)
    app = QtWidgets.QApplication(sys.argv)
    main_window = App()
    main_window.show()
    app.exec()
