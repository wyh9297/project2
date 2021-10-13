<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  Created by IntelliJ IDEA.
  User: 陆镇涛
  Date: 2020/8/27
  Time: 19:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>设备主页</title>
    <link href="https://cdn.staticfile.org/twitter-bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<div class="container">

    <div class="row ">
        <div class="col-md-12 column">
            <table class="table table-hover table-striped">
                <thead>
                <tr>
                    <th>设备编号</th>
                    <th>设备名称</th>
                    <th>当前温度</th>
                    <th>状态</th>
                    <%--                    <th>书籍详情</th>--%>
                    <th>操作</th>

                </tr>
                </thead>

                <tbody>
                <c:forEach var="device" items="${devices}" >
                    <tr>
                        <td>${device.device_id}</td>
                        <td>${device.device_name}</td>
                        <td>${temperatures.get(device.device_id-1)}</td>
                        <td>${warning.get(device.device_id-1)}</td>
                            <%--                            <td>${book.detail}</td>--%>
                        <td>
<%--                            <a href="${pageContext.request.contextPath}/book/toUpdate?id=${book.bookID}">修改</a>--%>
<%--                            &nbsp; | &nbsp;--%>
<%--                            <a href="${pageContext.request.contextPath}/book/deleteBook/${book.bookID}">删除</a>--%>
<%--                            |--%>
                            <a href="${pageContext.request.contextPath}/deviceDetail?id=${device.device_id}">详情</a>
                        </td>
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
