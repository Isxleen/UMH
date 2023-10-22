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
		
		<div id="cuerpoindex">
			<form id="form" method="post" action="buscarvuelos.asp">
				<select type="text" name="origen" class="inindex">
					<option value="0">Or&iacute;gen</option>
					<%
					Set origen = Conexion.Execute("select IDCIUDAD, CIUDAD from CIUDAD order by CIUDAD")
					do while not origen.EOF
						Response.Write("<option value='" & origen("CIUDAD") & "'>" & origen("CIUDAD") & "</option>")
						origen.MoveNext
					loop
					%>
				</select>
				<select type="text" name="destino" class="inindex">
                    <option value="0">Destino</option>
                    <%
					Set destino = Conexion.Execute("select IDCIUDAD, CIUDAD from CIUDAD order by CIUDAD")
					do while not destino.EOF
						Response.Write("<option value='" & destino("CIUDAD") & "'>" & destino("CIUDAD") & "</option>")
						destino.MoveNext
					loop
					%>
                </select>				
				<input class="post" type="submit" value="Buscar">
			</form>	
		</div>
		<a href="IdConsulta.asp">Consultar Reserva</a>
	</body>
</html>