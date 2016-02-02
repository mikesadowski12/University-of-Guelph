<html>
<head>

</head>
<body>
<div style="padding: 0 20px 0 20px;">

  <div align="center">
    <h2>Code For Change Help Page</h2>
  </div>

  <p style="width:800px;">When creating links with "a" use a direct path through the server. If 
     You want to reference another page use "/cfc/(path)" Where path would
     be the absolute path from inside of our directory. Please look at this 
     code and the index.php in test to see what I mean. The link below and in 
     the other page shows how it is used.</p>

  <br/>
  <a href="/cfc/test/main.php">Link to Test index.php Page</a>
  <br/><br/>


  <?php 
    echo("<p>Echoing Some php code</p>"); 
    for($i=1;$i<11;$i++){
      echo('<p style="color:rgb('.($i*60).','.($i*10).','.($i*100).')">Row: '.$i.'</p>');
    }
  ?>

  <div align="center">
    <h3>The End</h3>
  </div>

</div>
</body>
</html>
