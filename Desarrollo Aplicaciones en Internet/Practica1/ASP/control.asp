<!DOCTYPE html>
<html>
<body>
	
	<%
	session("Autentificado")=0
	if request.form("nombre") = "admin" AND request.form("password") = "1234" then
		session("Autentificado")=1
		response.redirect("menuadmin.asp")
	
	else 
		response.redirect("menucliente.asp")
	end if%>
</body>
</html>