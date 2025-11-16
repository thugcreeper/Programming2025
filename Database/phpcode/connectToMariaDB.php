<html>

<title>Connect to mariaDB</title>

<?php
echo "Try to connect mariaDB...<br>";
?>
<?php
$user = '<username>';
$password = '<password>';
try{
$db = new

PDO('mysql:host=localhost;dbname=homework;charset=utf8',$user,$password);
$db ->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$db ->setAttribute(PDO::ATTR_EMULATE_PREPARES,false);
echo "Connect mariaDB successfully";
}
catch(PDOException $e){
Print "ERROR!: ". $e->getMessage();
die();
}

//$db = null;//結束連線
?>
</html>