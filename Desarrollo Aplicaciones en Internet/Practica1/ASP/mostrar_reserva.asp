<!DOCTYPE html>
<!-- #include file=conexion.asp-->
<html>

<body>
	<p> Reseva:</p>

		<%
		dni = request.querystring("dni")
        nreserva = request.querystring("nreserva")

		Set reserva = Conexion.Execute("select * from  RESERVA where NIF = " & dni & " AND IDRESERVA = " & nreserva  &"")

		id=reserva("IDRESERVA")
		apellidos=reserva("APELLIDOS")
		nombre=reserva("NOMBRE")
		idvuelo=reserva("IDVUELO")
		cancelado=reserva("CANCELADO")

		if cancelado = 1 then
			reserva_cancelada = "Cancelada"
		end if

		 if cancelado = 0 then
			reserva_cancelada ="No cancelada"
		end if


		%>	
	
    <form id="form" method="get" action="cancelar_reserva.asp">
		<table>
			<tr><td>C&oacute;digo reserva: <td><input type=text name=idreserva readonly value="<% response.write(id)%>"</td></tr>
			<tr><td>Apellidos:</td><td><input type=text name=apellidos readonly value="<% response.write(apellidos)%>"</td></tr>
			<tr><td>Nombre:</td><td><input type=text name=apellidos readonly value="<% response.write(nombre)%>" </td></tr>
			<tr><td>ID vuelo:</td><td><input type=text name=apellidos readonly value="<% response.write(idvuelo)%>" </td></tr>
			<tr><td>Vuelo:</td><td><input type=text name=vuelo_cancelado readonly value="<% response.write(reserva_cancelada)%>" </td></tr>
			</tr>
		</table>
		<input class="cancelar" type="submit" value="Cancelar">
    </form>
	<br/><br/>