<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  Created by IntelliJ IDEA.
  User: 陆镇涛
  Date: 2020/8/27
  Time: 19:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8" isELIgnored="false" %>
<%@ page import="java.io.*,java.util.*" %>
<!DOCTYPE html>
<head>
    <title>设备详情</title>
    <link href="https://cdn.staticfile.org/twitter-bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%response.setIntHeader("Refresh", 5);%><%--每五秒刷新一次--%>
<div class="container">
    <div class="row">
        <div style="text-align: center">
            <%--            <h1 class="display-1">--%>
            设备名：${device.device_name}
            <%--            </h1>--%>
        </div>

    </div>
    <div class="row ">
        <div class="col-md-12 column">
            <table class="table table-hover table-striped">
                <thead>
                <tr>
                    <th>设备温度/℃</th>
                    <th>检测时间</th>
                </tr>
                </thead>

                <tbody>
                <c:forEach var="device_temperature" items="${device_temperatures}">
                    <tr>
                        <td>${device_temperature.temperature}</td>
                            <%--                        <td>${book.bookCounts}</td>--%>
                        <td>${device_temperature.time}</td>
                    </tr>
                </c:forEach>
                </tbody>
            </table>
        </div>
    </div>
    <div>
<%--        <a href="/book/reader">返回主页面</a>--%>
    </div>
</div>

</body>
</html>
