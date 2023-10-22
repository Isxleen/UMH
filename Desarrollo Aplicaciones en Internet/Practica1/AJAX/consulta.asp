<!-- #include file=conexion.asp -->
<%
      '  Script ASP programado con VBScript
      ' Realiza consulta en la base de datos y genera como resultato
      '  una lista de vuelos en formato XML
 
      'on Error Resume Next

	' Accedemos al compañía enviado desde la pagina principal

	ciudad_origen = request.form("ciudad_origen")
	ciudad_destino = request.form("ciudad_destino")
	 
	 
    ' El contenido a devolver es XML


	 response.ContentType="text/xml"
	 response.CacheControl="no-cache, must-revalidate"


	 	  

      ' Consulta SQL de las ciudades que son origen de algun vuelo

        SentenciaSQL = "Select * from VUELO where IDCIUDADORIGEN=" & ciudad_origen & "AND IDCIUDADDESTINO=" & ciudad_destino

        Set rs = Conexion.Execute(SentenciaSQL)


       ' Se genera una salida XML con la lista de vuelos
	  
        if (not(rs.Eof)) then

		%><?xml version="1.0" encoding="UTF-8"?> <%
		response.write("<XML>")
  	     
           ' Recorremos el Recorset
           do until rs.Eof

	      response.write("<vuelo>")
          response.write("<idvuelo>")
          response.write( rs("IDVUELO") )
          response.write("</idvuelo>")

          response.write("<ciudad_origen>")
          response.write( rs("IDCIUDADORIGEN") )
          response.write("</ciudad_origen>")

          response.write("<ciudad_destino>")
          response.write( rs("IDCIUDADDESTINO") )
          response.write("</ciudad_destino>")

          response.write("<fecha>")
          response.write( rs("FECHA") )
          response.write("</fecha>")

          response.write("<compania>")
          response.write( rs("IDCOMPANIA") )
          response.write("</compania>")

          response.write("<n_plazas_disponibles>")
          response.write( rs("N_PLAZAS_DISPONIBLES") )
          response.write("</n_plazas_disponibles>")

          response.write("<duracion>")
          response.write( rs("DURACION") )
          response.write("</duracion>")

          response.write("<avion>")
          response.write( rs("IDAVION") )
          response.write("</avion>")

          response.write("</vuelo>")
             
			 
		   rs.MoveNext
           loop

           response.write("</XML>")
    
         end if  
%>  