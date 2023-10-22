<!-- #include file = conexion.asp-->

<html>
<body>
<%
    Set maxid = Conexion.Execute("select max(IDRESERVA) as ultimo_id from RESERVA")
    idreserva = maxid("ultimo_id") + 1

	idvuelo=request.form("idvuelo")
	nombre = request.form("nombre")
	apellidos= request.form("apellidos")
	n_asientos= request.form("asientos")
    plazas_disp= request.form("plazas_disp")
    nif= request.form("nif")
    cancelado=0

   
    SentenciaSQL = "insert into RESERVA values ("&idreserva & ",'" & apellidos & "','" & nombre & "'," & nif & "," & idvuelo & "," & n_asientos & "," & cancelado & ")"
    Set rs = Conexion.Execute(SentenciaSQL)
    response.redirect("reservar.asp?idvuelo=" & idvuelo & "&idreserva=" &idreserva)


     
        %>  
</body>
</html>