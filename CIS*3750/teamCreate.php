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

    <title>Create Team</title>

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


    <div class="container">
      <h1 class="well">Create a Team</h1>
      <div class="col-lg-12 well">
        <div class="row">
          <form name="waiver-form" method="POST" action="/cfc/Includes/php/tempTeamCookie-request.php">
            <input type="hidden" name="source" value="register"/>
            <div class="col-sm-12">
              <div class="row" style="font-size:20px;">
                <div class="form-group">
                  <label>Team Name</label>
                  <input type="text" placeholder="Enter Team Name Here.." class="form-control" name="teamName" required="" autofocus="" style="width:400px;">
                </div>
                <div class="form-group" style="margin-bottom:0;">
                  <label>Team Privacy:</label>
                </div>
                <div class="form-group">
                  <input type="radio" name="privacy" value="1" checked>Public <br/>
                  <input type="radio" name="privacy" value="0">Private <br/>
                </div>
              </div>
              <button type="button" class="btn btn-lg btn-info" data-toggle="modal" onclick="declinePage()">Cancel</button>
              <button type="submit" class="btn btn-lg btn-info">Next</button></a>
            </div>
          </form>
        </div>
      </div>
    </div> <!-- container -->

    <div class="container">
      <?php include"./Includes/footer.inc"; ?>
    </div>

    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="/cfc/Includes/js/jquery.min.js"></script>
    <script src="/cfc/Includes/js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="/cfc/Includes/js/ie10-viewport-bug-workaround.js"></script>

    <script type="text/javascript">
    function declinePage(){
      if(confirm('Canceling now you will lose all progress in the application process. Is this okay?')){
        window.location = '/cfc/events.php';
      }else {
        return false;
      }
    }
    </script>

</body></html>
