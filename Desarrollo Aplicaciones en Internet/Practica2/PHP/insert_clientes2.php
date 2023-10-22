<?php
include "conexionPDO.php";
sinclude "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

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


$SentenciaSQL=("insert into clientes(DNI,Nombre,Apellido1,Apellido2,Direccion,CP,Poblacion,Provincia,Telefono,Email) values ('$dni','$nombre','$apellido1','$apellido2','$direccion','$cp','$poblacion', '$provincia', '$telf', '$email')");

$result = $conexion->query($SentenciaSQL);
if(!$result){
	echo"<br>Error al introducir el Cliente en la Base de Datos";
}else{
	echo"<br>El Cliente se ha introducido con &eacute;xito en la base de datos";
}

?>

<a href=gestion_clientes.php><input type=button value=Gestion></a>
<a href=index.php><input type=button value=Inicio></a>
