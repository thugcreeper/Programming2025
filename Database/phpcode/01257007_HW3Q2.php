<html>
    <head>
        <title>01257007 DB Hw3 Q2</title>
        <p>Write a PHP program to show all the content of the “employee” relation for those who live in Taipei. The data should be displayed in a table. (注意：需用prepared statement的寫法，部分程式可參考教學手冊第30、32、37頁所示) 
        (1)	Give the program listing.
        (2)	Capture the screen which shows the answer based on your database content. (Your answer of Question 1(4).) (注意：畫面必須擷取到網址)
        </p>
        <h1>Show all the content of the “employee” relation for those who live in Taipei</h1>
        <style>
            <?php include 'css/table.css'; ?>
        </style>
    </head>
    <?php
    include_once 'connectToMariaDB.php';//引入連線檔案
    //題目要求:show all the content of the “employee” relation 
    // for those who live in Taipei. The data should be displayed in a table. 
    echo "<h3>Employee who live in Taipei</h3>";
    echo "<table>
            <tr><th>ID</th><th>person_name</th><th>street</th><th>city</th></tr>";
    $city='台北市';
    $sqlQuery="SELECT * FROM employee WHERE city=?";
    $stmt = $db->prepare($sqlQuery);//要prepare statement
    $stmt->execute(array($city));
    $results=$stmt->fetchAll();
    
    for($i=0;$i<count($results);$i++){
        echo "<tr>";
        echo "<td>".$results[$i]['ID']."</td>";
        echo "<td>".$results[$i]['person_name']."</td>";
        echo "<td>".$results[$i]['street']."</td>";
        echo "<td>".$results[$i]['city']."</td>";
        echo "</tr>";
    }
    echo "</table>";
    if(!$results){
        echo "No employee live in Taipei";
        exit;
    }
    $db = null;//結束連線
    ?>
</html>