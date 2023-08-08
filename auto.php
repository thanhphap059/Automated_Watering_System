<?php
ini_set('display_errors', 1); error_reporting(-1);
// doc du lieu tu website gui ve
include("config.php");

$solid = $_POST["doAM"];
$temp  = $_POST["nhietDo"];
$time  = $_POST["time"];

if ($temp == NULL)
  $temp = 0;

if ($solid == NULL)
  $solid = 0;

if ($time == NULL)
  $time = 0;

$timestamp = strtotime($time);
$hour = date('H', $timestamp);
$minute = date('i', $timestamp);  
$second = date('s', $timestamp);  

echo $hour;


$sql = "UPDATE auto
SET  solid = $solid, 
temp = $temp, 
time = '$time',
hour = $hour,
minute = $minute,
second = $second
WHERE stt = 1"; 

if(!mysqli_query($conn,$sql)){
  echo "Error: " ,mysql_error($conn);
}

// ngat ket noi voi database
mysqli_close($conn);
?>