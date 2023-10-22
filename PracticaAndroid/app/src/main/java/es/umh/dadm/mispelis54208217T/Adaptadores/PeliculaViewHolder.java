package es.umh.dadm.mispelis54208217T.Adaptadores;

import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import es.umh.dadm.mispelis54208217T.R;

public class PeliculaViewHolder extends RecyclerView.ViewHolder{


    ImageView imageView;
    TextView nombre;


    public PeliculaViewHolder(@NonNull View itemView) {
        super(itemView);
        imageView = itemView.findViewById(R.id.caratula);
        nombre = itemView.findViewById(R.id.nombrePelicula);
    }
}
