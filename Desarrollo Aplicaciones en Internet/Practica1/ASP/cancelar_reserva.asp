<!--- #include file = conexion.asp -->
<html>
<body>
<%
	idreserva=request.querystring("idreserva")
	cancelado=request.querystring("cancelado")

	if cancelado = 0 then

		SentenciaSQL= "Update RESERVA set CANCELADO= 1"  
		
		Set rs = Conexion.Execute(SentenciaSQL)

		if Conexion.Errors.Count>0 then
			for each objErr in Conexion.Errors
				response.write("<p>")
				response.write("Error al cancelar: ")
				response.write(objErr.Decription & "</p>")
			next
		else
					response.write("Cancelacion OK")
		end if
	else
		response.write("La reserva ya estaba cancelada anteriormente")
	end if 

	Conexion.Close
	Set Conexion = nothing
%>
</body>
</html>