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

    <title>Participant Waiver</title>

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
      <h1 class="well">Participant Waiver</h1>
      <div class="col-lg-12 well">
        <div class="row">
          <form name="waiver-form">
            <div class="col-sm-12">
              <div class="row">
                <div class="col-sm-6 form-group">
                  <h4 style = "text-align:left">Terms and conditions</h4>
                  <div style="height:300px;width:500px;border:1px solid #ccc;font:16px/26px Georgia, Garamond, Serif;overflow:auto;">
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer cursus at turpis vitae ornare. In rutrum augue eu tortor gravida facilisis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean dictum purus nunc, eu vehicula sem condimentum at. Pellentesque viverra, ex ac dapibus gravida, metus metus aliquet libero, ut semper neque metus ut lacus. Curabitur enim erat, iaculis id ipsum non, tempor tempor velit. Mauris molestie, arcu a luctus pharetra, orci erat pulvinar tortor, non pharetra ipsum metus vitae neque. Duis eu porttitor augue. Quisque egestas suscipit tortor sed commodo.

                    Morbi mollis nisl sed lectus iaculis volutpat. Pellentesque elementum tellus id laoreet mattis. Fusce volutpat varius lacus, eu vehicula eros lobortis in. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Maecenas feugiat vulputate urna at faucibus. Sed gravida vestibulum tristique. Fusce in justo sagittis, laoreet leo eu, porttitor turpis. Aliquam convallis eu ipsum sit amet rhoncus. Suspendisse et tellus lorem. Donec egestas est quam, at molestie lacus sagittis eget. Nulla sit amet tortor in lorem fermentum venenatis commodo in tortor. Mauris sit amet vehicula purus. Nullam ullamcorper, metus vitae egestas imperdiet, enim purus eleifend sem, quis viverra leo velit vitae mauris. Cras a lorem non lectus rutrum sodales.

                    Nulla ac consequat risus. Maecenas vitae pretium neque. Sed vitae auctor tortor, nec auctor massa. Donec semper, turpis vel dictum facilisis, velit mi dapibus ante, eu venenatis tellus turpis ac metus. Etiam iaculis vestibulum tellus, porttitor tristique augue mattis id. Donec maximus aliquam sem, id egestas magna consequat ac. Curabitur mattis iaculis sem, a volutpat ante blandit vel. Sed aliquam elit ac felis congue, ac imperdiet massa pellentesque. Quisque mattis non quam a tempus. Integer quis ornare neque, at rutrum diam. Pellentesque fringilla turpis sit amet nisi semper malesuada in at justo. Ut sed elementum felis. Nam nec elementum nibh, at hendrerit nisl. Nulla iaculis placerat dolor. Donec libero dolor, interdum vel placerat ut, rhoncus at metus. Maecenas vestibulum orci eu orci imperdiet aliquam.

                    Aenean varius nisi at orci viverra venenatis. Mauris quam sapien, egestas ut luctus eget, eleifend ut arcu. Sed finibus magna sit amet tempor eleifend. Curabitur faucibus enim a orci fermentum, in dictum orci ullamcorper. Sed eros nunc, tristique ut ligula ultrices, fringilla imperdiet mauris. Phasellus a luctus augue. Sed at ornare enim.
                  </div>
                  <br/>
                  <input type="checkbox" name="DisabilityCheck">Do you have accessibility needs? 
                  <br/>
                  <input type="checkbox" name="StudentCheck">Are you a University of Guelph student?
                  <br/>
                </div>
                <img src="http://avssc.ca/wp/wp-content/uploads/2015/09/phead.png" alt="testPic" height = "350" width = "400" style="padding-left:50px;">               						
              </div>
              <button type="button" class="btn btn-lg btn-info" onclick="declinePage()">Decline</button>
              <button type="button" class="btn btn-lg btn-info" data-toggle="modal" onclick="pageDirection()">Accept</button>
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
    function pageDirection(){
      if(document.forms['waiver-form']['DisabilityCheck'].checked == true){
        document.cookie="tempAccessibility=1; expires=Thu, 01 Oct 2020 12:00:00 UTC; path=/";
      } else {
        document.cookie="tempAccessibility=0; expires=Thu, 01 Oct 2020 12:00:00 UTC; path=/";
      }

      if(document.forms['waiver-form']['StudentCheck'].checked == true){
        window.location = '/cfc/busWaiver.php';
      } else {
        window.location = '/cfc/Includes/php/eventRegister-request.php';
      }
    }

    function declinePage(){
      if(confirm('Declining now you will lose all progress in the application process. Is this okay?')){
        window.location = '/cfc/events.php';
      }else {
        return false;
      }
    }
    </script>
  

</body></html>
