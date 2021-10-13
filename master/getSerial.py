import serial
from time import sleep
import pymysql #引入pymssql模块
import time

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
    data =recv(serial)
    if data != b'' :
        # print(data)
        temp="";
        id="";
        if(len(data) == 3) :
            temp=str(int(data[0])-48)+str(int(data[1])-48);
            id=str(int(data[2])-48);
        # press=str(int(data[2])-48)+str(int(data[3])-48)+str(int(data[4])-48);
        if(temp != "00" and temp!=""):
            # print(temp," ",id)
            return [temp,id]
    return ['-1','-1']

def conn_init():
	'''连接数据库并初始化'''
	connect = pymysql.connect(
	    host='rm-uf614v1zjojkhd4tw7o.mysql.rds.aliyuncs.com', 
	    port=3306,
	    user='wyh123',
	    password='Ab123456',
	    database="prodesign2"
    ) #服务器名,账户,密码,数据库名
	if connect:
		print("连接成功!")
	cursor_obj = connect.cursor(pymysql.cursors.DictCursor)
	return [cursor_obj,connect]
    

if __name__ == '__main__':
	serial = serial.Serial('COM14', 19200, timeout=0.5)  #/devyUSB0
	if serial.isOpen():
		print("open success")
	else:
		print("open failed")
	cursor_obj,connect = conn_init()
	while True:
		temperature,id = getData(serial)
		device_id = int(id)
		temperature = float(temperature)
		if(temperature != -1 and id!=-1):
			print(temperature,device_id)
			time_stamp = str(int(time.time()*1000))#以时间戳字符存储并转为java时间戳格式 
			print(time_stamp,type(time_stamp))
			# print(type(time_stamp))
			cursor_obj.execute("insert into device_temperature(device_id,temperature,time) \
				value(%d,%.2f,%s)"%(device_id,temperature,time_stamp))
			connect.commit()
			sleep(5)

