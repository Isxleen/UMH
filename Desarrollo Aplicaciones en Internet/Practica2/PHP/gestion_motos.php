<html>
<body>

<form method=post action=eliminar_motocicletas.php>
	<table border=1>
	<tr><td>Matricula</td><td>Id_cliente</td><td>Marca</td><td>Modelo</td><td>Anyo</td><td>Color</td><td>Borrar</td></tr>
		
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT * from motocicletas order by Matricula";
	$consulta = $conexion->prepare($sql);
	$consulta->execute();
	$result = $consulta->fetchAll();
	

	foreach($result as $fila){
		$matricula =$fila['Matricula'];
		$marca = $fila['Marca'];
		$modelo = $fila['Modelo'];
		$anyo = $fila['Anyo'];
		$color = $fila['Color'];
		$id_cliente = $fila['Id_Cliente'];


		echo "<tr>
			<td><a href=detalles_motos.php?matricula=$matricula>$matricula</b></a></td>
			<td>$id_cliente</td>
			<td>$marca</td>
			<td>$modelo</td>
			<td>$anyo</td>
			<td>$color</td>
			<td><center><input type=checkbox name=borrar[] value=$matricula</center></td></tr>";
	}
?>

</tr></table>
	<input type=submit value="Eliminar motociclietas seleccionadas">
	<input type=reset value="Deseleccionar todos">
	<a href="insert_moto.php"><input type=button value="Añadir nueva motociclieta"></a>
</form>
</body>