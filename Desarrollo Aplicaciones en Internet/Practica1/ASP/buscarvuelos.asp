<!-- #include file=conexion.asp -->
<html>
<style>
	table{
		border:solid black;
		width: 100%;
	}
</style>
<body>

<table>
	<td><center><b>ID VUELO</b></center></td><td><center><b>ORIGEN - DESTINO</b></center></td><td><center><b>PLAZAS</b></center>	</td><td><center><b>FECHA</b></center></td><td><center><b>PRECIO</b></center></td>
<%
 origen = request.form("origen")
 destino = request.form("destino")

 if origen="0" AND destino="0" then
	Set consulta=Conexion.Execute("select * from LISTA_VUELOS_PRECIO")
	do while not consulta.EOF
		Response.Write("<tr><td><center>" & consulta("IDVUELO") & "</center></td><td><center>" & consulta("CIUDAD_ORIGEN") & " - " & consulta("CIUDAD_DESTINO") & "</center></td><td><center>" & consulta("N_PLAZAS_DISPONIBLES") & "</center></td><td><center>"& consulta("FECHA") & "</center></td><td><center>" & round(consulta("PRECIO"),2) &"</center></td><td><a href=menu_reserva.asp?idvuelo=" & consulta("IDVUELO") & "><input type=button value=Reservar></a></tr>")
			consulta.MoveNext
	loop
else
	Set consulta=Conexion.Execute("select * from LISTA_VUELOS_PRECIO  where ciudad_origen='"&origen&"' and ciudad_destino='"&destino&"'")
	do while not consulta.EOF 
	Response.Write("<tr><td><center>" & consulta("IDVUELO") & "</center></td><td><center>" & consulta("CIUDAD_ORIGEN") & " - " & consulta("CIUDAD_DESTINO") & "</center></td><td><center>" & consulta("N_PLAZAS_DISPONIBLES") & "</center></td><td><center>"& consulta("FECHA") & "</center></td><td><center>" & round(consulta("PRECIO"),2) &"</center></td><td><a href=menu_reserva.asp?idvuelo=" & consulta("IDVUELO") & "><input type=button value=Reservar></a></tr>")
		consulta.MoveNext
	loop
end if

%>
</table>
</body>
</html>