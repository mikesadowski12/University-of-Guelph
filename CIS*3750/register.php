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

    <title>Sign Up</title>

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
      <h1 class="well">Sign Up</h1>
      <div class="col-lg-12 well">
        <div class="row">
          <form name="signup-form" method="POST" action="/cfc/Includes/php/signup-request.php">
            <div class="col-sm-12">
              <div class="row">
                <div class="col-sm-6 form-group">
                  <label>First Name</label>
                  <input type="text" placeholder="Enter First Name Here.." class="form-control" name="firstName" required="" autofocus="">
                </div>
                <div class="col-sm-6 form-group">
                  <label>Last Name</label>
                  <input type="text" placeholder="Enter Last Name Here.." class="form-control" name="lastName" required="">
                </div>
              </div>
              <div class="form-group">
                <label style="color:red"><?php echo $_GET['error']; ?></label><br/>
                <label>Email Address</label>
                <input type="email" placeholder="Enter Email Address Here.." class="form-control" name="email" required="">
              </div>
              <div class="form-group">
                <span id="errorPass" style="color:red;"></span>
                <label>Password</label>
                <input type="password" id="pass1" placeholder="Password Should Be At Least 4 Characters Long.." class="form-control" name="password" required="">
              </div>
              <div class="form-group">
                <label>Password (Confirm)</label>
                <input type="password" id="pass2" placeholder="Confirm Password.." class="form-control" name="password2" required="">
              </div>
              <div class="form-group">
                <label>Would you like Trick Or Eat to be able to send you updates or promotions to your email?</label><br/>
                Subscribe to Trick Or Eat emails:
                <input type="checkbox" name="subscribe" value="1">
              </div>
              <button type="button" class="btn btn-lg btn-info" onclick="checkPassword()">Submit</button>
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
    function checkPassword(){
        if(document.forms['signup-form'].password.value != document.forms['signup-form'].password2.value){
            document.getElementById('errorPass').innerHTML = "Passwords do NOT match!<br/>";
            return false;
        } else if(document.forms['signup-form'].password.value.length < 4) {
            document.getElementById('errorPass').innerHTML = "Your password must be at least 4 characters long!<br/>";
            return false;
        } else {
            document.forms['signup-form'].submit();
            return true;
        }
    }
    </script>

</body></html>
