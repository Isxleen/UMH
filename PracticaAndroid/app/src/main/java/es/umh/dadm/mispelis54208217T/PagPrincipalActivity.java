package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class PagPrincipalActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.pagina_principal);

        MyDatabaseHelper dbHelper = new MyDatabaseHelper(PagPrincipalActivity.this);

        Button btnPlataformas = findViewById(R.id.btnPlatafomas);
        Button btnPeliculas = findViewById(R.id.btnPeliculas);

        Button btnExportar = findViewById(R.id.btnExportar);

        btnPlataformas.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View view) {
                startActivity(new Intent(PagPrincipalActivity.this, PlataformasActivity.class));
            }
        });

        btnPeliculas.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(PagPrincipalActivity.this, PeliculasActivity.class));
            }
        });

        btnExportar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                dbHelper.exportData(PagPrincipalActivity.this);
            }
        });
    }
}
