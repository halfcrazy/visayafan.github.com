// 鼠标放在tab上不用点击自动切换
// $('.nav-tabs > li > a').hover( function(){
//     $(this).tab('show');
// });

$(function () {
    var activeTab = $('[href=' + location.hash + ']');
    activeTab && activeTab.tab('show');
});
