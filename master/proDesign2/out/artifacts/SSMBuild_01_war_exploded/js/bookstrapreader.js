﻿$(document).ready(function(){
    $("#table_page1").bootstrapTable({
        columns:[{
            field:'id',
            title:'Id'
        },{
            field:'Type',
            title:'类型'
        },{
            field:'Name',
            title:'姓名'
        },{
            field:'Age',
            title:'年龄'
        },{
            field:'Sex',
            title:'性别'
        },{
            field:'Phone',
            title:'电话'
        },{
            field:'Dept',
            title:'所在地'
        },{
            field:'RegDate',
            title:'日期'
        },{
            field:'MaxLendTime',
            title:'最大借阅时间'
        },{
            field:'Option',
            title:'操作'
        },],
        formatLoadingMessage:function () {
            return "";
        },
    });
});