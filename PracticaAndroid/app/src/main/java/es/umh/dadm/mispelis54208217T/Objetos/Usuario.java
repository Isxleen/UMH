package es.umh.dadm.mispelis54208217T.Objetos;

import android.text.TextUtils;

import androidx.annotation.NonNull;

import java.util.ArrayList;

public class Usuario{

    private static final ArrayList <Usuario> listaUsuarios = new ArrayList<>();
    protected int  id;
    protected String email;
    protected String nombre;
    protected String apellidos;
    protected String contrasena;
    protected String  fecha_nacimiento;
    protected String preg_seguridad;
    protected String resp_seguridad;
    protected String intereses;
    protected ArrayList<String> arrayintereses;

    /* GETTERS */
    public static ArrayList<Usuario> getListaUsuarios() {return listaUsuarios;}
    public int getId() {
        return id;
    }
    public String getEmail() {
        return email;
    }
    public String getNombre() {
        return nombre;
    }
    public String getApellidos() {
        return apellidos;
    }
    public String getContrasena() {
        return contrasena;
    }
    public String getFecha_nacimiento() {
        return fecha_nacimiento;
    }
    public String getPreg_seguridad() {
        return preg_seguridad;
    }
    public String getRespuesta_seguridad() {
        return resp_seguridad;
    }
    public ArrayList<String> getArrayIntereses() { return arrayintereses; }



    /* SETTERS */
    public void setId(int id) {
        this.id = id;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public void setContrasena(String contrasena) {
        this.contrasena = contrasena;
    }

    public void setFecha_nacimiento(String fecha_nacimiento) {
        this.fecha_nacimiento = fecha_nacimiento;
    }

    public void setPreg_seguridad(String preg_seguridad) {
        this.preg_seguridad = preg_seguridad;
    }

    public void setResp_seguridad(String resp_seguridad) {
        this.resp_seguridad = resp_seguridad;
    }

    public void setIntereses(String intereses) {
        this.intereses = intereses;
    }

    public void setArrayintereses(ArrayList<String> arrayintereses) {
        this.arrayintereses = arrayintereses;
    }

    public String getIntereses() {
        // Juntar todos los intereses en un String
        String separador = ",";
        this.intereses = TextUtils.join(separador, arrayintereses);
        return intereses;
    }

    @NonNull
    @Override
    public String toString() {
        return "Usuario{" +
                "id =" + id +
                ", nombre='" + nombre + '\'' +
                ", apellidos=" + apellidos +
                ", contrasena=" + contrasena +
                ", fecha_nacimiento='" + fecha_nacimiento + '\'' +
                ", preg_seguridad='" + preg_seguridad + '\'' +
                ", resp_seguridad='" + resp_seguridad + '\'' +
                ", intereses='" + intereses + '\'' +
                '}';
    }

}
