<html>
<body>

<form method=post action=eliminar_facturas.php>
	<table border=1>
	<tr><td>Numero Factura</td><td>Matricula</td><td>Mano Obra</td><td>Precio hora</td><td>Fecha emision</td><td>Fecha pago</td><td>Base imponible</td><td>IVA</td><td>Total</td><td>Borrar</td></tr>
		
<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$sql = "SELECT * from facturas order by Numero_Factura";
	$consulta = $conexion->prepare($sql);
	$consulta->execute();
	$result = $consulta->fetchAll();
	

	foreach($result as $fila){
		$nfact =$fila['Numero_Factura'];
		$matricula = $fila['Matricula'];
		$mobra = $fila['Mano_Obra'];
		$phora = $fila['Precio_Hora'];
		$femision =$fila['Fecha_Emision'];
		$fpago = $fila['Fecha_Pago'];
		$bimponible = $fila['Base_Imponible'];
		$IVA = $fila['IVA'];
		$total = $fila['Total'];

		echo "<tr>
			<td><a href=detalles_facturas.php?num_fact=$nfact>$nfact</b></a></td>
			<td>$matricula</td>
			<td>$mobra</td>
			<td>$phora</td>
			<td>$femision</td>
			<td>$fpago</td>
			<td>$bimponible</td>
			<td>$IVA</td>
			<td>$total</td>
	
			<td><center><input type=checkbox name=borrar[] value=$nfact</center></td></tr>";
	}
?>

</tr></table>
	<input type=submit value="Eliminar facturas seleccionadas">
	<input type=reset value="Deseleccionar todos">
	<a href="insert_factura.php"><input type=button value="Añadir nueva factura"></a>
</form>
</body>