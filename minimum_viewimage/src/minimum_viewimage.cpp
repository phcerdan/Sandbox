#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkViewImage.h"

int main(int argc, char *argv[])
{
  using PixelType = float;
  constexpr unsigned int Dimension = 3;
  using ImageType = itk::Image<PixelType, Dimension>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  auto reader = ReaderType::New();
  reader->SetFileName("/tmp/Slicer-phc/RemoteIO/MR-head.nrrd");
  reader->Update();
  itk::ViewImage<ImageType>::View(reader->GetOutput());
};
