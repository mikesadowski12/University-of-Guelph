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

    <title>Events</title>
   
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


    <div class="container" style="color:white;">
      <div class="row">

        <!-- SECTION 2 -->
        <div class="col-xs-12">
          <?php

          /*used personal Database code here because Database team had different thoughts on how
            things worked therefore setup some personal things that way site would function as
            we needed/wanted it to for the final Demo.*/
          include ('./Includes/php/registeredEvent-get.php');

          if($registered == "true"){
              echo '
              <h1>My Events</h1>
              <hr>
              <div style="width:350px; margin: 0 auto; font-size:22px;">
                <ol style="float:left;">
                  <li><a class="cfc-link" href="/cfc/Event/info.php">Trick-Or-Eat 2015</a></li>';
                echo '</ol>
              </div></div>

              <div class="col-xs-12">
              <h1 style="text-align:left; display:inline;">Current Events</h1>
              <hr>
              <div style="width:350px; margin: 0 auto; text-align:left; font-size:22px;">
                <ol style="float:left;">
                  <li><a class="cfc-link" href="#">Fake Event 1</a></li>
                  <li><a class="cfc-link" href="#">Fake Event 2</a></li>
                </ol>
              </div>
              ';
          } else {
              echo '
              <h1>Current Events</h1>
              <hr>
              <div class="cfc-font">
                <div style="width:350px; margin: 0 auto; text-align:left; font-size:22px;" align="center">
                  <ol style="float:left;">
                    <li><a class="cfc-link" href="/cfc/trickOrEatInfo.php"><font size="5">Trick-Or-Eat 2015</font></a></li>
                    <li><a class="cfc-link" href="#"><font size="5">Fake Event 1</font></a></li>
                    <li><a class="cfc-link" href="#"><font size="5">Fake Event 2</font></a></li>
                  </ol>
                </div>
              </div>
              ';
          }
          ?>
        </div>
      </div> 
      <?php include"./Includes/footer.inc"; ?>
    </div> <!-- /container -->

    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="/cfc/Includes/js/jquery.min.js"></script>
    <script src="/cfc/Includes/js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="/cfc/Includes/js/ie10-viewport-bug-workaround.js"></script>
  

</body></html>
