#include <cmath>
#include <QColor>

double* RGBtoXYZ (QColor color)
{
    double *xyz = new double[3];
    double var_R = ( double(color.red()) / 255 );
    double var_G = ( double(color.green()) / 255 );
    double var_B = ( double(color.blue()) / 255 );

    if ( var_R > 0.04045 )
    {
        var_R = pow((( var_R + 0.055 ) / 1.055 ), 2.4);
    }
    else
    {
        var_R /= 12.92;
    }

    if ( var_G > 0.04045 )
    {
        var_G = pow((( var_G + 0.055 ) / 1.055 ), 2.4);
    }
    else
    {
        var_G /= 12.92;
    }

    if ( var_B > 0.04045 )
    {
        var_B = pow((( var_B + 0.055 ) / 1.055 ), 2.4);
    }
    else
    {
        var_B /= 12.92;
    }

    xyz[0] = (var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805)*100;
    xyz[1] = (var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722)*100;
    xyz[2] = (var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505)*100;

    return xyz;
}

int* XYZtoRGB(double X, double Y, double Z)
{
    double var_X = X / 100;
    double var_Y = Y / 100;
    double var_Z = Z / 100;

    double var_R = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
    double var_G = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415;
    double var_B = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570;

    if ( var_R > 0.0031308 )
    {
        var_R = 1.055 * ( pow(var_R,( 1 / 2.4 )) ) - 0.055;
    }
    else
    {
        var_R *= 12.92;
    }

    if ( var_G > 0.0031308 )
    {
        var_G = 1.055 * ( pow(var_G,( 1 / 2.4 )) ) - 0.055;
    }
    else
    {
        var_G *= 12.92;
    }

    if ( var_B > 0.0031308 )
    {
        var_B = 1.055 * ( pow(var_B,( 1 / 2.4 )) ) - 0.055;
    }
    else
    {
        var_B *= 12.92;
    }

    int *rgb = new int[3];

    rgb[0] = int(var_R * 255);
    rgb[1] = int(var_G * 255);
    rgb[2] = int(var_B * 255);

    return rgb;
}

double* XYZtoLAB(double *xyz)
{
    double *lab = new double[3];
    double var_X = xyz[0] / 95.047;
    double var_Y = xyz[1] / 100;
    double var_Z = xyz[2] / 108.883;

    if ( var_X > 0.008856 )
    {
        var_X = pow(var_X,(0.3333333333));
    }
    else
    {
        var_X = ( 7.787 * var_X ) + ( 16 / 116 );
    }

    if ( var_Y > 0.008856 )
    {
        var_Y = pow(var_Y,(0.3333333333));
    }
    else
    {
        var_Y = ( 7.787 * var_Y ) + ( 16 / 116 );
    }

    if ( var_Z > 0.008856 )
    {
        var_Z = pow(var_Z,(0.3333333333));
    }
    else
    {
        var_Z = ( 7.787 * var_Z ) + ( 16 / 116 );
    }

    lab[0] = ( 116 * var_Y ) - 16;
    lab[1] = 500 * ( var_X - var_Y );
    lab[2] = 200 * ( var_Y - var_Z );
    return(lab);
}

double* LABtoXYZ(double *lab)
{
    double *xyz = new double[3];
    double var_Y = ( lab[0] + 16 ) / 116;
    double var_X = lab[1] / 500 + var_Y;
    double var_Z = var_Y - lab[2] / 200;

    if ( pow(var_Y,3)  > 0.008856 )
    {
        var_Y = pow(var_Y,3);
    }
    else
    {
        var_Y = ( var_Y - 16 / 116 ) / 7.787;
    }

    if ( pow(var_Z,3)  > 0.008856 )
    {
        var_Z = pow(var_Z,3);
    }
    else
    {
        var_Z = ( var_Z - 16 / 116 ) / 7.787;
    }

    if ( pow(var_X,3)  > 0.008856 )
    {
        var_X = pow(var_X,3);
    }
    else
    {
        var_X = ( var_X - 16 / 116 ) / 7.787;
    }

    xyz[0] = var_X * 95.047;
    xyz[1] = var_Y * 100;
    xyz[2] = var_Z * 108.883;
    return xyz;
}
