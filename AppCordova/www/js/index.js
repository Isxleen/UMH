
document.addEventListener('deviceready', onDeviceReady, false);
document.getElementById("acceptTerms").addEventListener("change", activarBoton);


function onDeviceReady() {
    // Cordova is now initialized. Have fun!

    console.log('Running cordova-' + cordova.platformId + '@' + cordova.version);
    document.getElementById('deviceready').classList.add('ready');
}

function activarBoton() {
  var acceptCheckbox = document.getElementById("acceptTerms");
  var createAccountButton = document.getElementById("createButton");

  if (acceptCheckbox.checked) {
      createAccountButton.disabled = false;
  } else {
      createAccountButton.disabled = true;
  }
}

function mostrarMensaje() {
  var email = document.getElementById("email").value;
  var password = document.getElementById("password").value;
  var acceptCheckbox = document.getElementById("acceptTerms");

  if (email === "" || password === "") {
      alert("Rellena todos los campos");
  } else {
      alert("Bienvenido " + email);
  }
    
}
