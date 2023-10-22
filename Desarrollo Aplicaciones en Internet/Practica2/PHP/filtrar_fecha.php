<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";
?>
<html>
<html>
<body>	<table border=1>
	<tr><td>Numero Factura</td><td>Matricula</td><td>Mano Obra</td><td>Precio hora</td><td>Fecha emision</td><td>Fecha pago</td><td>Base imponible</td><td>IVA</td><td>Total</td></tr>
	
	<?php
		$fecha1 = $_POST['fecha1'];
		$fecha2 = $_POST['fecha2'];
		
		$sentencia = $conexion->query("SELECT * FROM facturas where Fecha_pago BETWEEN '$fecha1' AND '$fecha2'");
		$sentencia->execute();
		$rows = $sentencia->fetchAll();
		
		foreach($rows as $fila){
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
			<td>$total</td>";
	}
	?>
	</table>
</body>
</html>