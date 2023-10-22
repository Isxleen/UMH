<!--- #include file=conexion.asp -->
<!DOCTYPE html>
<html>
<style>
	table{
		border:solid black;
		width: 100%;
	}
</style>
	<body>
		<%
            idvuelo = request.QueryString("idvuelo")
            idreserva = request.QueryString("idreserva")
 
            response.write("La reserva se ha realizado con exito <br><br> Datos reserva:")


            set datosreserva = Conexion.Execute("select * from RESERVA where IDRESERVA=" & idreserva)
			
			nombre = datosreserva("NOMBRE")
			apellidos = datosreserva("APELLIDOS")
			n_asientos = datosreserva("N_ASIENTOS")
			nif = datosreserva("NIF")
       
        %>
		<br>

		<table>
			<tr><td>Id Reserva:</td><td><% response.write(idreserva) %></td></tr> 
            <tr><td>Nombre:</td><td> <% response.write(nombre)%> </td></tr>     
            <tr><td>Apellidos:</td><td><% response.write(apellidos) %>
            <tr><td>NIF:</td><td><% response.write(nif) %> </td></tr> 
			<tr><td>N Asientos:</td><td><% response.write(n_asientos) %></td></tr>			
		</table>

	</body>
</html>