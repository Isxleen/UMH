package es.umh.dadm.mispelis54208217T.SQLite;

import java.util.List;

import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.Objetos.Usuario;

public class DatosExportados {
    private List<Usuario> usuarios;
    private List<Pelicula> peliculas;
    private List<Plataforma> plataformas;

    public DatosExportados(List<Usuario> usuarios, List<Pelicula> peliculas, List<Plataforma> plataformas) {
        this.usuarios = usuarios;
        this.peliculas = peliculas;
        this.plataformas = plataformas;
    }

    public List<Usuario> getUsuarios() {
        return usuarios;
    }

    public List<Pelicula> getPeliculas() {
        return peliculas;
    }

    public List<Plataforma> getPlataformas() {
        return plataformas;
    }
}






