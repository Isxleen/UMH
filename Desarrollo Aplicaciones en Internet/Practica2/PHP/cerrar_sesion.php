<?php
session_start();
?>
<html><head> <title> Uso de sesiones </title></head>
<body>
<?php
	echo "Ha cerrado la sesion";
	session_destroy();
?>	
<a href="Login.php">Login</a>
</body>
</html>