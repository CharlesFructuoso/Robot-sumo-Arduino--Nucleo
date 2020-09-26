<!-------------- Traitement du formulaire de contact     -------------->
<?php

    $name = $_POST['name'];
    $mail = $_POST['mail'];
    $texte = $_POST['message'];
    $date = date("d-m-Y");
    $heure = date("H:i");

    $sendhome = false;
    $sendclient = false;

    /******************** ENVOI MAIL CHEZ NOUS ******************/
    $destinataire = 'contact@zow-e.ovh';       
    $expediteur   = 'contact@zow-e.ovh'; 
    $reponse      = $expediteur;
    $subject      = 'Formulaire de contact';

    $message = "Name : ".$name."\r\n"."<br><br>";
    $message .= "Text : ".$texte."\r\n"."<br><br>";
    $message .= "Mail : ".$mail."\r\n<br><br>";
    $message .= "Sending : ".$date." at : ".$heure."\r\n"."<br><br>";
    
    if(mail('contact@zow-e.ovh',$subject,$message,"From: $expediteur\r\n"."Reply-To: $reponse\r\n"."Content-Type: text/html; charset=\"UTF-8\"\r\n"))
    {
        $sendhome = true;
    }else{
        $sendhome = false;
    }

    /******************** ENVOI MAIL CHEZ CLIENT ******************/
    $destinataire = $mail;       
    $expediteur   = 'contact@zow-e.ovh'; 
    $reponse      = $expediteur;
    $subject      = 'Sent form confirmation';

    $message = "Your message was succesfully sent."."\r\n"."<br><br>";

    if(mail($destinataire,$subject,$message,"From: $expediteur\r\n"."Reply-To: $reponse\r\n"."Content-Type: text/html; charset=\"UTF-8\"\r\n"))
    {
        $sendclient = true;
    }else{
        $sendclient = false;
    }

    /**************************************************************/

?>

<!doctype html>
<html lang="en">
<head>
	<meta charset="utf-8" />
    <link rel="icon" type="image/png" href="../assets/img/favicon.ico">
    <link rel="apple-touch-icon" sizes="76x76" href="../assets/img/apple-icon.png">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />

    <title>ZOW-E</title>

    <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
    <meta name="viewport" content="width=device-width" />

	<!-- Bootstrap core CSS     -->
	<link href="../assets/css/bootstrap.min.css" rel="stylesheet" />
	<link href="../assets/css/paper-kit.css?v=2.1.0" rel="stylesheet"/>

    <!--     Fonts and icons     -->
    <link href='http://fonts.googleapis.com/css?family=Montserrat:400,300,700' rel='stylesheet' type='text/css'>
    <link href="http://maxcdn.bootstrapcdn.com/font-awesome/latest/css/font-awesome.min.css" rel="stylesheet">
    <link href="../assets/css/nucleo-icons.css" rel="stylesheet">  	

</head>
<body>
    
    <!--     Navbar    -->
    <nav class="navbar navbar-expand-lg fixed-top navbar-transparent" color-on-scroll="300">
        <div class="container">
			<div class="navbar-translate">
				<a class="navbar-brand" href="https://www.zow-e.ovh">ZOW-E</a>
	            <button class="navbar-toggler navbar-toggler-right navbar-burger" type="button" data-toggle="collapse" data-target="#navbarToggler" aria-controls="navbarTogglerDemo02" aria-expanded="false" aria-label="Toggle navigation">
					<span class="navbar-toggler-bar"></span>
					<span class="navbar-toggler-bar"></span>
					<span class="navbar-toggler-bar"></span>
	            </button>
			</div>
	        <div class="collapse navbar-collapse" id="navbarToggler">
	            <ul class="navbar-nav ml-auto">
                    <li class="nav-item">
                        <a class="nav-link" rel="tooltip" title="Follow us on Youtube" data-placement="bottom" href="#" target="_blank">
                            <i class="fa fa-youtube"></i>
                            <p class="d-lg-none">Youtube</p>
                        </a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" rel="tooltip" title="Follow us on Facebook" data-placement="bottom" href="https://www.facebook.com/ZOW.E.OFF/" target="_blank">
                            <i class="fa fa-facebook"></i>
                            <p class="d-lg-none">Facebook</p>
                        </a>
                    </li>
                    <li class="nav-item">
                        <a href="index.html" class="nav-link"><i class=""></i>EN</a>
                    </li>
                    <li class="nav-item">
                        <a href="fr.html" class="nav-link"><i class=""></i>FR</a>
                    </li>
                    <li class="nav-item">
                        <a href="br.html" class="nav-link"><i class=""></i>BR</a>
                    </li>
	            </ul>
	        </div>
		</div>
    </nav>

    <!--     Main    -->
    <div class="wrapper">
        <div class="page-header page-header-xs" data-parallax="true" style="background-image: url('../assets/img/sao.jpg');">
			<div class="filter"></div>
            <!--     Header     -->
    <div class="container">
        <div class="motto text-center">
            <img src="robot.png">
            <h1>ZOW-E</h1>
            <h3>International Sumo Robot Competition</h3>
            <h4>São Paulo - July 2018</h4><br/>
        </div>
	</div>
		</div>
        <div class="section profile-content">
            <div class="container">
                
                <br>
                
                <!--     Notifs    -->
                <?php
                
                if($sendhome == true AND $sendclient == true){ ?>
                    
                    <div class="alert alert-success alert-with-icon" data-notify="container">
                        <div class="container">
                            <div class="alert-wrapper">
                                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                                <i class="nc-icon nc-simple-remove"></i>
                                </button>
                                <div class="message"><i class="nc-icon nc-bell-55"></i>  Your message has been sent.</div>
                            </div>
                        </div>
                    </div> <?php
                    
                }else{ ?>
                    
                    <div class="alert alert-warning alert-with-icon" data-notify="container">
                        <div class="container">
                            <div class="alert-wrapper">
                                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                                <i class="nc-icon nc-simple-remove"></i>
                                </button>
                                <div class="message"><i class="nc-icon nc-bell-55"></i>  Sorry, your message could not be sent. Please retry later. Thank you.</div>
                            </div>
                        </div>
                    </div> <?php
                    
                }
                
                ?>
                
                <!--     Notif    -->
                
                
                <center><h2>Contact</h2></center><br><br>
                
                <center><h5>Due to unexpected volumes, it is taking us a little longer than we would like to respond to emails. Our current email response time is 1-2 business days.</h5></center>
                
            </div>
        </div>
    </div>
    
    <!-- Footer -->
	<footer class="footer section-dark">
		<div class="container">
			<div class="row">
                <!-- Footer Navbar -->
				<nav class="footer-nav">
				</nav>
				<div class="credits ml-auto">
					<span class="copyright">
						© <script>document.write(new Date().getFullYear())</script>, made with <i class="fa fa-heart heart"></i> by ZOW-E Team
					</span>
				</div>
			</div>
		</div>
	</footer>
</body>

<!-- Core JS Files -->
<script src="../assets/js/jquery-3.2.1.js" type="text/javascript"></script>
<script src="../assets/js/jquery-ui-1.12.1.custom.min.js" type="text/javascript"></script>
<script src="../assets/js/popper.js" type="text/javascript"></script>
<script src="../assets/js/bootstrap.min.js" type="text/javascript"></script>

<!--  Paper Kit Initialization snd functons -->
<script src="../assets/js/paper-kit.js?v=2.1.0"></script>

</html>
