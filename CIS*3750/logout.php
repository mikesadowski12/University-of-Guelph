<?php
if(!isset($_COOKIE['unid'])){
    header('Location: /cfc/404error.php');
    die();
}

$url = "http://104.45.142.40:5000/api/Logout";

$ch = curl_init();

curl_setopt($ch, CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Authentication: '.$_COOKIE['token']));
curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query( array('Authentication' => 'TOKEN')));
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
$result = curl_exec($ch);
curl_close($ch);

echo $result;

$mydata = json_decode($result);
$status = $mydata->status;

echo "status: ".$status;


//DELETE current cookies
setcookie('teamCaptain',' ',time() - 3600, '/');
setcookie('token',' ',time() - 3600, '/');
setcookie('team',' ',time() - 3600, '/');
setcookie('unid',' ',time() - 3600, '/');


if($status == "true"){
  header('Location: /cfc/index.php');
} else {
  header('Location: /cfc/404error.php');
}

exit();
?>
