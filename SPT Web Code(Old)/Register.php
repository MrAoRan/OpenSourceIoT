<?php
header('Content-Type: text/html; charset=utf-8');//设置http响应头
$Username = $_POST['username'];
$Password = $_POST['password'];
$Password2 = $_POST['password2'];
$email = $_POST['email'];
//！！接下来四个变量填写自己的数据库信息：
    $servername = "localhost";//MySQL数据库的服务器名称或IP地址
	$username = "admin";//MySQL数据库的用户名
	$password = "admin";//MySQL数据库的密码
	$dbname = "server";//要连接的数据库的名称
//连接数据库：
	$conn = new mysqli($servername, $username, $password, $dbname);
//检测连接：
if ($conn->connect_error) {
    die("连接失败: " . $conn->connect_error);
}
$searchName = "select * from user where username='$Username'";
$searchNameResult = $conn->query($searchName);
$row = $searchNameResult->fetch_row();
$sql="insert into user values(null,'".$Username."','".$Password."','".$email."')";
if ($Username == "" or $Password == ""){
    echo '<script>alert("账号或密码不能留空");history.go(-1);</script>';
}
else if ($Password != $Password2){
    echo '<script>alert("你两次输入的密码不一致");history.go(-1);</script>';
}
else if ($row > 0){
    echo '<script>alert("已有人使用该账户名，请更换一个名字");history.go(-1);</script>';
}
else if ($conn->query($sql) === TRUE) {
    echo '<script>alert("用户注册成功");</script>';
    header("Refresh:0;url=index.html");
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();
?>