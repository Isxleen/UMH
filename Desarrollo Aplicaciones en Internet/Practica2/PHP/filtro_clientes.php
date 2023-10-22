<?php
include "conexionPDO.php";
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";
?>
<html>
<html>
<body>
	<form action="filtro_clientes2.php" method="POST">
		Nombre:<input type="text" name="nombre">
		<br>Apellido 1:<input type="text" name="apellido1">
		<br>Apellido 2::<input type="text" name="apellido2">
		<br>Poblacion:<input type="text" name="poblacion">
		<br>Provincia:<input type="text" name="provincia">
		<br>Telefono:<input type="text" name="telefono">
		<br><input type="submit" value="Buscar">
	</form>
</body>
</html>