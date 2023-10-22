<?php
session_start();

$_SESSION['nombre'] = $_GET["nombre"];
$_SESSION['empresa'] = $_GET["pass"];
$_SESSION['autentificado']='SI';
header("Location: index.php");
?>
