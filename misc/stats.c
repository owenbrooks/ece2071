#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

int main(int argc, char **argv)
{
  MagickBooleanType status;

  MagickWand *magick_wand;

  if (argc != 2)
  {
    (void)fprintf(stdout, "Usage: %s image\n", argv[0]);
    exit(0);
  }

  /*
    Read an image.
  */
  MagickWandGenesis();
  magick_wand = NewMagickWand();
  status = MagickReadImage(magick_wand, argv[1]);

  ChannelStatistics *channel_statistics;
  channel_statistics = MagickGetImageStatistics(magick_wand);
  double std_dev_red = channel_statistics[RedChannel].standard_deviation;
  double red_mean = channel_statistics[RedChannel].mean;

  printf("mean: %f, std_dev: %f\n", red_mean, std_dev_red);

  magick_wand = DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  return (0);
}
