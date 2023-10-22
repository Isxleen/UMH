<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";

$id=$_POST["cliente"];
$matricula=$_POST["matricula"];
$marca=$_POST["marca"];
$modelo=$_POST["modelo"];
$anyo=$_POST["anyo"];
$color=$_POST["color"];

echo"(insert into motocicletas(Matricula,Marca,Modelo,Anyo,Color,Id_Cliente) values ('$matricula','$marca','$modelo','$anyo','$color','$id'";


$SentenciaSQL=("insert into motocicletas(Matricula,Marca,Modelo,Anyo,Color,Id_Cliente) values ('$matricula','$marca','$modelo',$anyo,'$color',$id)");

$result = $conexion->query($SentenciaSQL);
if(!$result){
	echo"<br>Error al introducir la motocicleta en la Base de Datos";
}else{
	echo"<br>La motocicleta se ha introducido con &eacute;xito en la base de datos";
}
