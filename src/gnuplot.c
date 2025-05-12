#include "gnuplot.h"

// Inciar el manejo de gnuplot.
gnuplot_ctrl *gnuplot_init(void)
{
    gnuplot_ctrl *handle = (gnuplot_ctrl *)malloc(sizeof(gnuplot_ctrl));
    if (!handle)
        return NULL;

    handle->gp_pipe = popen("gnuplot -persist", "w");
    if (!handle->gp_pipe)
    {
        free(handle);
        return NULL;
    }

    handle->nplots = 0;
    memset(handle->tmp_filename_tbl, 0, sizeof(handle->tmp_filename_tbl));
    return handle;
}

// Cerrar el manejo de gnuplot.
void gnuplot_close(gnuplot_ctrl *handle)
{
    if (handle)
    {
        pclose(handle->gp_pipe);
        free(handle);
    }
}

// Funciones para manejar gnuplot.
void gnuplot_setstyle(gnuplot_ctrl *handle, const char *plot_style)
{
    fprintf(handle->gp_pipe, "set style data %s\n", plot_style);
}

// Funciones para establecer el título y etiquetas de los ejes.
void gnuplot_settitle(gnuplot_ctrl *handle, const char *title)
{
    fprintf(handle->gp_pipe, "set title \"%s\"\n", title);
}

// Funciones para establecer etiquetas del eje X.
void gnuplot_set_xlabel(gnuplot_ctrl *handle, const char *label)
{
    fprintf(handle->gp_pipe, "set xlabel \"%s\"\n", label);
}

// Funciones para establecer etiquetas del eje Y.
void gnuplot_set_ylabel(gnuplot_ctrl *handle, const char *label)
{
    fprintf(handle->gp_pipe, "set ylabel \"%s\"\n", label);
}

// Funciones para graficar datos XY.
void gnuplot_plot_xy(gnuplot_ctrl *handle, const double *x, const double *y, int n, const char *title)
{
    fprintf(handle->gp_pipe, "plot '-' title \"%s\" with lines\n", title);
    for (int i = 0; i < n; i++)
        fprintf(handle->gp_pipe, "%lf %lf\n", x[i], y[i]);
    fprintf(handle->gp_pipe, "e\n");
    fflush(handle->gp_pipe);
}

// Funciones para guardar la gráfica en un archivo PNG.
void gnuplot_saveplot(gnuplot_ctrl *handle, const char *filename)
{
    fprintf(handle->gp_pipe, "set terminal pngcairo size 800,600\n");
    fprintf(handle->gp_pipe, "set output \"%s\"\n", filename);
    fprintf(handle->gp_pipe, "replot\n");
    fprintf(handle->gp_pipe, "set output\n"); // Cerrar el archivo de salida.
    fprintf(handle->gp_pipe, "set terminal pop\n");
    fflush(handle->gp_pipe);
}

// Funciones para ejecutar comandos gnuplot.
void gnuplot_cmd(gnuplot_ctrl *handle, const char *cmd, ...)
{
    va_list ap;
    va_start(ap, cmd);
    vfprintf(handle->gp_pipe, cmd, ap);
    fprintf(handle->gp_pipe, "\n");
    va_end(ap);
    fflush(handle->gp_pipe);
}