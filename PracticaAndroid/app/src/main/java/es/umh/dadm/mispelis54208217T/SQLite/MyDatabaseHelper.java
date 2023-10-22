package es.umh.dadm.mispelis54208217T.SQLite;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import es.umh.dadm.mispelis54208217T.Objetos.Imagen;
import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.Objetos.Usuario;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.R;

import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MyDatabaseHelper extends SQLiteOpenHelper {
    /*
    *
    *
     */

    private static final String NOMBRE_BD = "DBMisPelis.db";
    private static final int VERSION_ACTUAL = 1;
    private final Context contexto;


    private static final String TABLA_USUARIOS = "Usuarios";
    private static final String TABLA_PLATAFORMAS = "Plataformas";
    private static final String TABLA_PELICULAS = "Peliculas";


    /* REGISTROS USUARIO */
    private static final String USU_ID = "_id";
    private static final String USU_EMAIL = "email";
    private static final String USU_NOMBRE = "nombre";
    private static final String USU_APELLIDOS = "apellidos";
    private static final String USU_CONTRASENA = "contraseña";
    private static final String USU_FECHA = "fecha_nacimiento";
    private static final String USU_PREGS = "pregunta_seguridad";
    private static final String USU_RESPS = "respuesta_seguridad";

    /* REGISTROS PLATAFORMA */
    private static final String PLT_ID = "_id";
    private static final String PLT_IDUSUARIO = "id_usuario";
    private static final String PLT_IMG = "imagen";
    private static final String PLT_NOMBRE = "nombre";
    private static final String PLT_URL = "url";
    private static final String PLT_USUARIO = "usuario_acceso";
    private static final String PLT_CONTRASENA = "contraseña_acceso";

    /* REGISTROS PELICULA */
    private static final String PELI_ID = "_id";
    private static final String PELI_IDUSUARIO = "id_usuario";
    private static final String PELI_IDPLATAFORMA = "nombre_plataforma";
    private static final String PELI_CARATULA = "caratula";
    private static final String PELI_TITULO = "titulo";
    private static final String PELI_DURACION = "duracion";
    private static final String PELI_GENERO = "genero";
    private static final String PELI_CALIFICACION = "calificacion";


    private static final String UsuarioTable = "CREATE TABLE " + TABLA_USUARIOS + " (" + USU_ID + " integer primary key autoincrement, "
            + USU_EMAIL + " text not null, " + USU_NOMBRE + " text not null, " + USU_APELLIDOS + " text, " +
            USU_CONTRASENA + " long not null, " + USU_FECHA + " text, " + USU_PREGS + " text, "
            + USU_RESPS + " text);";


    private static final String PlataformaTable = "CREATE TABLE " + TABLA_PLATAFORMAS + " (" + PLT_ID + " integer primary key autoincrement, "
            + PLT_IDUSUARIO + " text not null, " + PLT_IMG + " text not null, " + PLT_NOMBRE + " text, " +
            PLT_URL + " long not null, " + PLT_USUARIO + " text, " + PLT_CONTRASENA + "  text, FOREIGN KEY(id_usuario) REFERENCES Usuarios(id)" +
            ");";

    private static final String PeliculaTable = "CREATE TABLE " + TABLA_PELICULAS + " (" + PELI_ID + " integer primary key autoincrement, "
            + PELI_IDUSUARIO + " text not null, " + PELI_IDPLATAFORMA + " text not null, " + PELI_CARATULA + " text, " +
            PELI_TITULO + " long not null, " + PELI_DURACION + " text, " + PELI_GENERO + "  text, " + PELI_CALIFICACION + " integrer, " +
            "FOREIGN KEY(id_usuario) REFERENCES Usuarios(id), FOREIGN KEY(nombre_plataforma) REFERENCES Plataformas(id));";


    public MyDatabaseHelper(Context contexto) {
        super(contexto, NOMBRE_BD, null, VERSION_ACTUAL);
        this.contexto = contexto;
    }

    @Override
    public void onOpen(SQLiteDatabase db) {
        super.onOpen(db);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(UsuarioTable);
        db.execSQL(PlataformaTable);
        db.execSQL(PeliculaTable);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLA_USUARIOS);
        onCreate(db);
    }

    /*
          ---------      INSERTS        ---------
     */
    public long insertUsuario(Usuario usuario) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();

        cv.put(USU_EMAIL, usuario.getEmail());
        cv.put(USU_NOMBRE, usuario.getNombre());
        cv.put(USU_APELLIDOS, usuario.getApellidos());
        cv.put(USU_CONTRASENA, usuario.getContrasena());
        cv.put(USU_FECHA, usuario.getFecha_nacimiento());
        //cv.put(USU_FECHA, usuario.getIntereses());
        cv.put(USU_PREGS, usuario.getPreg_seguridad());
        cv.put(USU_RESPS, usuario.getRespuesta_seguridad());

        long result = db.insert(TABLA_USUARIOS, null, cv);

        return result;
    }

    public long insertPlataforma(Plataforma plataforma) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();

        cv.put(PLT_IDUSUARIO, plataforma.getId_usuario());
        cv.put(PLT_NOMBRE, plataforma.getNombre());
        cv.put(PLT_IMG, plataforma.getImagen().getArrayFoto());
        cv.put(PLT_URL, plataforma.getUrl());
        cv.put(PLT_USUARIO, plataforma.getUsuario_acceso());
        cv.put(PLT_CONTRASENA, plataforma.getPassword_acceso());

        long result = db.insert(TABLA_PLATAFORMAS, null, cv);

        plataforma.setId(db.rawQuery("SELECT _id FROM " + TABLA_PLATAFORMAS + " WHERE Nombre = '" + plataforma.getNombre() + "'", null).getColumnIndex("_id"));
        db.close();
        return result;
    }

    public long insertPelicula(Pelicula pelicula) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();

        cv.put(PELI_TITULO, pelicula.getTitulo());
        cv.put(PELI_IDUSUARIO, pelicula.getId_usuario());
        cv.put(PELI_IDPLATAFORMA, pelicula.getNombre_plataforma());
        cv.put(PELI_DURACION, pelicula.getDuracion());
        cv.put(PELI_GENERO, pelicula.getGenero());
        cv.put(PELI_CALIFICACION, pelicula.getCalificacion());
        cv.put(PELI_CARATULA, pelicula.getCaratula().getArrayFoto());

        long result = db.insert(TABLA_PELICULAS, null, cv);
        if (result == -1) {
            Toast.makeText(contexto, "Algo salió mal", Toast.LENGTH_SHORT).show();

        }
        return result;
    }

    public boolean validarUsuario(String username, String password) {
        SQLiteDatabase db = this.getReadableDatabase();
        String[] columns = {USU_ID};
        String selection = USU_EMAIL + " = ?" + " AND " + USU_CONTRASENA + " = ?";
        String[] selectionArgs = {username, password};
        Cursor cursor = db.query(TABLA_USUARIOS, columns, selection, selectionArgs, null, null, null);
        int count = cursor.getCount();
        cursor.close();
        return count > 0;
    }

    @SuppressLint("Range")
    public int idUsuario(String username, String password) {
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery("SELECT _id FROM Usuarios WHERE email=? AND contraseña=?", new String[]{username, password});
        int userId = -1;
        if (cursor.moveToFirst()) {
            userId = cursor.getInt(cursor.getColumnIndex("_id"));
        }
        cursor.close();
        db.close();
        return userId;
    }

    public boolean existeValorEnCampo(String valor, String nombreCampo, String nombreTabla) {
        SQLiteDatabase db = this.getWritableDatabase();

        String query = "SELECT COUNT(*) FROM " + nombreTabla + " WHERE " + nombreCampo + " = ?";
        String[] selectionArgs = {valor};

        Cursor cursor = db.rawQuery(query, selectionArgs);
        cursor.moveToFirst();
        int count = cursor.getInt(0);
        cursor.close();

        return count > 0;
    }

    public Plataforma idPlataforma(int idPlataforma, Context context) {
        SQLiteDatabase db = this.getReadableDatabase();

        String selectQuery = "SELECT * FROM Plataformas WHERE _id = ?";
        String[] args = {String.valueOf(idPlataforma)};

        Plataforma plataforma = null;

        Cursor cursor = db.rawQuery(selectQuery, args);
        if (cursor.moveToFirst()) {
            do {
                plataforma = asignarValoresPlt(cursor);

            } while (cursor.moveToNext());
        }

        cursor.close();
        db.close();

        return plataforma;
    }

    public Pelicula idPelicula(int idPelicula, Context context) {
        SQLiteDatabase db = this.getReadableDatabase();

        String selectQuery = "SELECT * FROM Peliculas WHERE _id = ?";
        String[] args = {String.valueOf(idPelicula)};

        Pelicula pelicula = null;

        Cursor cursor = db.rawQuery(selectQuery, args);
        if (cursor.moveToFirst()) {
            do {
                pelicula = asignatValorPeli(cursor);

            } while (cursor.moveToNext());
        }

        cursor.close();
        db.close();

        return pelicula;
    }

    @SuppressLint("Range")
    public List<Plataforma> listaPlataformas(int idUsuario) {
        List<Plataforma> plataformas = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();

        String selectQuery = "SELECT * FROM Plataformas WHERE id_usuario = ?";
        String[] args = {String.valueOf(idUsuario)};

        Plataforma plataforma;

        Cursor cursor = db.rawQuery(selectQuery, args);

        if (cursor.moveToFirst()) {
            do {
                plataforma = asignarValoresPlt(cursor);
                plataformas.add(plataforma);

            } while (cursor.moveToNext());
        }

        cursor.close();
        db.close();

        return plataformas;
    }

    private Plataforma asignarValoresPlt(Cursor cursor) {

        Plataforma plataforma = new Plataforma();
        plataforma.setId(cursor.getInt(0));
        plataforma.setId_usuario(cursor.getInt(1));

        Imagen img = new Imagen();
        img.setArrayFoto(cursor.getBlob(2));
        plataforma.setImagen(img);

        plataforma.setNombre(cursor.getString(3));
        plataforma.setUrl(cursor.getString(4));
        plataforma.setUsuario_acceso(cursor.getString(5));
        plataforma.setPassword_acceso(cursor.getString(6));

        return plataforma;
    }

    @SuppressLint("Range")
    public List<Pelicula> listaPeliculas(int idUsuario) {
        List<Pelicula> peliculas = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();

        String selectQuery = "SELECT * FROM Peliculas WHERE id_usuario = ?";
        String[] args = {String.valueOf(idUsuario)};

        Pelicula pelicula;

        Cursor cursor = db.rawQuery(selectQuery, args);

        if (cursor.moveToFirst()) {
            do {
                pelicula = asignatValorPeli(cursor);
                peliculas.add(pelicula);

            } while (cursor.moveToNext());
        }

        cursor.close();
        db.close();

        return peliculas;
    }

    private Pelicula asignatValorPeli(Cursor cursor) {

        Pelicula pelicula = new Pelicula();
        pelicula.setId(cursor.getInt(0));
        pelicula.setId_usuario(cursor.getInt(1));
        pelicula.setNombre_plataforma(cursor.getString(2));

        Imagen img = new Imagen();
        img.setArrayFoto(cursor.getBlob(3));
        pelicula.setCaratula(img);

        pelicula.setTitulo(cursor.getString(4));
        pelicula.setDuracion(cursor.getString(5));
        pelicula.setGenero(cursor.getString(6));
        pelicula.setCalificacion(cursor.getInt(7));

        return pelicula;
    }

    public ArrayList<String> listaNombrePLT(int id_usuario, Context context) {
        ArrayList<String> nombresPlataformas = new ArrayList<>();
        SQLiteDatabase db = this.getWritableDatabase();

        nombresPlataformas.add("Selecciona plataforma");

        String selectQuery = "SELECT * FROM Plataformas WHERE _id = ?";
        String[] args = {String.valueOf(id_usuario)};

        Cursor cursor = db.rawQuery(selectQuery, args);
        if (cursor.moveToFirst()) {
            do {
                @SuppressLint("Range") String nombre = cursor.getString(cursor.getColumnIndex("nombre"));
                nombresPlataformas.add(nombre);
            } while (cursor.moveToNext());
        }
        return nombresPlataformas;
    }

    public boolean borrarPlataforma(Plataforma plataforma, Context context) {
        SQLiteDatabase db = this.getWritableDatabase();
        int rowsAffected = db.delete("Plataformas", "_id = " + plataforma.getId(), null);

        if (rowsAffected > 0) {
            // Borrado exitoso
            return true;
        } else {
            return false;
        }
    }

    public boolean borrarPelicula(Pelicula pelicula, Context context) {
        SQLiteDatabase db = this.getWritableDatabase();
        int rowsAffected = db.delete("Peliculas", "_id = " + pelicula.getId(), null);

        if (rowsAffected > 0) {
            // Borrado exitoso
            return true;
        } else {
            return false;
        }
    }

    public void actualizarPlataforma(Plataforma plataforma) {
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues valores = new ContentValues();
        valores.put("nombre", plataforma.getNombre());
        valores.put("url", plataforma.getUrl());
        valores.put("usuario_acceso", plataforma.getUsuario_acceso());
        valores.put("contraseña_acceso", plataforma.getPassword_acceso());
        valores.put("imagen", plataforma.getImagen().getArrayFoto());


        String whereClause = "_id = ?";
        String[] whereArgs = {String.valueOf(plataforma.getId())};

        db.update("Plataformas", valores, whereClause, whereArgs);
        db.close();
    }

    public void actualizarPelicula(Pelicula pelicula) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues valores = new ContentValues();

        valores.put("titulo", pelicula.getTitulo());
        valores.put("nombre_plataforma", pelicula.getNombre_plataforma());
        valores.put("caratula", pelicula.getCaratula().getArrayFoto());
        valores.put("duracion", pelicula.getDuracion());
        valores.put("genero", pelicula.getGenero());
        valores.put("calificacion", pelicula.getCalificacion());

        String whereClause = "_id = ?";
        String[] whereArgs = {String.valueOf(pelicula.getId())};

        db.update("Plataformas", valores, whereClause, whereArgs);
        db.close();
    }

    public void exportData(Context context) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor usuariosCursor = db.rawQuery("SELECT * FROM Usuarios", null);
        Cursor cursorPlataformas = db.rawQuery("SELECT * FROM Plataformas", null);
        Cursor cursorPeliculas = db.rawQuery("SELECT * FROM Peliculas", null);

        List<Usuario> usuarios = new ArrayList<>();
        if (usuariosCursor.moveToFirst()) {
            do {
                @SuppressLint("Range")
                int id = usuariosCursor.getInt(usuariosCursor.getColumnIndex(USU_ID));
                @SuppressLint("Range")
                String email = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_EMAIL));
                @SuppressLint("Range")
                String nombre = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_NOMBRE));
                @SuppressLint("Range")
                String apellidos = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_APELLIDOS));
                @SuppressLint("Range")
                String contrasena = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_CONTRASENA));
                @SuppressLint("Range")
                String fechaNacimiento = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_FECHA));
                @SuppressLint("Range")
                String preguntaSeguridad = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_PREGS));
                @SuppressLint("Range")
                String respuestaSeguridad = usuariosCursor.getString(usuariosCursor.getColumnIndex(USU_RESPS));


                Usuario usuario = new Usuario();
                usuario.setId(id);
                usuario.setEmail(email);
                usuario.setNombre(nombre);
                usuario.setApellidos(apellidos);
                usuario.setContrasena(contrasena);
                usuario.setFecha_nacimiento(fechaNacimiento);
                usuario.setPreg_seguridad(preguntaSeguridad);
                usuario.setResp_seguridad(respuestaSeguridad);


            } while (usuariosCursor.moveToNext());
            Toast.makeText(context, usuarios.size() + R.string.usu_exportados, Toast.LENGTH_SHORT).show();
        }

        List<Plataforma> plataformas = new ArrayList<>();
        if (cursorPlataformas.moveToFirst()) {
            do {
                @SuppressLint("Range")
                int id = cursorPlataformas.getInt(cursorPlataformas.getColumnIndex(PLT_ID));
                @SuppressLint("Range")
                int idUsuario = cursorPlataformas.getInt(cursorPlataformas.getColumnIndex(PLT_IDUSUARIO));
                @SuppressLint("Range")
                String nombre = cursorPlataformas.getString(cursorPlataformas.getColumnIndex(PLT_NOMBRE));
                @SuppressLint("Range")
                String url = cursorPlataformas.getString(cursorPlataformas.getColumnIndex(PLT_URL));
                @SuppressLint("Range")
                String usuario = cursorPlataformas.getString(cursorPlataformas.getColumnIndex(PLT_USUARIO));
                @SuppressLint("Range")
                String contrasena = cursorPlataformas.getString(cursorPlataformas.getColumnIndex(PLT_CONTRASENA));

                Plataforma plataforma = new Plataforma();
                plataforma.setId(id);
                plataforma.setId_usuario(idUsuario);
                plataforma.setNombre(nombre);
                plataforma.setUrl(url);
                plataforma.setUsuario_acceso(usuario);
                plataforma.setPassword_acceso(contrasena);


                plataformas.add(plataforma);

            } while (cursorPlataformas.moveToNext());
            Toast.makeText(context, plataformas.size() + R.string.plc_exprtadas, Toast.LENGTH_SHORT).show();

        }

        List<Pelicula> peliculas = new ArrayList<>();
        if (cursorPeliculas.moveToFirst()) {
            do {
                @SuppressLint("Range")
                int id = cursorPeliculas.getInt(cursorPeliculas.getColumnIndex(PELI_ID));
                @SuppressLint("Range")
                int idUsuario = cursorPeliculas.getInt(cursorPeliculas.getColumnIndex(PELI_IDUSUARIO));
                @SuppressLint("Range")
                String nombrePlatafroma = cursorPeliculas.getString(cursorPeliculas.getColumnIndex(PELI_IDPLATAFORMA));
                @SuppressLint("Range")
                byte[] fotoArray = cursorPeliculas.getBlob(cursorPeliculas.getColumnIndex(PELI_CARATULA));
                @SuppressLint("Range")
                String titulo = cursorPeliculas.getString(cursorPeliculas.getColumnIndex(PELI_TITULO));
                @SuppressLint("Range")
                String duracion = cursorPeliculas.getString(cursorPeliculas.getColumnIndex(PELI_DURACION));
                @SuppressLint("Range")
                String genero = cursorPeliculas.getString(cursorPeliculas.getColumnIndex(PELI_GENERO));
                @SuppressLint("Range")
                int calificacion = cursorPeliculas.getInt(cursorPeliculas.getColumnIndex(PELI_CALIFICACION));

                Pelicula pelicula = new Pelicula();
                Imagen img = new Imagen();
                img.setArrayFoto(fotoArray);

                pelicula.setId(id);
                pelicula.setId_usuario(idUsuario);
                pelicula.setNombre_plataforma(nombrePlatafroma);
                pelicula.setCaratula(img);
                pelicula.setTitulo(titulo);
                pelicula.setDuracion(duracion);
                pelicula.setGenero(genero);
                pelicula.setCalificacion(calificacion);

                peliculas.add(pelicula);

            } while (cursorPeliculas.moveToNext());
            Toast.makeText(context, peliculas.size() + R.string.plc_exprtadas, Toast.LENGTH_SHORT).show();

        }

        DatosExportados db2 = new DatosExportados(usuarios, peliculas, plataformas);
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        String json = gson.toJson(db2);

        File file = new File("/data/data/es.umh.dadm.mispelis54208217T/files/datos.json");
        try {
            FileWriter writer = new FileWriter(file);
            writer.write(json);
            writer.close();
            Toast.makeText(context, R.string.arch_export, Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
