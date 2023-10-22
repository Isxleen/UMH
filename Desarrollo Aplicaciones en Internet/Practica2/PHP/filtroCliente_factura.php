<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";
?>
<html>
<html>
<body>
	<table border=1>
	<tr><td>Numero Factura</td><td>Matricula</td><td>Mano Obra</td><td>Precio hora</td><td>Fecha emision</td><td>Fecha pago</td><td>Base imponible</td><td>IVA</td><td>Total</td><td>Borrar</td></tr>
	
	<?php
		$cliente = $_REQUEST['cliente'];
		
		
		$sentencia = $conexion->query("SELECT * FROM facturas AS F,motocicletas AS M WHERE M.Matricula = F.Matricula AND M.Id_Cliente =$cliente");
		$sentencia->execute();
		$rows = $sentencia->fetchAll();
		
		foreach($rows as $row){
		$nfact =$row['Numero_Factura'];
		$matricula = $row['Matricula'];
		$mobra = $row['Mano_Obra'];
		$phora = $row['Precio_Hora'];
		$femision =$row['Fecha_Emision'];
		$fpago = $row['Fecha_Pago'];
		$bimponible = $row['Base_Imponible'];
		$IVA = $row['IVA'];
		$total = $row['Total'];

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
	</table>
</body>
</html>