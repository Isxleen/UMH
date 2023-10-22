<!-- #include file=conexion.asp -->
<%
    ciudad_origen = request.querystring("ciudad_origen")
    SentenciaSQL = "select * from LISTA_DESTINOS(" & ciudad_origen&")"
    texto = texto & "<select name='ciudad_destino' id='ciudad_destino'>"
    
    Set rs = Conexion.Execute(SentenciaSQL)

    do while not rs.EOF
        texto = texto & "<option value='" & rs("IDCIUDADDESTINO")&"'>" & rs("CIUDAD_DESTINO") & "</option>"
		rs.MoveNext
	loop
	
	texto = texto & "</select>"
	response.write(texto)
%>