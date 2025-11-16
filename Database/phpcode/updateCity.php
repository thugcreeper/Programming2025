<html>
<title>Edit Employee Data</title>
<h1>將city統一加上"市"</h1>
<?php
    include_once 'connectToMariaDB.php';//引入連線檔案
    $query = "
    UPDATE employee
    SET city = CONCAT(city, '市')
    WHERE city NOT LIKE '%市';
    ";
    $stmt = $db ->prepare($query);
    $result =$stmt ->execute();
    include_once 'showEmployee.php';
    $db=null;//結束連線
?>
</html>