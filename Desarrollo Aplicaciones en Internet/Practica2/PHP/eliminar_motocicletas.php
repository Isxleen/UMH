<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

$array_borrados=$_POST["borrar"];

$error=0;


for($i=0;$i<count($array_borrados);$i++){
	$SentenciaSQL = "Delete from motocicletas where Matricula='".$array_borrados[$i]."'";
	echo $SentenciaSQL;
	
	$result = $conexion->query($SentenciaSQL);
	
	if(!$result){
		$error=1;
	}
}

if($error==0){
	echo "<br><br>La/Las Motocicleta(s) se ha(n) eliminado correctamente.";
}

?>

<html>
<body>
	<a href=index.php>Gestion Motos</a>
</body>
</html>