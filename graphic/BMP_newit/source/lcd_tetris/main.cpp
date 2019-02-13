#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

typedef struct _PIXEEL_DATA_POS_RGB
{
/* position data*/
    int x;
    int y;

  /*RGB data*/    
    unsigned char r;
    unsigned char g;
    unsigned char b;
} PixelData;

PixelData SetPixelData(int x, int y, unsigned char r, unsigned char g, unsigned char b);

void DisplayIMG(PixelData IMG_Data[][400], int Length, int Height);
void SetPixelColor(PixelData *p, unsigned char r, unsigned char g, unsigned char b);

void Interpolation(PixelData **(IMG_Data[][400]), int Length, int Height);

void CleanIMG(PixelData IMG_Data[][400], unsigned char *PixelData, char StartPixelAddress, int IMG_Length, int IMG_Height, int Degree);
void RotateImg(PixelData IMG_Data[][400], int ArrLength, int ArrHeight, unsigned char *PixelData, char StartPixelAddress, int IMG_Length, int IMG_Height, int Degree, int InterpolationState);
double ConvRadian(int Degree);

int main()
{
    unsigned int size;
    char *buf;
    char *buf1;
    char *buf2;
    unsigned int count=0;
    unsigned int y_position=5;
    unsigned int x_position=202;
    int ch;
    int speed=20;

    int width, height;

    unsigned char * data;
    FILE * file;
 
    unsigned int k, color;
    int i, j;
    unsigned char r,g,b;
    unsigned short tmp_rgb;
    unsigned int toggle;
    unsigned char init_value=0x30;
    PixelData ImgData[400][400];
    
    initwindow( 400 , 400 , "lcd_tetris" ); 
    
      file = fopen( "tiger.bmp", "rb" );
    
    if ( file == NULL ) return 0;
    
    width = 320;
    height = 240;
    
    data = (unsigned char *)malloc( width * height * 4 );
    //  fread( data, width * height * 2 + 0x46, 1, file );
    fread( data, width * height * 3 + 0x36, 1, file );
    
    fclose( file );

    
    for(i=0;i<16;i++)
        printf(" 0x%02x ",*(data+i));
    
    printf("\n");
#if 1

// BMP 24 bit format
      for(i=0;i<240;i++){
           for(j=0;j<320;j++){
               b=*(data+0x36 + j*3 + i*320*3) ;
               g=*(data+0x37 + j*3 + i*320*3) ;
               r=*(data+0x38 + j*3 + i*320*3) ;

               putpixel(319-j, 240-i,COLOR(r,g,b)); 
           }
      }
      
int cnt=0;

while(1)
{
    
    RotateImg(ImgData, 400, 400, data, 0x36, 320, 240, cnt, 1);
    
    DisplayIMG(ImgData, 400, 400);
    CleanIMG(ImgData, data, 0x36, 400, 400, cnt);
    DisplayIMG(ImgData, 400, 400);
    cnt+=10;
}

#endif
    getch();   
  
    closegraph();    
    return 0;
}// end of main();



void RotateImg(PixelData IMG_Data[][400],int ArrLength, int ArrHeight, unsigned char *PixelData, char StartPixelAddress, int IMG_Length, int IMG_Height, int Degree, int InterpolationState)
{
    double Radian, Pixel_x, Pixel_y;
    int Length, Height, Center_x, Center_y;
    unsigned char r, g, b;
    int i, j;
    
    Center_x=IMG_Length/2;
    Center_y=IMG_Height/2;
    
    //setactivepage(1);
    
    Radian= ConvRadian(Degree);
    
    for(Length=0; Length<IMG_Length; Length++)
    {
        for(Height=0; Height<IMG_Height; Height++)
        {
            b=*(PixelData+ StartPixelAddress + Length*3 + Height*IMG_Length*3) ;
            g=*(PixelData+(StartPixelAddress+1) + Length*3 + Height*IMG_Length*3) ;
            r=*(PixelData+(StartPixelAddress+2) + Length*3 + Height*IMG_Length*3) ;
            
            Pixel_x= (Length-Center_x)*cos(Radian)-(Height-Center_y)*sin(Radian)+Center_x;
            Pixel_y= (Length-Center_x)*sin(Radian)+(Height-Center_y)*cos(Radian)+Center_y;
            
            if(Pixel_x<0 || Pixel_y<0)
            {
                continue;
            }
            IMG_Data[(int)Pixel_y][(int)Pixel_x]= SetPixelData((int)Pixel_x, (int)Pixel_y, r, g, b);
        }
    }
    
    if(InterpolationState==1)
    {   
        for(i=0; i<ArrHeight; i++)
        {
            for(j=0; j<ArrLength; j++)
            {
                if(j==0)
                {
                    (IMG_Data[i][j]).r=(IMG_Data[i][j+1]).r;
                    (IMG_Data[i][j]).g=(IMG_Data[i][j+1]).g;
                    (IMG_Data[i][j]).b=(IMG_Data[i][j+1]).b;
                }
                
                else if(j==IMG_Length-1)
                {
                    (IMG_Data[i][j]).r=(IMG_Data[i][j-1]).r;
                    (IMG_Data[i][j]).g=(IMG_Data[i][j-1]).g;
                    (IMG_Data[i][j]).b=(IMG_Data[i][j-1]).b;
                }
                
                else
                {
                    if(IMG_Data[i][j].r==0 && IMG_Data[i][j].g==0 && IMG_Data[i][j].b==0)
                    {
                    (IMG_Data[i][j]).r=( (IMG_Data[i][j-1]).r+(IMG_Data[i][j+1]).r )/2;
                    (IMG_Data[i][j]).g=( (IMG_Data[i][j-1]).g+(IMG_Data[i][j+1]).g )/2;
                    (IMG_Data[i][j]).b=( (IMG_Data[i][j-1]).b+(IMG_Data[i][j+1]).b )/2;
                    }
                }
            }
        }
    }
    //setvisualpage(1);
}

