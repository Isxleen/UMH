package es.umh.dadm.mispelis54208217T;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.chip.ChipGroup;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import es.umh.dadm.mispelis54208217T.Objetos.Usuario;
import es.umh.dadm.mispelis54208217T.Objetos.UsuarioLogeado;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class AddCuentaActivity extends AppCompatActivity {
/*
*       Esta actividad recoge los datos introducidos por el usuario, los verifica y los añade a la base de datos
*
 */
    Context context;
    boolean setPregunta = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.crear_cuenta);


        Button btnRegistrar = (Button) findViewById(R.id.continuar);
        Button btnCancelar = (Button) findViewById(R.id.cancelar);

        EditText txtnombre = (EditText) findViewById(R.id.txtNombre);
        EditText txtemail = (EditText) findViewById(R.id.txtEmail);
        EditText txtapellidos = (EditText) findViewById(R.id.txtApellidos);
        EditText txtcumple = (EditText) findViewById(R.id.txtCumple);
        EditText txtpassw = (EditText) findViewById(R.id.txtcontraseña);
        EditText txtpasswconfrim = (EditText) findViewById(R.id.txtConfContra);
        EditText txtrespSeg = (EditText) findViewById(R.id.resp_preguntaSeg);

        EditText txtOtrosIntereses = findViewById(R.id.txtOtrosIntereses);

        MyDatabaseHelper dbHelper = new MyDatabaseHelper(AddCuentaActivity.this);

        ChipGroup chipGroup = findViewById(R.id.chip_group);
        //EditText editTextOtro = findViewById(R.id.);

        List<String> interesesSeleccionados = new ArrayList<>();

        List<Integer> listaIntereses = chipGroup.getCheckedChipIds();

        String[] preguntasSeguridad = getResources().getStringArray(R.array.array_preguntas);

        Intent intent = new Intent(AddCuentaActivity.this, MainActivity.class);


        Spinner spinner = findViewById(R.id.preg_seguridad);

        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_dropdown_item, preguntasSeguridad);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setSelection(0, false);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                setPregunta = position != 0;
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                // No se hace nada
            }
        });


        txtcumple.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Calendar c = Calendar.getInstance();
                int anyo = c.get(Calendar.YEAR);
                int mes = c.get(Calendar.MONTH);
                int dia = c.get(Calendar.DAY_OF_MONTH);

                DatePickerDialog datePickerDialog = new DatePickerDialog(AddCuentaActivity.this, new DatePickerDialog.OnDateSetListener() {
                    @SuppressLint("SetTextI18n")
                    @Override
                        public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
                                // on below line we are setting date to our text view.
                            txtcumple.setText(dayOfMonth + "/" + (monthOfYear + 1) + "/" + year);

                            }
                        }, anyo, mes, dia);

                datePickerDialog.show();
            }
        });

        /*
        * METODO PARA DESPLEGAR EL EDITEXT CUANDO EL USUARIO PULSE OTRO EN INTERESES
        */
       /* chipGroup.setOnCheckedChangeListener(new ChipGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(ChipGroup group, int checkedId) {
                // Obtener el chip seleccionado
                Chip selectedChip = findViewById(checkedId);

                // Verificar si el chip seleccionado es Otros
                if (selectedChip != null && selectedChip.getText().toString().equalsIgnoreCase("Otros")) {
                    // Mostrar el EditText para Otros
                    txtOtrosIntereses.setVisibility(View.VISIBLE);
                } else {
                    // Ocultar el EditText para Otros
                    txtOtrosIntereses.setVisibility(View.GONE);
                }

                // Limpiar la lista de intereses seleccionados
                interesesSeleccionados.clear();


            }
        });*/


        btnRegistrar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String nombre = ValorEditText(txtnombre);
                String email =  ValorEditText(txtemail);
                String apellidos =  ValorEditText(txtapellidos);
                String contra =  ValorEditText(txtpassw);
                String confcontra = ValorEditText(txtpasswconfrim);
                String pregSeguridad;

                /* Registro la posicion seleccionada en el spinner y guardo la pregunta del array de preguntas de dicha posicion en
                * la variable  */
                int position = spinner.getSelectedItemPosition();
                if(!setPregunta){
                    pregSeguridad = "";
                }else{
                    pregSeguridad = preguntasSeguridad[position];
                }

                String respSeguridad =  ValorEditText(txtrespSeg);
                String intereses = "";
                String fnacimiento = txtcumple.getText().toString();


                /* *******************    PILLAR INTERESES DEL CHIPGROUP         ************************  */
                // Obtener chips seleccionados
               /* for (int i = 0; i < chipGroup.getChildCount(); i++) {
                    Chip chip = (Chip) chipGroup.getChildAt(i);
                    if (chip.isChecked() && !chip.getText().toString().equalsIgnoreCase("Otros")) {
                        interesesSeleccionados.add(chip.getText().toString());
                    }
                }

                // Agregar el interés escrito en el EditText para Otros, si está visible y tiene texto
                if (txtOtrosIntereses.getVisibility() == View.VISIBLE && !TextUtils.isEmpty(txtOtrosIntereses.getText().toString())) {
                    interesesSeleccionados.add(txtOtrosIntereses.getText().toString());
                }
                // Juntar todos los intereses en un String
                String separador = ",";
                intereses = TextUtils.join(separador, interesesSeleccionados);
                /* ________________________________________________________________________________    */


                if (ValidarCampos(nombre, email, apellidos, contra, confcontra, respSeguridad, fnacimiento, intereses, dbHelper)) {

                        Usuario usuario = new Usuario();
                        usuario.setEmail(email);
                        usuario.setNombre(nombre);
                        usuario.setApellidos(apellidos);
                        usuario.setContrasena(contra);
                        usuario.setFecha_nacimiento(fnacimiento);
                        usuario.setPreg_seguridad(pregSeguridad);
                        usuario.setResp_seguridad(respSeguridad);
                        usuario.setIntereses(intereses);

                    if(dbHelper.insertUsuario(usuario) != -1){
                        int id = dbHelper.idUsuario(email,contra);
                        UsuarioLogeado usu = UsuarioLogeado.obtenerInstancia();
                        usu.setId(id);
                        startActivity(new Intent(AddCuentaActivity.this, PlataformasActivity.class));
                        finish();
                    }
                }
            }
        });

        btnCancelar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder builder1 = new AlertDialog.Builder(AddCuentaActivity.this);
                builder1.setMessage(R.string.pregCancelar);
                builder1.setCancelable(true);

                builder1.setPositiveButton(
                        R.string.si,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                startActivity(intent);
                            }
                        });

                builder1.setNegativeButton(
                        R.string.cancelar,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

                AlertDialog alert11 = builder1.create();
                alert11.show();
            }
        });
    }

    public boolean ValidarCampos(String nom, String mail, String apellidos, String contr, String confcontr, String resp_seguridad,
                                 String fecha, String intereses, MyDatabaseHelper dbHelper){

        if (mail.isEmpty() || mail.equals(" ")) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU1, Toast.LENGTH_SHORT).show();
            return false;
        }else if(!mail.matches("[a-zA-Z0-9._-]+@[a-z]+\\.+[a-z]+")){
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU8, Toast.LENGTH_SHORT).show();
            return false;
        }else if(dbHelper.existeValorEnCampo(mail, "email", "Usuarios")){
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU2, Toast.LENGTH_SHORT).show();
            return false;
        }else if (nom.isEmpty()) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU3, Toast.LENGTH_SHORT).show();
            return false;
        } else if (contr.isEmpty()) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU4, Toast.LENGTH_SHORT).show();
            return false;
        } else if (confcontr.isEmpty()) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU5, Toast.LENGTH_SHORT).show();
            return false;
        } else if (!contr.equals(confcontr)) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU6, Toast.LENGTH_SHORT).show();
            return false;
        } else if (setPregunta && resp_seguridad.equals("")) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU7, Toast.LENGTH_SHORT).show();
            return false;
        } else if (!setPregunta && !resp_seguridad.equals("")) {
            Toast.makeText(AddCuentaActivity.this, R.string.TUSU8, Toast.LENGTH_SHORT).show();
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