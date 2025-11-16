<html>
    <head>
    <title>Show all data of employee</title>
    <style>
        <?php include 'css/table.css'; ?>
        
    </style>
    </head>
    <?php
    include_once 'connectToMariaDB.php';//引入連線檔案

    $sqlQuery="SELECT * FROM employee";;
    $results=$db->query($sqlQuery);
    echo "<h3>Employee Table</h3>";
    echo "<table>
            <tr><th>ID</th><th>person_name</th><th>street</th><th>city</th></tr>";
    while($row=$results->fetch(PDO::FETCH_ASSOC)){
        echo "<tr>";
        echo "<td>".$row['ID']."</td>";
        echo "<td>".$row['person_name']."</td>";
        echo "<td>".$row['street']."</td>";
        echo "<td>".$row['city']."</td>";
        echo "</tr>";
    }
    echo "</table>";
    if(!$results){
        echo "Error in query";
        exit;
    }
    $db = null;//結束連線
    ?>
</html>