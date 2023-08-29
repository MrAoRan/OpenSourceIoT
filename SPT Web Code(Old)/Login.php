<?php
header('Content-Type: text/html; charset=utf-8');
$Username = $_POST['username'];
$Password = $_POST['password'];
$servername = "localhost";
$username = "admin";
$password = "admin";
$dbname = "server";
$conn = new mysqli($servername,$username,$password,$dbname);
//检测连接：
if ($conn->connect_error){
    die("连接失败".$conn->connect_error);
}
//检查数据库：
$sql = "select userPwd from user where username='".$Username."'";
$allSql = "select * from user where username='".$Username."'";
$result = $conn->query($sql);
$allResult = $conn->query($allSql);
if ($Username == "" or $Password == ""){
    echo '<script>alert("账号或密码不能留空");history.go(-1);</script>';
}
else if($result->num_rows > 0){
    $row = $result->fetch_row();
    $db_userpwd = $row[0];
    if($db_userpwd==$Username){
        echo '欢迎用户'.$Username.'登录';
    }else{
        echo '<script>alert("账号或密码错误"); history.go(-1);</script>';
    }
}else {
    echo '<script>alert("用户不存在"); history.go(-1);</script>';
}
$conn->close();
?>