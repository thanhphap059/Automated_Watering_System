<?php
// connect to database
ini_set('display_errors', 1); error_reporting(-1);
$servername = "localhost";
$user = "nt";
$password = "132001";
$dbname = "final";
$conn = mysqli_connect($servername,$user,$password,$dbname);
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  die();
}
?>


