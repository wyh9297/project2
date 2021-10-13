import pymysql
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
cursor_obj.execute("delete from device_temperature")
connect.commit()