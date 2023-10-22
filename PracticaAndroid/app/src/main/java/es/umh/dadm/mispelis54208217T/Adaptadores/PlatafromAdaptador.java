package es.umh.dadm.mispelis54208217T.Adaptadores;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import com.google.gson.Gson;

import android.content.Context;
import android.view.LayoutInflater;
import android.widget.Toast;

import java.util.List;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import es.umh.dadm.mispelis54208217T.DetallesPlatafromaActivity;
import es.umh.dadm.mispelis54208217T.Objetos.Plataforma;
import es.umh.dadm.mispelis54208217T.R;
import es.umh.dadm.mispelis54208217T.SQLite.MyDatabaseHelper;

public class PlatafromAdaptador extends RecyclerView.Adapter<PlataformaViewHolder> {

    Context context;
    List<Plataforma> plataformas;

    public PlatafromAdaptador(Context context, List<Plataforma> plataformas) {
        this.context = context;
        this.plataformas = plataformas;
    }

    @NonNull
    @Override
    public PlataformaViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new PlataformaViewHolder(LayoutInflater.from(context).inflate(R.layout.plataforma_view,parent, false));
    }

    @Override
    public void onBindViewHolder(PlataformaViewHolder holder, int position) {
        holder.nombre.setText(plataformas.get(position).getNombre());
        holder.imageView.setImageBitmap(plataformas.get(position).getImagen().getFoto());
        Plataforma plataforma = plataformas.get(position);

        MyDatabaseHelper db = new MyDatabaseHelper(context);

        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                AlertDialog.Builder builder1 = new AlertDialog.Builder(context);
                builder1.setMessage(R.string.borrar);
                builder1.setCancelable(true);

                builder1.setPositiveButton(
                        R.string.si,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                if(db.borrarPlataforma(plataforma, context)){
                                    Toast.makeText(context, R.string.TPT6, Toast.LENGTH_SHORT).show();
                                }else{
                                    Toast.makeText(context, R.string.error, Toast.LENGTH_SHORT).show();
                                }
                            }
                        });

                builder1.setNegativeButton(
                        R.string.cancelar,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

                AlertDialog alert11 = builder1.create();
                alert11.show();
                return false;
            }
        });

        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int idPlataforma = plataforma.getId();
                Intent intent = new Intent(context, DetallesPlatafromaActivity.class);
                intent.putExtra("idPlataforma", idPlataforma);
                context.startActivity(intent);

            }
        });
    }

    @Override
    public int getItemCount() {
        return plataformas.size();
    }
}
