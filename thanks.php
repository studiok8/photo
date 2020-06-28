<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>ありがとう</title>
</head>

<?php

$dsn = 'mysql:host=mysql2011.db.sakura.ne.jp;dbname=studiok_315w;charset=utf8';
$user = "studiok"; // データベース ユーザ名(初期アカウント名)
$pass = "rintarou1974"; // 接続パスワード変更

$dbh = new PDO($dsn, $user, $pass);
$dbh->query('SET NAMES utf8');
?>

<?php
if (!empty($_POST["onamae"])) {
            $name = $_POST['onamae'];
        }
        
?>
<?php
if (!empty($_POST["email"])) {
            $email = $_POST['email'];
        }
        
?>
<?php
if (!empty($_POST["goiken"])) {
            $goiken = $_POST['goiken'];
        }
        
?>

<body>
<h1>受付完了</h1>
 
<?php 
echo $name."さん、お問い合わせありがとうございます。";
echo '<br>';
echo "メールの返信をお待ちください&#128075;"; 
?>

<?php $sql = 'INSERT INTO coment(oname,email,goiken)VALUES("'.'onamae'.'","'.'email'.'","'.'goiken'.'")';
$stmt = $dbh->prepare ($sql);
$stmt->execute();

$dbh = null;
?>
</body>
</html>