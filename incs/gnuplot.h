#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#define GP_MAX_TMP_FILES 64

// Estructura para manejar la comunicación con gnuplot.
typedef struct _gnuplot_ctrl
{
    FILE *gp_pipe;                            // Pipe para la comunicación con gnuplot.
    char *tmp_filename_tbl[GP_MAX_TMP_FILES]; // Archivos temporales usados por gnuplot.
    int nplots;                               // Número de gráficos.
} gnuplot_ctrl;

// Inicializa la comunicación con gnuplot.
gnuplot_ctrl *gnuplot_init(void);

// Cierra la comunicación con gnuplot.
void gnuplot_close(gnuplot_ctrl *);

// Establece el estilo de los gráficos en gnuplot.
void gnuplot_setstyle(gnuplot_ctrl *, const char *);

// Establece el título del gráfico en gnuplot.
void gnuplot_settitle(gnuplot_ctrl *, const char *);

// Establece la etiqueta del eje X.
void gnuplot_set_xlabel(gnuplot_ctrl *, const char *);

// Establece la etiqueta del eje Y.
void gnuplot_set_ylabel(gnuplot_ctrl *, const char *);

// Grafica un conjunto de puntos (x, y) en gnuplot.
void gnuplot_plot_xy(gnuplot_ctrl *, const double *, const double *, int, const char *);

// Guarda el gráfico generado en un archivo.
void gnuplot_saveplot(gnuplot_ctrl *, const char *);

// Envía comandos personalizados a gnuplot.
void gnuplot_cmd(gnuplot_ctrl *, const char *, ...);
