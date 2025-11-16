<html>

<title>Insert data</title>

<?php

include_once 'connectToMariaDB.php';//引入連線檔案
$ID=8;
$person_name='小白';
$street='雙林路';
$city='台北市';

try{
    //使用預處理寫法是為了防止 sql injection 
    //prepare
    $query = ("insert into employee values(?,?,?,?)");
    // stmt 對應到一個 欲執行 SQL 的物件。
    $stmt = $db->prepare($query);
    //execute
    $result = $stmt->execute(array($ID,$person_name,$street,$city));
}
catch (PDOException $e) {
    echo "Error: " . $e->getMessage();
}
include_once 'showEmployee.php';//引入顯示資料檔案
$db = null;//結束連線
?>
</html>