<html>
<body>

<form method=post action=filtroCliente_factura.php>
	<table border=1>
	<tr><td>ID</td><td>DNI</td><td>Nombre</td><td>Apellido 1</td><td>Apellido 2</td><td>Direccion</td><td>CP</td>
			<td>Poblacion</td><td>Provincia</td><td>Telefono</td><td>Email</td><td>Seleccionar</td></tr>
		
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT * from clientes order by id_cliente";
	$result = $conexion->query($sql);
	
	$rows = $result->fetchALL();

	foreach($rows as $row){
		$id_cliente =$row['Id_Cliente'];
		$dni = $row['DNI'];
		$nombre = $row['Nombre'];
		$apellido1 = $row['Apellido1'];
		$apellido2 = $row['Apellido2'];
		$direccion = $row['Direccion'];
		$cp = $row['CP'];
		$poblacion = $row['Poblacion'];
		$provincia = $row['Provincia'];
		$telefono = $row['Telefono'];
		$email = $row['Email'];
		$foto = $row['Fotografia'];

		echo "
			<tr><td><a href=detalles_clientes.php?id_cliente=$id_cliente>$id_cliente</b></a></td>
			<td>$dni</td>
			<td>$nombre</td>
			<td>$apellido1</td>
			<td>$apellido2</td>
			<td>$direccion</td>
			<td>$cp</td>
			<td>$poblacion</td>
			<td>$provincia</td>
			<td>$telefono</td>
			<td>$email</td>
			<td><center><input type=radio name=cliente value=$id_cliente</center></td></tr>";
	}
?>

</tr></table>
	<input type=submit value="Buscar facturas">
</form>


<h3>Buscar factura entre las fechas:</h3>
<form method=post action=filtrar_fecha.php>
	<input type=date name=fecha1></input>
	<input type=date name=fecha2></input>
	<input type=submit value="Buscar facturas">
</form>


</body>