
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";

$ref = $_POST["ref"];
$descrip=$_POST["descrip"];
$imp=$_POST["imp"];
$ganancia=$_POST["ganancia"];


$sql = "UPDATE repuestos SET Referencia = '$ref',
			Descripcion = '$descrip',
			Importe = '$imp',
			Ganancia = '$ganancia'
	
		WHERE Referencia='$ref'";
		
$update = $conexion->prepare($sql);
$update->execute();

echo"El repuesto se ha modificado con éxito
	<a href=gestion_repuestos.php><input type=button value=Volver></a>"
?>

