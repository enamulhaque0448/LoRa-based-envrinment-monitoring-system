<?php
include 'db_connect.php';

$json = file_get_contents('php://input');
$data = json_decode($json);

if ($data) {
    $temperature = $conn->real_escape_string($data->temperature);
    $humidity = $conn->real_escape_string($data->humidity);
    $pressure = $conn->real_escape_string($data->pressure);

    $sql = "INSERT INTO readings (temperature, humidity, pressure) 
            VALUES ('$temperature', '$humidity', '$pressure')";

    if ($conn->query($sql) === TRUE) {
        http_response_code(200);
        echo "New record created successfully";
    } else {
        http_response_code(500);
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    http_response_code(400);
    echo "No data received";
}

$conn->close();
?>
