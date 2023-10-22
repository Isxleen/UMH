package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.Serializable;

import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class DetallesPlatafromaActivity extends AppCompatActivity implements Serializable {
    MyDatabaseHelper dbHelper = new MyDatabaseHelper(DetallesPlatafromaActivity.this);

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.detalles);

        Intent intent = getIntent();
        int idPlataforma = intent.getIntExtra("idPlataforma", -1); // Obtener el ID de la plataforma

        FloatingActionButton btnEditar = findViewById(R.id.floatingActionButton);

        TextView textViewURL = findViewById(R.id.tv1);
        TextView textViewUsuario = findViewById(R.id.tv2);
        TextView textViewContraseña = findViewById(R.id.tv3);


        TextView txtNombre = findViewById(R.id.txt1);
        TextView txtURL = findViewById(R.id.txt2);
        TextView txtUsuario = findViewById(R.id.txt3);
        TextView txtContra = findViewById(R.id.txt4);

        ImageView img = findViewById(R.id.iwfoto);
        Plataforma plataforma = dbHelper.idPlataforma(idPlataforma, DetallesPlatafromaActivity.this);


        txtNombre.setText(plataforma.getNombre());
        txtURL.setText(plataforma.getUrl());
        txtUsuario.setText(plataforma.getUsuario_acceso());
        txtContra.setText(plataforma.getPassword_acceso());
        img.setImageBitmap(plataforma.getImagen().getFoto());

        textViewURL.setText(R.string.urlacceso);
        textViewUsuario.setText(R.string.usuarioacceso);
        textViewContraseña.setText(R.string.contraseña);

        btnEditar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int idPlataforma = plataforma.getId();
                Intent intent = new Intent(DetallesPlatafromaActivity.this, EditarPlataformaActivity.class);
                intent.putExtra("idPlataforma", idPlataforma);
                startActivity(intent);
                finish();

            }
        });

    }
}
