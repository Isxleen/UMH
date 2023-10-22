<?php
include ("conexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";

$id = $_REQUEST["id"];
$matricula=$_REQUEST["matricula"];
$marca=$_REQUEST["marca"];
$modelo=$_REQUEST["modelo"];
$anyo=$_REQUEST["anyo"];
$color=$_REQUEST["color"];


$sql = "UPDATE motocicletas SET 
			Marca = '$marca',
			Modelo = '$modelo',
			Anyo = '$anyo',
			Color = '$color',
			Id_Cliente = '$id'
		WHERE Matricula='$matricula'";
		
$update = $conexion->prepare($sql);
$update->execute();

echo"Los datos de la motocicleta se han modificado con éxito
	<a href=gestion_motos.php><input type=button value=Volver></a>"
?>
