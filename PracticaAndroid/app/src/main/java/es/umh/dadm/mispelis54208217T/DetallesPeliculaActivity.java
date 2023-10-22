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

import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class DetallesPeliculaActivity extends AppCompatActivity implements Serializable {
    MyDatabaseHelper dbHelper = new MyDatabaseHelper(DetallesPeliculaActivity.this);

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.detalles);



        Intent intent = getIntent();
        int idPelicula = intent.getIntExtra("idPelicula", -1); // Obtener el ID de la plataforma

        FloatingActionButton btnEditar = findViewById(R.id.floatingActionButton);

        TextView textViewPlataforma = findViewById(R.id.tv1);
        TextView textViewGenero = findViewById(R.id.tv2);
        TextView textViewDuracion = findViewById(R.id.tv3);
        TextView textViewCalific = findViewById(R.id.tv4);
        textViewCalific.setVisibility(View.VISIBLE);


        TextView txtTitulo = findViewById(R.id.txt1);
        TextView txtPlataforma = findViewById(R.id.txt2);
        TextView txtGenero = findViewById(R.id.txt3);
        TextView txtDuracion = findViewById(R.id.txt4);
        TextView txtCalific = findViewById(R.id.txt5);
        txtCalific.setVisibility(View.VISIBLE);

        ImageView img = findViewById(R.id.iwfoto);
        Pelicula pelicula = dbHelper.idPelicula(idPelicula, DetallesPeliculaActivity.this);


        txtTitulo.setText(pelicula.getTitulo());
        txtPlataforma.setText(pelicula.getNombre_plataforma());
        txtGenero.setText(pelicula.getGenero());
        txtDuracion.setText(pelicula.getDuracion());
        img.setImageBitmap(pelicula.getCaratula().getFoto());

        textViewPlataforma.setText(R.string.plataforma);
        textViewGenero.setText(R.string.genero);
        textViewDuracion.setText(R.string.duracion);
        textViewCalific.setText(R.string.calificacion);


        btnEditar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int idPelicula = pelicula.getId();
                Intent intent = new Intent(DetallesPeliculaActivity.this, EditarPlataformaActivity.class);
                intent.putExtra("idPelicula", idPelicula);
                startActivity(intent);
                finish();

            }
        });

    }
}

