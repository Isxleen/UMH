
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";

$id = $_POST["id"];
$dni=$_POST["dni"];
$nombre=$_POST["nombre"];
$apellido1=$_POST["apellido1"];
$apellido2=$_POST["apellido2"];
$direccion=$_POST["direccion"];
$cp=$_POST["cp"];
$poblacion=$_POST["poblacion"];
$provincia=$_POST["provincia"];
$telf=$_POST["telf"];
$email=$_POST["email"];

$sql = "UPDATE clientes SET DNI = '$dni',
			Nombre = '$nombre',
			Apellido1 = '$apellido1',
			Apellido2 = '$apellido2',
			Direccion = '$direccion',
			CP = '$cp',
			Poblacion = '$poblacion',
			Provincia = '$provincia',
			Telefono = '$telf',
			Email = '$email'
		WHERE Id_Cliente='$id'";
		
$update = $conexion->prepare($sql);
$update->execute();

echo"El perfil del cliente se ha modificado con éxito
	<a href=gestion_clientes.php><input type=button value=Volver></a>"
?>

