<!-- #include file = conexion.asp-->
<!DOCTYPE html
<html>
<body>
<%
	idvuelo=request.QueryString("idvuelo")
    set consulta = Conexion.Execute("select * from VUELO where IDVUELO=" &idvuelo)
    plazas_disp = consulta("N_PLAZAS_DISPONIBLES")
%>

    <form name="formAnadir" action="insert_reserva.asp" method="post">
        <table>
            <tr><td>ID Vuelo</td><td><input type=text name="idvuelo" readonly value=<%response.write(idvuelo)%>></td></tr>
            <tr><td>Nombre</td><td><input type=text name="nombre"></td></tr>	
            <tr><td>Apellidos</td><td><input type=text name="apellidos"></td></tr>	
            <tr><td>N Asientos</td><td><input type=text name="asientos"></td></tr>
            <tr><td>NIF</td><td><input type=text name="nif"></td></tr>	
           <input type=hidden name="plazas_disp" readonly value=<%response.write(plazas_disp)%>>	
        </table>
        <input type="submit" id="insert_reserva" value="Reservar"/>

    </form>
    
</body>
</html>