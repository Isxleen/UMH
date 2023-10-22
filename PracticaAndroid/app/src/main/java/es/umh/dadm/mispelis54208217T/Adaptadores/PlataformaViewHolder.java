package es.umh.dadm.mispelis54208217T.Adaptadores;

import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import es.umh.dadm.mispelis54208217T.R;

public class PlataformaViewHolder extends RecyclerView.ViewHolder {

    ImageView imageView;
    TextView nombre;


    public PlataformaViewHolder(@NonNull View itemView) {
        super(itemView);
        imageView = itemView.findViewById(R.id.imageView);
        nombre = itemView.findViewById(R.id.nombrePlataforma);
    }
}
