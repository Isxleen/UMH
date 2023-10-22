<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$num_factura=$_GET["num_fact"];
	
	$sql = "SELECT * FROM facturas where Numero_Factura='$num_factura'";
	$result = $conexion->query($sql);
	$rows = $result->fetchALL();
	
	foreach($rows as $row){
		$num_factura=$row['Numero_Factura'];
		$matricula = $row['Matricula'];
		$mano_obra = $row['Mano_Obra'];
		$precio_hora = $row['Precio_Hora'];
		$fecha_emision = $row['Fecha_Emision'];
		$fecha_pago = $row['Fecha_Pago'];
		$base_imponible = $row['Base_Imponible'];
		$iva = $row['IVA'];
		$total = $row['Total'];

	}

		echo " <form method=post action=modificar_facturas.php> 
		Numero_Factura:
		<input type=text name=numfactura  readonly value='$num_factura'>
		Matricula:
		<input type=text name=matricula value=$matricula>
		<br>Mano Obra:
		<input type=text name=mano_obra value=$mano_obra>
		<br>Precio Hora:
		<input type=text name=precio_hora value=$precio_hora>
		<br>Fecha emision:
		<input type=text name=fecha_emision value=$fecha_emision>
		<br>Fecha pago:
		<input type=text name=fecha_pago value=$fecha_pago>
		<br>Base imponible:
		<input type=text name=base_imponible readonly value=$base_imponible>
		<br>IVA:
		<input type=text name=iva readonly value=$iva>
		<br>Total:
		<input type=text name=total readonly value=$total>";


?>
<input type=submit value=Modificar>
</form>