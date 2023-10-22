package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.List;

import es.umh.dadm.mispelis54208217T.Adaptadores.PeliculaAdaptador;
import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.Objetos.UsuarioLogeado;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class PeliculasActivity extends AppCompatActivity {
    RecyclerView recyclerView;
    FloatingActionButton add_button;

    MyDatabaseHelper dbHelper;

    UsuarioLogeado usulog = new UsuarioLogeado();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.peliculas_activity);

        RecyclerView recyclerView = findViewById(R.id.recyclerView);
        add_button = findViewById(R.id.add_button);

        dbHelper = new MyDatabaseHelper(PeliculasActivity.this);

        List<Pelicula> peliculas;
        peliculas = dbHelper.listaPeliculas(UsuarioLogeado.obtenerInstancia().getId());

        LinearLayoutManager layoutManager = new LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false);

        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setNestedScrollingEnabled(false);

        recyclerView.setAdapter(new PeliculaAdaptador(PeliculasActivity.this, peliculas));

        add_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(PeliculasActivity.this, AddPeliculaActivity.class));
                finish();
            }
        });


    }
}
