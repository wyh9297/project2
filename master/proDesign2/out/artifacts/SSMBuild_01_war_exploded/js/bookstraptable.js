$(document).ready(function(){
    $("#table_page").bootstrapTable({
        columns:[{
            field:'id',
            title:'Id'
        },{
            field:'Name',
            title:'用户名'
        },{
            field:'passWord',
            title: '密码'
        },{
            field:'Role',
            title:'角色'
        },{
            field:'option',
            title:'操作'
        },],
        formatLoadingMessage:function () {
            return "";
        },
    });
});