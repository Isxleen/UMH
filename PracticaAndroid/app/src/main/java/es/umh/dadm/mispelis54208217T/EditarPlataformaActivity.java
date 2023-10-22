package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

import es.umh.dadm.mispelis54208217T.Objetos.Imagen;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class EditarPlataformaActivity extends AppCompatActivity {

    private static final int CAPTURAR_IMAGEN = 1;
    private static final int SELECCIONAR_IMAGEN_GALERIA = 3;
    MyDatabaseHelper dbHelper = new MyDatabaseHelper(EditarPlataformaActivity.this);
    private Bitmap bp;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.plataforma_add);

        Intent intent = getIntent();
        int idPlataforma = intent.getIntExtra("idPlataforma", -1); // Obtener el ID de la plataforma

        EditText txtNombre = findViewById(R.id.txtNombre);
        EditText txtUrl = findViewById(R.id.txtURL);
        EditText txtUsuarioA = findViewById(R.id.txtUsuacceso);
        EditText txtPaswAcceso = findViewById(R.id.txtPaswAcceso);

        Button btnContinuar = findViewById(R.id.btnContinuar);
        FloatingActionButton btnCamara = findViewById(R.id.btnCamara);
        FloatingActionButton btnGaleria = findViewById(R.id.floatingActionButton2);

        Plataforma plataforma = dbHelper.idPlataforma(idPlataforma, EditarPlataformaActivity.this);

        txtNombre.setHint(plataforma.getNombre());
        txtUrl.setHint(plataforma.getUrl());
        txtUsuarioA.setHint(plataforma.getUsuario_acceso());
        txtPaswAcceso.setHint(plataforma.getPassword_acceso());

        ImageView foto = findViewById(R.id.fotoPrevPlataforma);
        foto.setImageBitmap(plataforma.getImagen().getFoto());

        btnContinuar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String nombre = txtNombre.getText().toString();
                String url = txtUrl.getText().toString();
                String usuario = txtUsuarioA.getText().toString();
                String passw = txtPaswAcceso.getText().toString();

                if(ValidarcamposPlataforma(nombre, bp)){
                    Plataforma plataforma1 = new Plataforma();
                    plataforma1.setNombre(ValorEditText(txtNombre));
                    plataforma1.setUrl(ValorEditText(txtUrl));
                    plataforma1.setUsuario_acceso(ValorEditText(txtUsuarioA));
                    plataforma1.setPassword_acceso(ValorEditText(txtPaswAcceso));

                    Imagen img = new Imagen();
                    img.setFoto(bp);
                    plataforma1.setImagen(img);

                    dbHelper.actualizarPlataforma(plataforma1);
                    startActivity(new Intent(EditarPlataformaActivity.this, PlataformasActivity.class));
                }
            }
        });

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

    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);
        ImageView foto = findViewById(R.id.fotoPrevPlataforma);
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
    public boolean ValidarcamposPlataforma(String nombre, Bitmap bp){
        if(dbHelper.existeValorEnCampo(nombre, "nombre", "Plataformas")){
            Toast.makeText(this, R.string.TPLT1, Toast.LENGTH_SHORT).show();
            return false;
        }else if(nombre.equals("")){
            Toast.makeText(this, R.string.TPLT2, Toast.LENGTH_SHORT).show();
            return false;
        }
        if(bp == null) {
            Toast.makeText(getApplicationContext(), R.string.TE1, Toast.LENGTH_SHORT).show();
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
}
