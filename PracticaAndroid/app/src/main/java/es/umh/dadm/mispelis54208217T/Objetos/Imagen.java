package es.umh.dadm.mispelis54208217T.Objetos;

import android.graphics.Bitmap;

import java.io.Serializable;

import es.umh.dadm.mispelis54208217T.Adaptadores.ConversorBitmap;

public class Imagen implements Serializable {
    private int id;
    private byte[] arrayFoto;
    private Bitmap foto;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Bitmap getFoto() {
        return foto;
    }

    public void setFoto(Bitmap foto) {
        this.foto = foto;

        arrayFoto = ConversorBitmap.bitmapToArray(this.foto);
    }

    public byte[] getArrayFoto() {
        return arrayFoto;
    }

    public void setArrayFoto(byte[] arrayFoto) {
        this.arrayFoto = arrayFoto;
        this.foto = ConversorBitmap.imageFromArray(this.arrayFoto);
    }
}
