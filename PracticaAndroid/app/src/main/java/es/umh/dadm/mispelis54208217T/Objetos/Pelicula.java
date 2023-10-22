package es.umh.dadm.mispelis54208217T.Objetos;

public class Pelicula {
    private String[] camposPeli = new String[] {"id", "id_usuario", "id_plataforma", "caratula", "titulo",
            "duracion", "genero", "calificacion"};

    int id;
    int id_usuario;
    String nombre_plataforma;
    String titulo;
    String duracion;
    String genero;
    int calificacion;
    Imagen caratula;

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

    public String getNombre_plataforma() {
        return nombre_plataforma;
    }

    public void setNombre_plataforma(String nombre_plataforma) {
        this.nombre_plataforma = nombre_plataforma;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getDuracion() {
        return duracion;
    }

    public void setDuracion(String duracion) {
        this.duracion = duracion;
    }

    public String getGenero() {
        return genero;
    }

    public void setGenero(String genero) {
        this.genero = genero;
    }

    public int getCalificacion() {
        return calificacion;
    }

    public void setCalificacion(int calificacion) {
        this.calificacion = calificacion;
    }

    public Imagen getCaratula() {
        return caratula;
    }

    public void setCaratula(Imagen caratula) {
        this.caratula = caratula;
    }
}
