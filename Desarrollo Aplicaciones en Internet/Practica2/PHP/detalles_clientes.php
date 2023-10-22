<?php
include "conexionPDO.php";	
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";

	$id_cliente=$_GET["id_cliente"];
	
	$sql = "SELECT * FROM clientes where Id_Cliente='$id_cliente'";
	$result = $conexion->query($sql);
	$rows = $result->fetchALL();
	
	foreach($rows as $row){
		$id=$row['Id_Cliente'];
		$dni = $row['DNI'];
		$nombre = $row['Nombre'];
		$apellido1 = $row['Apellido1'];
		$apellido2 = $row['Apellido2'];
		$direccion = $row['Direccion'];
		$cp = $row['CP'];
		$poblacion = $row['Poblacion'];
		$provincia = $row['Provincia'];
		$telf = $row['Telefono'];
		$email = $row['Email'];
	}

		echo " <form method=post action=modificar_clientes.php> 
		Id Cliente:
		<input type=text name=id  readonly value='$id'>
		DNI:
		<input type=text name=dni value=$dni>
		<br>Nombre:
		<input type=text name=nombre value=$nombre>
		<br>Apellido1:
		<input type=text name=apellido1 value=$apellido1>
		<br>Apellido2:
		<input type=text name=apellido2 value=$apellido2>
		<br>Direccion:
		<input type=text name=direccion value=$direccion>
		<br>CP:
		<input type=text name=cp value=$cp>
		<br>Poblacion:
		<input type=text name=poblacion value=$poblacion>
		<br>Provinica:
		<input type=text name=provincia value=$provincia>
		<br>Telefono:
		<input type=text name=telf value=$telf>
		<br>Email:
		<input type=text name=email value=$email><br>";


?>
<input type=submit value=Modificar>
</form>