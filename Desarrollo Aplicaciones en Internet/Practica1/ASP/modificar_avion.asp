<!-- #include file=conexion.asp -->
<html>
<table>
<%	idavion=request.querystring("idavion")
	avion=request.querystring("avion")
	nplazas=request.querystring("plazas")
	precio=request.querystring("precio")
	
	SentenciaSQL= "Update AVION set AVION='" & avion & "', N_PLAZAS=" & nplazas & " where IDAVION=" & idavion
	
	Set rs = Conexion.Execute(SentenciaSQL)
	
	response.write("El avi&oacute;on se ha modificado con &eacute;xito.")
	
	Conexion.close
	set conexion = nothing
%>
</table>
</html>