package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import es.umh.dadm.mispelis54208217T.Objetos.Imagen;
import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.Objetos.UsuarioLogeado;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class AddPeliculaActivity extends AppCompatActivity {

    private static final int CAPTURAR_IMAGEN = 1;
    private static final int SELECCIONAR_IMAGEN_GALERIA = 3;
    MyDatabaseHelper dbHelper = new MyDatabaseHelper(AddPeliculaActivity.this);
    private Bitmap bp;
    ArrayList<String> plataformas;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.peliculas_add);

        UsuarioLogeado usulog = UsuarioLogeado.obtenerInstancia();

        Button btnContinuar = findViewById(R.id.btnContinuarP);
        FloatingActionButton btnCamara = findViewById(R.id.btnCamaraP);
        FloatingActionButton btnGaleria = findViewById(R.id.btnGaleriaP);

        EditText txtTitulo = findViewById(R.id.txtTitulo);
        EditText txtCalif = findViewById(R.id.txtCalificacion);
        EditText txtDuracion = findViewById(R.id.txtDuraicon);

        Spinner spinnerPlataforma = findViewById(R.id.platafroma);
        Spinner spinnerGenero = findViewById(R.id.genero);



        plataformas = dbHelper.listaNombrePLT(usulog.getId(),AddPeliculaActivity.this);
        ArrayAdapter<String> adapterP = new ArrayAdapter<>(this, android.R.layout.simple_spinner_dropdown_item, plataformas);
        adapterP.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerPlataforma.setAdapter(adapterP);
        spinnerPlataforma.setSelection(0, false);

        String[] generos = getResources().getStringArray(R.array.array_generos);
        ArrayAdapter<String> adapterG = new ArrayAdapter<>(this, android.R.layout.simple_spinner_dropdown_item, generos);
        adapterG.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerGenero.setAdapter(adapterG);
        spinnerGenero.setSelection(0, false);

        btnCamara.setOnClickListener(view -> {
            Intent cInt = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            startActivityForResult(cInt,CAPTURAR_IMAGEN);
        });
        btnGaleria.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent cInt = new Intent();
                cInt.setType("image/*");
                cInt.setAction(Intent.ACTION_GET_CONTENT);
                startActivityForResult(Intent.createChooser(cInt, "Seleccionar imagen"), SELECCIONAR_IMAGEN_GALERIA);
            }
        });


        btnContinuar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String titulo = ValorEditText(txtTitulo);
                String duracion = ValorEditText(txtDuracion);
                int calificacion = 0;

                int positionP = spinnerPlataforma.getSelectedItemPosition();
                String plataforma = plataformas.get(positionP);

                int positionG = spinnerGenero.getSelectedItemPosition();
                String genero = generos[positionG];

                if(ValidarCampos(titulo, txtCalif, calificacion, plataforma, genero, bp)){
                    Imagen img = new Imagen();
                    img.setFoto(bp);

                    UsuarioLogeado usuarioLogeado = UsuarioLogeado.obtenerInstancia();
                    int id_usuario = usuarioLogeado.getId();

                    Pelicula pelicula = new Pelicula();
                    pelicula.setId_usuario(id_usuario);
                    pelicula.setTitulo(titulo);
                    pelicula.setNombre_plataforma(plataforma);
                    pelicula.setCalificacion(calificacion);
                    pelicula.setGenero(genero);
                    pelicula.setDuracion(duracion);
                    pelicula.setCaratula(img);

                    if(dbHelper.insertPelicula(pelicula) != -1){
                        Toast.makeText(AddPeliculaActivity.this, R.string.TPL5, Toast.LENGTH_SHORT).show();
                        startActivity(new Intent(AddPeliculaActivity.this, PeliculasActivity.class));
                        finish();

                    }else{
                        Toast.makeText(AddPeliculaActivity.this, R.string.error, Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });
    }

    public boolean ValidarCampos(String nombre, EditText txtcalificacion, int calificacion, String plataforma, String genero, Bitmap bp){
        calificacion = ValorEditNumero(txtcalificacion);

        if(dbHelper.existeValorEnCampo(nombre, "titulo", "Peliculas")){
            Toast.makeText(this, R.string.TPL1, Toast.LENGTH_SHORT).show();
            return false;
        }else if(nombre.equals("")) {
            Toast.makeText(this, R.string.TPL6, Toast.LENGTH_SHORT).show();
            return false;
        }
        else if(calificacion > 10 || calificacion < 1){
            Toast.makeText(this, R.string.TPL2, Toast.LENGTH_SHORT).show();
            return false;
        }else if(genero == null){
            Toast.makeText(this, R.string.TPL3, Toast.LENGTH_SHORT).show();
            return false;
        }else if(plataforma == null){
            Toast.makeText(this, R.string.TPL4, Toast.LENGTH_SHORT).show();
            return false;
        }if(bp == null) {
            Toast.makeText(getApplicationContext(), R.string.TE1, Toast.LENGTH_SHORT).show();
            return false;
        }
        if(plataforma.equals("Selecciona plataforma")) {
            Toast.makeText(getApplicationContext(), R.string.TPL8, Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }

    public String ValorEditText(EditText editText){
        if (editText.getText() != null) {
            return editText.getText().toString().trim();
        } else {
            return "";
        }
    }
    public int ValorEditNumero(EditText txtcalificacion){
        try {
            return Integer.parseInt(txtcalificacion.getText().toString());
        } catch (NumberFormatException e) {
            Toast.makeText(this, R.string.TPLT3, Toast.LENGTH_SHORT).show();
            return 0;
        }
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);
        ImageView foto = findViewById(R.id.fotoPrevPelicula);
        //A continuación hago uso de bp.compress para comprimir imagenes, pues algunas son demasiado grandes
        if (requestCode == CAPTURAR_IMAGEN) {
            if (resultCode == RESULT_OK) {
                bp = (Bitmap) data.getExtras().get("data");
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                bp.compress(Bitmap.CompressFormat.JPEG, 100, stream);
                foto.setImageBitmap(bp);
            } else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(this, R.string.cancelCam, Toast.LENGTH_LONG).show();
            }
        } else if (requestCode == SELECCIONAR_IMAGEN_GALERIA){
            if (resultCode == RESULT_OK) {
                Uri uri = data.getData();
                try {
                    bp = (MediaStore.Images.Media.getBitmap(this.getContentResolver(), uri));
                    ByteArrayOutputStream stream = new ByteArrayOutputStream();
                    bp.compress(Bitmap.CompressFormat.JPEG, 100, stream);
                    foto.setImageBitmap(bp);
                } catch (IOException e) {
                    Toast.makeText(this, R.string.errorCam, Toast.LENGTH_LONG).show();
                }

            } else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(this, R.string.cancelCam, Toast.LENGTH_LONG).show();
            }
        }
    }

}
