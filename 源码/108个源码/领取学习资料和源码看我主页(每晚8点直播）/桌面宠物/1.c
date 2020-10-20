<!DOCTYPE html>
<html>

 <head>
 <meta charset="UTF-8">
 <title>刮刮奖</title>
 <style type="text/css">
 * {
 margin: 0;
 padding: 0;
 }
 
 .box {
 width: 500px;
 height: 500px;
 margin: 0 auto;
 position: relative;
 background: #00BFFF;
 }
 
 #prize {
 width: 300px;
 height: 100px;
 position: absolute;
 top: 50%;
 left: 50%;
 margin: -50px 0 0 -150px;
 background: #fff;
 font-family: "微软雅黑";
 font-size: 40px;
 text-align: center;
 line-height: 100px;
 -webkit-user-select: none;
 }
 
 #myCanvas {
 position: absolute;
 top: 50%;
 left: 50%;
 margin: -50px 0 0 -150px;
 }
 </style>
 </head>

 <body>
 <div class="box">
 <div id="prize"></div>
 <canvas id="myCanvas" width="300" height="100"></canvas>
 </div>
 </body>
 <script type="text/javascript">
 //获取对象
 var textArr = ["一等奖", "二等奖", "三等奖", "谢谢惠顾", "再来一次"];
 var prize = document.getElementById("prize");
 var num = Math.random() * 100;
 if (num <= 60) {
 prize.innerText = textArr[3];
 } else if (num <= 70) {
 prize.innerText = textArr[4];
 } else if (num <= 80) {
 prize.innerText = textArr[2];
 } else if (num <= 90) {
 prize.innerText = textArr[1];
 } else if (num <= 100) {
 prize.innerText = textArr[0];
 }
 var myCanvas = document.getElementById("myCanvas");
 // 搭建环境
 var cxt = myCanvas.getContext("2d");
 cxt.globalAlpha = 1;
 cxt.fillStyle = "#ccc";
 cxt.fillRect(0, 0, 300, 100);
 var txt = "刮刮奖";
 cxt.fillStyle = "#000";
 cxt.font = "30px 微软雅黑";
 cxt.textAlign = "center";
 cxt.textBaseline = "middle";
 cxt.fillText(txt, 150, 50, 300);
 var mX, mY;
 var flag = false;
 myCanvas.onmousedown = function(e) {
 flag = true;
 mX = e.offsetX;
 mY = e.offsetY;
 drawArc(mX, mY);
 }
 document.body.onmousemove = function(e) {
 if (flag == true) {
 mX = e.offsetX;
 mY = e.offsetY;
 drawArc(mX, mY);
 }
 }
 document.body.onmouseup = function() {
 flag = false;
 sayPrize();
 }

 function drawArc(x, y) {
 cxt.globalCompositeOperation = "destination-out"; //相交部分不显示
 cxt.beginPath();
 cxt.fillStyle = "white";
 cxt.moveTo(x, y);
 cxt.arc(x, y, 10, 0, 2 * Math.PI);
 cxt.fill();
 }

 function sayPrize() {
 var myImg = cxt.getImageData(70, 30, 160, 40);
 // var myImg = cxt.getImageData(93, 37, 40, 30);
 // 设置像素点的颜色
 var num = 0;
 var max = myImg.data.length / 4;
 for (var i = 0; i < myImg.data.length; i += 4) {
 if (myImg.data[i + 3] <= 200) {
 num++;
 }
 }
 //2/3*myImg.data.length/4
 if (num >= max * 0.6) {
 alert("恭喜您,获得：" + prize.innerText);
 }
 }
 </script>

</html>