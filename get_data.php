<?php
include 'db_connect.php';

$sql = "SELECT id, temperature, humidity, pressure, reg_date 
        FROM readings 
        ORDER BY id DESC 
        LIMIT 50";

$result = $conn->query($sql);

$data = array();

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
}

$conn->close();

$data = array_reverse($data);

header('Content-Type: application/json');
echo json_encode($data);
?>
