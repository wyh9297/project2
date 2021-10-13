import time
import pymysql
def testFun():
	a = 1
	b = 2
	return [a,b]
# print(float("-2.1"))
strTime = str(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())) 
print("%s" %strTime)
#x,y = testFun()
# print(x,y)
# time_stamp = time.time()
# print(time_stamp,str(time_stamp))
# connect = pymysql.connect(
# 	    host='rm-uf614v1zjojkhd4tw7o.mysql.rds.aliyuncs.com', 
# 	    port=3306,
# 	    user='wyh123',
# 	    password='Ab123456',
# 	    database="prodesign2"
#     ) #服务器名,账户,密码,数据库名
# if connect:
# 	print("连接成功!")
# cursor_obj = connect.cursor(pymysql.cursors.DictCursor)
# a = 1
# b = 28.0
# c = "1"
# cursor_obj.execute("select * from device_temperature")
# data1 = cursor_obj.fetchall()
# print("1:",data1)
# cursor_obj.execute("insert into device_temperature(device_id,temperature,time) \
# 				value(%d,%.2f,%s)" %(a,b,c))
# cursor_obj.fetchall()
# cursor_obj.execute("select * from device_temperature")
# data = cursor_obj.fetchall()
# connect.commit()
# print(data)