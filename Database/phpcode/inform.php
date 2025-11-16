<?php
include "db _conn.
$no = "
$query = ("select * from student where no = ?");
$stmt = $db ->prepare($query);
$error = $stmt ->execute(array($no));
$result = $stmt ->fetchAll();//回傳物件，將 $stmt 的資料取出來存成陣列，若無資料則回傳 NULL 。
//以上寫法是為了防止「 sql injection 」
for($i=0; $i<count($result ); $i++)
echo " dept: result [$i]['dept'].'
"no:". result [$i]['no'].'
" result [$i]['name'].'
"club:". result [$i ]['club'].'
'<br>';
//一般直接執行而沒有預處理的寫法
$query = ("select * from student where no = 00557888");
$stmt = $db->query($query);
$result = $stmt ->fetchAll();
?>