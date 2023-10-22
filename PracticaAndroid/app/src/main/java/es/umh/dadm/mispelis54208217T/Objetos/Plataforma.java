package es.umh.dadm.mispelis54208217T.Objetos
        ;

import android.graphics.Bitmap;

import java.io.Serializable;
import java.util.ArrayList;

public class Plataforma implements Serializable {

    private int id;
    private int id_usuario;
    private String nombre;
    private String url;
    private String usuario_acceso;
    private String password_acceso;
    private Imagen imagen;


    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId_usuario() {
        return id_usuario;
    }

    public void setId_usuario(int id_usuario) {
        this.id_usuario = id_usuario;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUsuario_acceso() {
        return usuario_acceso;
    }

    public void setUsuario_acceso(String usuario_acceso) {
        this.usuario_acceso = usuario_acceso;
    }

    public String getPassword_acceso() {
        return password_acceso;
    }

    public void setPassword_acceso(String password_acceso) {
        this.password_acceso = password_acceso;
    }

    public Imagen getImagen() {
        return imagen;
    }

    public void setImagen(Imagen imagen) {
        this.imagen = imagen;
    }

/*
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
    }*/



}
