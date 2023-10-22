<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$ref=$_GET["referencia"];
	
	$sql = "SELECT * FROM repuestos where Referencia=$ref";
	$result = $conexion->query($sql);
	$rows = $result->fetchALL();
	
	foreach($rows as $row){
		$descrip = $row['Descripcion'];
		$imp = $row['Importe'];
		$ganancia = $row['Ganancia'];
	}

		echo " <form method=post action=modificar_repuesto.php> 
		Referencia:
		<input type=text name=ref readonly value='$ref'>
		Descripcion:
		<input type=text name=descrip value=$descrip>
		<br>Importe(€):
		<input type=text name=imp value=$imp>
		<br>Ganancia:
		<input type=text name=ganancia value=$ganancia>";
?>
<input type=submit value=Modificar>
</form>