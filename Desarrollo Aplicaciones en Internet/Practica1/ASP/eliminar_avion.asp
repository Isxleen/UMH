<!--- #include file=conexion.asp --->

<html>
    <body>
        <%
            id_recibido=request.querystring("id")

            Set consulta = conexion.Execute("delete from AVION where IDAVION=" & id_recibido)

            if Conexion.Errors.Count>0 then
                for each error in Conexion.Errors
                    response.write(Error.Number & " = " & Error.Description)
                next
            else
                response.write("El avion se ha eliminado con &eacute;xito")
            end if
            
            Conexion.Close
            Set Conexion = nothing
        %>
    </body>
</html>