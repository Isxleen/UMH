<!-- #include file = conexion.asp-->

<html>
<body>
<%
	idavion=request.form("idavion")
	avion = request.form("avion")
	plazas= request.form("plazas")
	precio= request.form("precio")

	SentenciaSQL = "insert into AVION values(" & idavion & ",'" & avion & "','" & plazas & "','" & precio & "')'"
	
	Set rs = Conexion.Execute(SentenciaSQL)
	
	response.write("El avion se ha introducitdo con &eacute;xito en la Base de Datos.")
	
	Conexion.Close
	Set Conexion = nothing
%>
</body>
</html>