<?php
class dht11{
 public $link='';
 function __construct($temperature, $humidity,$soilmositure,$soilmositure_2){
  $this->connect();
  $this->storeInDB($temperature, $humidity,$soilmositure,$soilmositure_2);
 }
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'av_2030') or die('Cannot select the DB');
 }
 function storeInDB($temperature, $humidity,$soilmositure,$soilmositure_2){
//$query="INSERT INTO 'sih_2020'(humidity,temperature,soilmositure,soilmositure_2) VALUES ('".$humidity."', '".$temperature."','".$soilmositure."','".$soilmositure_2."')";
$query="INSERT INTO `sih_2020` (`temperature`, `humidity`, `soilmositure`,`solimositure_2`) VALUES ('".$humidity."', '".$temperature."','".$soilmositure."','".$soilmositure_2."')";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
}
if($_GET['temperature'] != ' ' and  $_GET['humidity'] != ' ' and  $_GET['soilmositure'] != ' ' and  $_GET['soilmositure_2'] != ' '){
 $dht11=new dht11($_GET['temperature'],$_GET['humidity'],$_GET['soilmositure'],$_GET['soilmositure_2']);
}
?>