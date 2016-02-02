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

    <title>Donate</title>

    <!-- main CSS -->
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

    <style type="text/css">
      .donate label {
        float: left;
        width: 250px;
        text-align: left;
        padding-right: 12px;
        margin-top: 12px;
        clear: left;
        color: #E6E6E6;
      }
      
      .antilabel {
        float: left;
      }

      .donate button {
        float: left;
        width: 200px;
        text-align: left;
        padding-right: 12px;
        margin-top: 12px;
        clear: left;
      }

      input {
        margin-top: 12px;
      }

      select {
        margin-top: 12px;
        height: 35px;
        color: #000;
      }

      select > option {
        margin-top: 12px;
        height: 35px;
        color: #000;
      }

      input[type=radio] {
        margin-top: 22px;
        margin-right: 3px;
        margin-left: 3px;
      }
      input[type=checkbox] {
        margin-top: 22px;
        margin-right: 8px;
      }
    </style>

  </head>

  <body>

  <?php include "./Includes/header.inc"; ?>


    <div class="container donate" style="color:white;">

      <div class="row">
        <div class="col-lg-12" style="padding: 10px;">
          <h1>Donate</h1>
          <hr>
            <p class="cfc-font">A Canada without hunger is possible.  Your generous gift is helping to end hunger and ensure good food for all across the country! </p>
        </div>
      </div>

      <div class="row" style="font-size: 20px; padding-left: 5px">
        <div class="col-lg-6" class="cfc-font">
          <h1>Contact Information</h1>
          <hr>
            <label>First Name:</label>
            <input type="text" style="color:#000;"><br>

            <label>Last Name:</label>
            <input type="text" style="color:#000;"><br>

            <label>Address:</label>
            <input type="text" style="color:#000;"><br>

            <label>City/Town:</label>
            <input type="text" style="color:#000;"><br>

            <label>Country:</label>
            <select style="width: 250px">
              <option></option>
            </select><br>

            <label>Province/State:</label>
            <select style="width: 250px">
              <option></option>
            </select><br>

            <label>Postal/Zip Code:</label>
            <input type="text" style="color:#000;"><br>

            <label>Phone Number:</label>
            (<input type="text" maxlength="3" style="color:#000; width: 75px">)
            <input type="text" style="color:#000; width: 155px"><br><br>

           <div class="antilabel"><input type="checkbox" checked>Allow meal exchange to contact me by e-mail</div><br>

        </div>

        <div class="col-lg-6">
          <h1>Payment Information</h1>
          <hr>
            <label>Donation Amount:</label>
            <form>
                <input type="radio" name="amount">$250
                <input type="radio" name="amount">$100
                <input type="radio" name="amount">$50
                <input type="radio" name="amount">$25<br>
                <input type="text" style="color:#000;"><br>
            </form>


            <label>Pay Using Credit Card:</label>
            <input type="radio" name="payType">Credit<br>

            <label>Pay Using PayPal:</label>
            <input type="radio" name="payType">PayPal<br>

            <label>Credit Card Type:</label>
            <select style="width: 250px; color:black;">
              <option>Mastercard</option>
              <option>VISA</option>
            </select><br>

            <label>Credit Card Number:</label>
            <input type="text" style="color:#000;"><br>

            <label>Card Security Number:</label>
            <input type="text" maxlength="3" style="color:#000; width:75px; margin-right: 8px">
            <a class="cfc-link" href="#">What is this?</a><br>

            <label>Cardholder's Name:</label>
            <input type="text" style="color:#000;"><br>

            <label>Credit Card Expiration Date:</label>
            <select style="width: 75px; margin-right: 6px">
              <option></option>
            </select>
            /
            <select style="width: 75px; margin-left: 6px">
              <option></option>
            </select><br>
            
      <button type="button" class="btn btn-primary btn-lg" style="text-align: center">Donate Now&nbsp</button>
        </div>
      </div><br/>
      
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
