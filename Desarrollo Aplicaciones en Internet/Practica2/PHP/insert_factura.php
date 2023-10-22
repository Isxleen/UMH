<html>
<body>
	<form method=post action="insert_factura2.php" enctype="multipart/form-data">
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT Matricula from motocicletas";
	$consulta = $conexion->prepare($sql);
	$consulta->execute();
	$result = $consulta->fetchAll();
	
	echo "<br>Matricula:";
	echo "<select name=matricula>";
	
	foreach($result as $fila){
		$matricula =$fila['Matricula'];

		echo "<option value=$matricula>$matricula</option>";
	}
	echo "</select>";
	$sql = "SELECT * FROM repuestos ORDER BY Referencia";
	$resultado = $conexion->query($sql);
	$rows = $resultado->fetchAll();
	
	echo "<br>Numero Factura:
		<input type=text name=nfact>
		<br>Mano Obra:
		<input type=text name=mobra>
		<br>Precio hora:
		<input type=text name=phora>
		<br>Fecha emision:
		<input type=date name=femision>
		<br>Fecha pago:
		<input type=date name=fpago>	

		<br><br><br><b>Detalle factura:</b>
		<br>Referencia:
		<select name='referencia[]' required>";
		
		foreach($rows as $row)
		{
			$referencia = $row['Referencia'];
			echo"<option value=$referencia>$referencia</option>";
		}
		
		
	echo"</select>
		<br>Unidades:
		<input type=number min='1' name='unidades[]'>
		<br><input type=submit value='Introducir Factura'>
		<br><input type=reset value='Borrar'>
	</form>
</body>
</html>";
?>
