<!DOCTYPE html>
<html>
<body>
	
	<%
	autentificacion = session("Autentificado")
	if autentificacion = 0 then
		response.redirect("identificacion.asp")

	end if%>
</body>
</html>