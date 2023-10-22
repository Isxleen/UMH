package es.umh.dadm.mispelis54208217T;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

import es.umh.dadm.mispelis54208217T.Objetos.Imagen;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.Objetos.UsuarioLogeado;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class AddPlataformaActivity extends AppCompatActivity {

    private static final int CAPTURAR_IMAGEN = 1;
    private static final int SELECCIONAR_IMAGEN_GALERIA = 3;

    private Bitmap bp;

    MyDatabaseHelper dbHelper = new MyDatabaseHelper(AddPlataformaActivity.this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.plataforma_add);

        EditText txtnombre = findViewById(R.id.txtNombre);
        EditText txturl = findViewById(R.id.txtURL);
        EditText txtUsuario = findViewById(R.id.txtUsuacceso);
        EditText txtContra = findViewById(R.id.txtPaswAcceso);
        ImageView foto = findViewById(R.id.fotoPrevPlataforma);

        Button btnContinuar = findViewById(R.id.btnContinuar);
        FloatingActionButton btnCamara = findViewById(R.id.btnCamara);
        FloatingActionButton btnGaleria = findViewById(R.id.floatingActionButton2);


        btnContinuar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                UsuarioLogeado usuarioLogeado = UsuarioLogeado.obtenerInstancia();
                int id_usuario = usuarioLogeado.getId();

                String nombre = ValorEditText(txtnombre);
                String url = ValorEditText(txturl);
                String usuario = ValorEditText(txtUsuario);
                String contra = ValorEditText(txtContra);


                if(ValidarcamposPlataforma(nombre, bp)){
                    Imagen img = new Imagen();
                    img.setFoto(bp);

                    Plataforma plataforma = new Plataforma();
                    plataforma.setNombre(nombre);
                    plataforma.setId_usuario(id_usuario);
                    plataforma.setUrl(url);
                    plataforma.setUsuario_acceso(usuario);
                    plataforma.setPassword_acceso(contra);
                    plataforma.setImagen(img);

                    if(dbHelper.insertPlataforma(plataforma) != -1){
                        Toast.makeText(AddPlataformaActivity.this, R.string.TPT5, Toast.LENGTH_SHORT).show();
                        startActivity(new Intent(AddPlataformaActivity.this, PlataformasActivity.class));
                        finish();
                    }
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

    @Override
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


