
#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>           // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp>     // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp>     // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp>         // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp>     // Lectura y escritura de videos

using namespace std;
using namespace cv;
Mat resta;
Mat resultado;
Mat negativo;
Mat negativo1;
Mat nueba;

int main(int argc, char *argv[])
{    
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Ejercicio", WINDOW_AUTOSIZE);
    namedWindow("Resultado", WINDOW_AUTOSIZE);

    Mat imagen = imread("./BRUCE_BANER.png");
    Mat imagen2 = imread("./BRUCE_BANER2.png");

    absdiff(imagen2, imagen, resta);
    nueba = Mat::zeros(imagen.size(), imagen.type());
    for (int i = 0; i < resta.rows; i++)
    {

        for (int j = 0; j < resta.cols; j++)
        {

            int pixelb = resta.at<Vec3b>(i, j)[0];
            int pixelg = resta.at<Vec3b>(i, j)[1];
            int pixelr = resta.at<Vec3b>(i, j)[2];

            if (pixelb > 0)
            {
                int limite;

                for (int x = j; x < imagen.cols; x++)
                {
                    if (resta.at<Vec3b>(i, x)[0] > 0)
                    {
                        limite = x;
                    }
                }
                for (int x = j; x < limite; x++)
                {
                    nueba.at<Vec3b>(i, x)[0] = 255; 
                    nueba.at<Vec3b>(i, x)[1] = 255; 
                    nueba.at<Vec3b>(i, x)[2] = 255;
                }
            }
        }
    }
    cvtColor(nueba,nueba,COLOR_RGB2GRAY);

    Mat src = imagen.clone();
    Mat mask = nueba.clone();
    Mat roi = src(Rect(0, 0,300,289));

    for (int i = 0; i < roi.rows; i++)
    {
        Vec3b *imgrow = roi.ptr<Vec3b>(i);
        uchar *mskrow = mask.ptr<uchar>(i);

        for (int j = 0; j < roi.cols; j++)
        {
            // verificar si el pixel esta dentro de la mascara
            if (mskrow[j] >= 1)
            {
                int pixelb = imagen.at<Vec3b>(i, j)[0];
                int pixelg = imagen.at<Vec3b>(i, j)[1];
                int pixelr = imagen.at<Vec3b>(i, j)[2];

                imgrow[j][0] =255-pixelb;
                imgrow[j][1] = 255-pixelg;
                imgrow[j][2] = 255-pixelr;
            }
        }
    }

    imshow("Original", imagen);
    imshow("Resultado", src);
    imshow("Ejercicio", imagen2);
   
    waitKey();
    destroyAllWindows();

    return 0;
}
