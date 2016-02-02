<!DOCTYPE html>
<!-- saved from url=(0051)http://getbootstrap.com/examples/navbar-static-top/ -->
<html lang="en"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="/cfc/Images/navicon.ico">

    <title>Trick Or Eat Info</title>
    
    <!-- Main CSS -->
    <link href="/cfc/Includes/css/main.css" rel="stylesheet">

    <!-- Bootstrap core CSS -->
    <link href="/cfc/Includes/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="/cfc/Includes/css/navbar-static-top.css" rel="stylesheet">

    <!-- Just for debugging purposes. Don't actually copy these 2 lines! -->
    <!--[if lt IE 9]><script src="../../assets/js/ie8-responsive-file-warning.js"></script><![endif]-->
    <script src="/cfc/Includes/js/ie-emulation-modes-warning.js"></script>

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>

  <?php include "./Includes/header.inc"; ?>


    <div class="container" style="color:white">
      <div class="col-lg-12" align="center"><img src="/cfc/Images/torSiteBanner.png" width=100%/></div>
      <h1 style="none;padding:0;margin0;font-size:1px;">&nbsp;</h1>
      <hr>
        <div class="row">
          
          <!-- SECTION 2 -->
          <div class="col-xs-12">
          	<div class="form-group" align="center">
              <h1 class="cfc-heading">Trick-or-Eat 2015</h1>
			<div id='container' align="left">
 				<img src="/cfc/Images/alpaca.jpg" width="250" align="right"/>
			 <p class="cfc-font">
				Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas pellentesque molestie sapien, rhoncus tempus justo tincidunt eget. Aliquam erat volutpat. Suspendisse vehicula ornare dui, in mattis magna rhoncus laoreet. In id urna egestas, interdum neque a, euismod mi. Donec iaculis ligula ante, ut vehicula libero eleifend ut. Nam rhoncus est eget massa efficitur pharetra. Nullam a ex nec arcu dignissim egestas nec nec erat. Suspendisse eleifend semper vulputate. Vivamus hendrerit nisl ut ante auctor, ac sodales sem semper. Nunc pellentesque urna nec lacinia elementum. Vestibulum nec massa urna. Suspendisse eleifend semper vulputate. Vivamus hendrerit nisl ut ante auctor, ac sodales sem semper. Nunc pellentesque urna nec lacinia elementum. Vestibulum nec massa urna. <br/><br/>
				Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas pellentesque molestie sapien, rhoncus tempus justo tincidunt eget. Aliquam erat volutpat. Suspendisse vehicula ornare dui, in mattis magna rhoncus laoreet. In id urna egestas, interdum neque a, euismod mi. Donec iaculis ligula ante, ut vehicula libero eleifend ut. Nam rhoncus est eget massa efficitur pharetra. Nullam a ex nec arcu dignissim egestas nec nec erat. Suspendisse eleifend semper vulputate. Vivamus hendrerit nisl ut ante auctor, ac sodales sem semper. Nunc pellentesque urna nec lacinia elementum. Vestibulum nec massa urna. 
			 </p><br/><br/>
			<div align="center" style="font-size: 22px;">
        <?php
        if(!isset($_COOKIE['unid'])){
			    echo 'Please <a href="/cfc/login.php">login</a> to register for this event';
        } else {
          echo '<a href="/cfc/teamCreate.php"><button type="button" class="btn btn-success" style="font-size:20px;"><span class="glyphicon glyphicon-ok"></span> Register Team</button></a>';
          echo '<a href="/cfc/waiver.php"><button type="button" class="btn btn-success" style="margin-left:30px; font-size:20px;"><span class="glyphicon glyphicon-ok"></span> Register For Event</button></a>';
        }
        ?>
			  <br/><br/>
			  <button type="button" class="btn btn-info" onclick="history.go(-1);return TRUE;" style="font-size:20px;">
                <span class="glyphicon glyphicon-arrow-left"></span> Go Back
              </button>
			</div>
			
			</div>
            </div>
          </div>
    </div> 

    <?php include"./Includes/footer.inc"; ?>

    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="/cfc/Includes/js/jquery.min.js"></script>
    <script src="/cfc/Includes/js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="/cfc/Includes/js/ie10-viewport-bug-workaround.js"></script>
  

</body></html>
