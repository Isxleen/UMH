package es.umh.dadm.mispelis54208217T;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import es.umh.dadm.mispelis54208217T.Objetos.UsuarioLogeado;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MyDatabaseHelper dbHelper = new MyDatabaseHelper(MainActivity.this);


        EditText txtemail = findViewById(R.id.email);
        EditText txtcontra = findViewById(R.id.passtext);

        String email = txtemail.getText().toString();
        String contra = txtcontra.getText().toString();

        Button btnInicio = findViewById(R.id.btnIniciar);
        Button btnCrearCuenta = findViewById(R.id.btnCuentaNueva);


        btnInicio.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                String email = txtemail.getText().toString();
                String contra = txtcontra.getText().toString();
                int num;

                if(email.equals("") && contra.equals("")){
                    Toast.makeText(MainActivity.this, "Los campos están vacíos",Toast.LENGTH_SHORT).show();
                }
                else if(!dbHelper.validarUsuario(email, contra)){
                    Toast.makeText(MainActivity.this, "Los datos introducidos son incorrectos",Toast.LENGTH_SHORT).show();
                }
                else if(dbHelper.validarUsuario(email, contra)){
                    startActivity(new Intent(MainActivity.this, PagPrincipalActivity.class));
                    num = dbHelper.idUsuario(email,contra);
                    UsuarioLogeado usuarioLogeado = UsuarioLogeado.obtenerInstancia();
                    usuarioLogeado.setId(num);
                    finish();

                }

            }
        });

        btnCrearCuenta.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, AddCuentaActivity.class));
                finish();
            }
        });

    }

}