void CleanIMG(PixelData IMG_Data[][400], unsigned char *PixelData, char StartPixelAddress, int IMG_Length, int IMG_Height, int Degree)
{
    double Radian, Pixel_x, Pixel_y;
    int Length, Height, Center_x, Center_y;
    
    Center_x=IMG_Length/2;
    Center_y=IMG_Height/2;
    
    //setactivepage(1);
    
    Radian= ConvRadian(Degree);
    
    for(Length=0; Length<IMG_Length; Length++)
    {
        for(Height=0; Height<IMG_Length; Height++)
        {   
            Pixel_x= (Length-Center_x)*cos(Radian)-(Height-Center_y)*sin(Radian)+Center_x;
            Pixel_y= (Length-Center_x)*sin(Radian)+(Height-Center_y)*cos(Radian)+Center_y;
            
            
            //IMG_Data[(int)Pixel_y][(int)Pixel_x]= SetPixelData((int)Pixel_x, (int)Pixel_y, 0, 0, 0);
            IMG_Data[(int)Height][(int)Length]= SetPixelData((int)Length, (int)Height, 0, 0, 0);
            //putpixel(Length, Height, COLOR(0,0,0) ); 
        }
    }
    //setvisualpage(1);
}



double ConvRadian(int Degree)
{
    return (PI*Degree)/180;
}

PixelData SetPixelData(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    PixelData data;
    
    data.x=x;
    data.y=y;
    
    data.r=r;
    data.g=g;
    data.b=b;
    
    return data;
}

void DisplayIMG(PixelData IMG_Data[][400], int Length, int Height)
{
    int i, j;
    setactivepage(2);
    for(i=0; i<Length; i++)
    {
        for(j=0; j<Length; j++)
        {
            putpixel( IMG_Data[i][j].x, IMG_Data[i][j].y, COLOR(IMG_Data[i][j].r, IMG_Data[i][j].g, IMG_Data[i][j].b) ); 
        }
    }
    setvisualpage(2);
}

/*void Interpolation(PixelData **(IMG_Data[][320]), int Length, int Height)
{
    int i,j;
    
    for(i=0; i<Height; i++)
    {
        for(j=0; j<Length; j++)
        {
            if(j==0)
            {
                (IMG_Data[i][j])->r=(IMG_Data[i][j+1])->r;
                (IMG_Data[i][j])->g=(IMG_Data[i][j+1])->g;
                (IMG_Data[i][j])->b=(IMG_Data[i][j+1])->b;
            }
            
            else if(j==Length-1)
            {
                (IMG_Data[i][j])->r=(IMG_Data[i][j-1])->r;
                (IMG_Data[i][j])->g=(IMG_Data[i][j-1])->g;
                (IMG_Data[i][j])->b=(IMG_Data[i][j-1])->b;
            }
            
            else
            {
                (IMG_Data[i][j])->r=( (IMG_Data[i][j-1])->r+(IMG_Data[i][j+1])->r )/2;
                (IMG_Data[i][j])->g=( (IMG_Data[i][j-1])->g+(IMG_Data[i][j+1])->g )/2;
                (IMG_Data[i][j])->b=( (IMG_Data[i][j-1])->b+(IMG_Data[i][j+1])->b )/2;
            }
        }
    }
}*/
