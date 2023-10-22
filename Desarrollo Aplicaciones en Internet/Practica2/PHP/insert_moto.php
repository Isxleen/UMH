<html>
<body>
	<form method=post action="insert_moto2.php" enctype="multipart/form-data">
		Propietario:
<?php
	include("ConexionPDO.php");
	include "seguridad.php";
	echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT * from clientes";
	$consulta = $conexion->prepare($sql);
	$consulta->execute();
	$result = $consulta->fetchAll();
	
	echo "<select name=cliente>";
	
	foreach($result as $fila){
		$id =$fila['Id_Cliente'];
		$nombre = $fila['Nombre'];
		$apellido1 = $fila['Apellido1'];
		$apellido2 = $fila['Apellido2'];

		$cliente = $nombre . " " . $apellido1 . " " . $apellido2;
		
		echo "<option value=$id>$cliente</option>";
	}
	echo "</select>"
?>
		<br>Matricula:
		<input type=text name=matricula>
		<br>Marca:
		<input type=text name=marca>
		<br>Modelo:
		<input type=text name=modelo>
		<br>Anyo:
		<input type=text name=anyo>
		<br>Color:
		<input type=text name=color>

		
		<br><input type=submit value="Introducir motocicleta">
		<br><input type=reset value="Borrar">
	</form>
</body>
</html>