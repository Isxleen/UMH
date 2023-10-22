package es.umh.dadm.mispelis54208217T.Adaptadores;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

import es.umh.dadm.mispelis54208217T.DetallesPeliculaActivity;
import es.umh.dadm.mispelis54208217T.DetallesPlatafromaActivity;
import es.umh.dadm.mispelis54208217T.Objetos.Pelicula;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.R;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class PeliculaAdaptador extends RecyclerView.Adapter<PeliculaViewHolder> {

    Context context;
    List<Pelicula> peliculas;

    public PeliculaAdaptador(Context context, List<Pelicula> peliculas) {
        this.context = context;
        this.peliculas = peliculas;
    }


    @NonNull
    @Override
    public PeliculaViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new PeliculaViewHolder(LayoutInflater.from(context).inflate(R.layout.pelicula_view,parent, false));
    }

    @Override
    public void onBindViewHolder(@NonNull PeliculaViewHolder holder, int position) {
        holder.nombre.setText(peliculas.get(position).getTitulo());
        holder.imageView.setImageBitmap(peliculas.get(position).getCaratula().getFoto());
        Pelicula pelicula = peliculas.get(position);
        MyDatabaseHelper db = new MyDatabaseHelper(context);

        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                AlertDialog.Builder builder = new AlertDialog.Builder(context);
                builder.setMessage(R.string.borrar);
                builder.setCancelable(true);

                builder.setPositiveButton(
                        R.string.si,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                if(db.borrarPelicula(pelicula, context)){
                                    Toast.makeText(context, R.string.TPT6, Toast.LENGTH_SHORT).show();
                                }else{
                                    Toast.makeText(context, R.string.error, Toast.LENGTH_SHORT).show();
                                }
                            }
                        });

                builder.setNegativeButton(
                        R.string.cancelar,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

                AlertDialog alert11 = builder.create();
                alert11.show();
                return false;
            }
        });

        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int idPelicula = pelicula.getId();
                Intent intent = new Intent(context, DetallesPeliculaActivity.class);
                intent.putExtra("idPelicula", idPelicula);
                context.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        return peliculas.size();
    }
}
