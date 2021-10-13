$(document).ready(function(){
    $("#table_page").bootstrapTable({
        columns:[{
            field:'id',
            title:'Id'
        },{
            field:'ISBN',
            title:'isdn'
        },{
            field:'BookName',
            title:'图书名称'
        },{
            field:'Author',
            title:'作者'
        },{
            field:'Publish',
            title:'出版社'
        },{
            field:'UnitPrice',
            title:'单价'
        },{
            field:'Status',
            title:'状态'
        },{
            field:'Operation',
            title:'操作'
        },],
        formatLoadingMessage:function () {
            return "";
        },
    });
});