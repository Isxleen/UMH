<?php
include("ConexionPDO.php");
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a><br>";
$num_factura=$_POST['numfactura'];
$matricula = $_POST['matricula'];
$mano_obra = $_POST['mano_obra'];
$precio_hora = $_POST['precio_hora'];
$fecha_emision = $_POST['fecha_emision'];
$fecha_pago = $_POST['fecha_pago'];
$base_imponible = $_POST['base_imponible'];
$iva = $_POST['iva'];
$total = $_POST['total'];

echo "Matricula = '$matricula',
			Mano_Obra = '$mano_obra',
			Precio_Hora = '$precio_hora',
			Fecha_Emision = '$fecha_emision',
			Fecha_Pago = '$fecha_pago',
			Base_Imponible = '$base_imponible',
			IVA = '$iva',
			Total = '$total'
		WHERE Numeeo_Factura ='$num_factura'";


$sql = "UPDATE facturas SET
			Matricula = '$matricula',
			Mano_Obra = '$mano_obra',
			Precio_Hora = '$precio_hora',
			Fecha_Emision = '$fecha_emision',
			Fecha_Pago = '$fecha_pago',
			Base_Imponible = '$base_imponible',
			IVA = '$iva',
			Total = '$total'
		WHERE Numero_Factura ='$num_factura'";
		
$update = $conexion->prepare($sql);
$update->execute();

echo"El perfil del cliente se ha modificado con éxito
	<a href=gestion_facturas.php><input type=button value=Volver></a>"
?>

