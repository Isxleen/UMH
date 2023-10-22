<!--#include file="conexion.asp"-->
<!DOCTYPE html>
<html>
	<head>
		<title>SkyTraveler</title>
	</head>
	<body>
		<div id="cabecera">
			<h1>SkyTraveler</h1>
			<a href="identificacion.asp" class ="login">Iniciar sesion</a>
		</div>
		
		<div id="cuerpoIdConsulta">
            <form id="form" method="get" action="mostrar_reserva.asp">
                <label name="dni">DNI: </label>
                <input type="text" name="dni">
                <br>
                <label name="nreserva">N Reserva: </label>
                <input type="text" name="nreserva">
                <input class="post" type="submit" value="Buscar">
            </form>
        </div>

	</body>
</html>