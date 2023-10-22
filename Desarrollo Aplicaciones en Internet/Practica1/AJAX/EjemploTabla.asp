<!-- #include file=conexion.asp -->
<html>
<head>
	<title>Ejemplo Listado Vuelos por Compa&ntilde;&iacute;a</title>
	<meta charset = "UTF-8"/>
  <script type="text/javascript">

	// FUNCIONES JAVASCRIPT
	
	// Creamos el objeto AJAX httprequest

    function AJAXCrearObjeto(){
    
       var obj;
     
       if (window.XMLHttpRequest) { // no es IE
      
          obj = new XMLHttpRequest();
	//alert('El navegador no es IE');
      } 
      
      else { // Es IE o no tiene el objeto
      
         try {
         
           obj = new ActiveXObject("Microsoft.XMLHTTP");
	   // alert('El navegador utilizado es IE');
         }
         catch (e) {
           
           // alert('El navegador utilizado no está soportado');
          }
      }

      //alert('realizado');
      return obj;
   }
	
	
	
	
	// Recibe y muestra los vuelos que pertenecen a la compania seleccionada

   function leerDatosTabla(){
		
	
	     
     // Comprobamos que se han recibido los datos
     
     if (oXML.readyState == 4) {
		

        // Accedemos al XML recibido

        var xml = oXML.responseXML.documentElement;
		
		

        // Accedemos al componente html correspondiente a la tabla

        var tabla = document.getElementById('tabla_vuelos');
        
        // Vaciamos el DIV
	  var definicion_tabla = new String("");

        // cadena con los datos para crear la tabla

          definicion_tabla ='<th>Id Vuelo</th><th>ID Ciudad Origen</th><th>ID Ciudad Destino</th><th>Fecha</th><th>Compa&ntilde;&iacute;a</th><th>Plazas Disponibles</th><th>Duraci&oacute;n</th><th>ID Avi&oacute;n</th><tr>';
          


         // Iteramos cada vuelo

          var v;
	      var item;

          
		  
		  for (i = 0; i < xml.getElementsByTagName('vuelo').length; i++){
	    
             // Accedemos al objeto XML 

             item = xml.getElementsByTagName('vuelo')[i];


           

 	        // Recuperamos el identificador de vuelo

                 v = item.getElementsByTagName('idvuelo')[0].firstChild.data;
 	             
				 
				 // Añadimos el campo a la tabla
				 
				 definicion_tabla =definicion_tabla+'<td>'+ v +'</td>';
            
             
          


           // Recuperamos el id de la ciudad de origen

            v = item.getElementsByTagName('ciudad_origen')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla =definicion_tabla+'<td>'+ v +'</td>';


           // Recuperamos el id de la ciudad destino

            v = item.getElementsByTagName('ciudad_destino')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v +'</td>';

	    // Recuperamos la fecha

            v = item.getElementsByTagName('fecha')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v + '</td>';


           // Recuperamos la compania

            v = item.getElementsByTagName('compania')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v + '</td>';

           // Recuperamos el numero de planzas disponibles

            v = item.getElementsByTagName('n_plazas_disponibles')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v + '</td>';

            // Recuperamos la duracion del vuelo

            v = item.getElementsByTagName('duracion')[0].firstChild.data;

           // Añadimos el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v + '</td>';


            // Recuperamos el id de avion

            v = item.getElementsByTagName('avion')[0].firstChild.data;

           // añadimo el campo a la tabla

            definicion_tabla= definicion_tabla+'<td>' + v + '</td></tr>';
		
	
        }
        // rellenamos el objeto html tabla con la definicion construida

        tabla.innerHTML = definicion_tabla;
         
      }
       

  }
  
    function leerdatos(){
      if(objetoAjax.readyState==4){
        var div = document.getElementById('destino');
        div.innerHTML = objetoAjax.responseText;
      }
  }
  

  function mostrar_destino(){
    selectOrigen = document.forms.origen.ciudad_origen;
    seleccionado = selectOrigen.value;

    objetoAjax = AJAXCrearObjeto();
    objetoAjax.open('get','cargar_vuelos.asp?ciudad_origen='+seleccionado, true);
    objetoAjax.onreadystatechange = leerdatos;

    objetoAjax.send('');

  }

	
	
	function mostrar_vuelos(){

		var valorx = document.getElementById("ciudad_origen").value;
		var valory = document.getElementById("ciudad_destino").value;
		

		oXML = AJAXCrearObjeto();
		oXML.open('POST', 'consulta.asp');
		
		oXML.onreadystatechange = leerDatosTabla;
		
		oXML.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		oXML.send('ciudad_origen='+valorx+'&ciudad_destino='+valory);
	
	}

  
    
   </script>	
	
</head>

<body>
<h2>EJEMPLO LISTAR VUELOS POR COMPA&Ntilde;&Iacute;A</h2>



Seleccione una Ciudad de origen del Vuelo: 

<form method="POST" name="origen" id="origen">
    <select name="ciudad_origen" id="ciudad_origen" onChange="return mostrar_destino();">
		<option>Ciudad Origen</option>
    <%
        Set origen = Conexion.Execute("select IDCIUDAD, CIUDAD from CIUDAD order by IDCIUDAD")
        do while not origen.EOF
            Response.Write("<option value='" & origen("IDCIUDAD") & "'>" & origen("CIUDAD") & "</option>")
          origen.MoveNext
        loop
    %>
    </select>

	<br>
	<div id="destino">
		<select id="ciudad_destino" name="ciudad_destino"> 
			<option>Ciudad Destino</option>
		
		</select>
	</div>
	<input type="button" onClick= "return mostrar_vuelos();" value="Buscar vuelos"></input>
</form>
	
	<table id="tabla_vuelos" name="tabla_vuelos" border='1'>
	</table>



</body>
</html>