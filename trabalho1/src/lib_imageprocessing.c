
#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"
#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}

void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
  printf("Imagem salva com sucesso\n");
}

void aplicar_brilho(imagem *I, float intensidade) {
    /* Muda o brilho da imagem por um fator linear intensidade que
     * pode ir de 0 a 1 */
     unsigned int i;
     for (i=0; i<(I->width)*(I->height); i++){
         if(I->r[i] * intensidade <= 255 ){
             I->r[i] *= intensidade;
         }
         else I->r[i] = 255;
         if(I->g[i] * intensidade <= 255 ){
             I->g[i] *= intensidade;
         }
         else I->g[i] = 255;
         if(I->b[i] * intensidade <= 255 ){
             I->b[i] *= intensidade;
         }
         else I->b[i] = 255;
   }

}

void printa_max(imagem *I){

    unsigned int i;
    float max = 0;
    for (i=0; i<(I->width)*(I->height); i++) {
        if(I->r[i] + I->g[i] + I->b[i] > max)
            max = I->r[i] + I->g[i] + I->b[i];
    }
    printf("O pixel de intensidade maxima vale %f\n",max);

}
