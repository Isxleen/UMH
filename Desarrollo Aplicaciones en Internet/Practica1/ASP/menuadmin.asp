<!DOCTYPE html>
<!-- #include file=seguridad.asp-->
<!-- #include file=conexion.asp-->
<html>
	<!-- ID ciudades-->
	<%
	Set consulta = Conexion.Execute("select max(IDAVION) as ultimo_id from AVION")
	sig_id = consulta("ultimo_id") + 1
	%>

<body>
	<p>Listado aviones:</p>
	<table><td><b>ID/Editar</b></td><td><center><b>Avion</b></center></td><td><b>Plazas</b></td><td><b>Precio</b></td><td><b>Eliminar</b></td>
		<%
		Set resultado = Conexion.Execute("select * from AVION") 
		
		do while not resultado.EOF
			Response.Write("<tr><td><a href=detalles.asp?id=" & resultado("IDAVION") & ">" & resultado("IDAVION") & "</a></center></td><td><center>" & resultado("AVION") &"</center><td><center>" & resultado("N_PLAZAS") &"</center></td><td><center>" & resultado("PRECIO_BASE") &"</center></td><td><center><a href=eliminar_avion.asp?id=" & resultado("IDAVION") & "><b>X</b></a></center></td></tr>")
			resultado.MoveNext 
			loop
		%>
	</table>	
	<br/><br/>

	<p>Introducir avion:</p>
	<form name="formAnadir" action="introducir_avion.asp" method="post">
		<table>
			<tr><td>ID Avion</td><td><input type=text name="idavion" readonly value=<%response.write(sig_id)%>></td></tr>
			<tr><td>Avion</td><td><input type=text name="avion"></td></tr>	
			<tr><td>Num plazas</td><td><input type=text name="plazas"></td></tr>	
			<tr><td>Precio base</td><td><input type=text name="precio"></td></tr>		
		</table>
		<input type="submit" id="introducir_avion" value="Introducir avion"/></center></td></tr>
	</form>

	<input type="button" value="Cerrar sesion">
	
	
</body>
</html>