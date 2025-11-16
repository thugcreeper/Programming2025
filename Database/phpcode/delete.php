<?php
include "db_conn.php";
//使用 prepare 的寫法
$stmt = $db->prepare("delete from student where no=?");
$no = "00557888";
$result = $stmt ->execute(array($no));

//直接刪除的寫法
$result = $db ->exec("delete from student where no='00557888'");
?>