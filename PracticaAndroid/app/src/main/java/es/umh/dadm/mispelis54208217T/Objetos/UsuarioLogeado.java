package es.umh.dadm.mispelis54208217T.Objetos;

public class UsuarioLogeado {
    private static UsuarioLogeado instancia;

    protected int  id;

    public UsuarioLogeado() {

    }

    public static UsuarioLogeado obtenerInstancia() {
        if (instancia == null) {
            instancia = new UsuarioLogeado();
        }
        return instancia;
    }

    public int getId(){
        return id;
    }

    public void setId(int id){
        this.id = id;
    }

    public void cerrarSesion() {
        this.id = 0;
        }
    }

